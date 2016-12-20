#include "stdafx.h"
#include "AVL_Tree.h"

CAVLTree::CAVLTree() : 
	m_root(NULL), 
	m_nHelpfullElements(10), 
	Difference(5.0)
{

}

CAVLTree::~CAVLTree()
{
	Clear(m_root);
}

void CAVLTree::Clear( TreeNode* node )
{
	if ( !node ) return;

	if ( node->right )
	{
		Clear(node->right);
		node->right = NULL;
	}

	if ( node->left )
	{
		Clear(node->left);
		node->left = NULL;
	}

	delete node;
	node = NULL;
}

inline unsigned char CAVLTree::GetHeight(TreeNode* p)
{
	return p  ?p->height:0;
}

inline int CAVLTree::bfactor(TreeNode* p)
{
	return GetHeight(p->right)-GetHeight(p->left);
}

void CAVLTree::SetHight(TreeNode* p)
{
	unsigned int hl = GetHeight(p->left);
	unsigned int hr = GetHeight(p->right);
	p->height = (hl>hr?hl:hr)+1;
}

TreeNode* CAVLTree::RotateToTheRight(TreeNode* p) // правый поворот вокруг p
{
	TreeNode* q = p->left;
	p->left = q->right;
	q->right = p;
	SetHight(p);
	SetHight(q);
	return q;
}

TreeNode* CAVLTree::RotateToTheLeft(TreeNode* q) // левый поворот вокруг q
{
	TreeNode* p = q->right;
	q->right = p->left;
	p->left = q;
	SetHight(q);
	SetHight(p);
	return p;
}

TreeNode* CAVLTree::Balancing(TreeNode* p) // балансировка узла p
{
	SetHight(p);
	if( bfactor(p)==2 )
	{
		if( bfactor(p->right) < 0 )
			p->right = RotateToTheRight(p->right);
		return RotateToTheLeft(p);
	}
	if( bfactor(p)==-2 )
	{
		if( bfactor(p->left) > 0  )
			p->left = RotateToTheLeft(p->left);
		return RotateToTheRight(p);
	}
	return p; // балансировка не нужна
}

TreeNode* CAVLTree::Insert(TreeNode* p, float k) // вставка ключа k в дерево с корнем p
{
	if( !p ) return new TreeNode(k);
	if( k<p->value )
		p->left = Insert(p->left,k);
	else
		p->right = Insert(p->right,k);
	return Balancing(p);
}

TreeNode* CAVLTree::GetDippestNod(TreeNode* p) // поиск узла с минимальным ключом в дереве p 
{
	return p->left?GetDippestNod(p->left):p;
}

TreeNode* CAVLTree::removemin(TreeNode* p) // удаление узла с минимальным ключом из дерева p
{
	if( p->left==0 )
		return p->right;
	p->left = removemin(p->left);
	return Balancing(p);
}

TreeNode* CAVLTree::remove(TreeNode* p, float k) // удаление ключа k из дерева p
{
	if( !p ) return 0;
	if( k < p->value )
		p->left = remove(p->left,k);
	else if( k > p->value )
		p->right = remove(p->right,k);	
	else //  k == p->key 
	{
		TreeNode* q = p->left;
		TreeNode* r = p->right;
		delete p;
		if( !r ) return q;
		TreeNode* min = GetDippestNod(r);
		min->right = removemin(r);
		min->left = q;
		return Balancing(min);
	}
	return Balancing(p);
}

int CAVLTree::_print_t(TreeNode *tree, int is_left, int offset, int depth, char s[30][255])
{
	char b[80] = {};
	int width = 6;

	if (!tree) return 0;

	sprintf_s(b, sizeof(b), "(%2.1f) ", tree->value);

	int left  = _print_t(tree->left,  1, offset,                depth + 1, s);
	int right = _print_t(tree->right, 0, offset + left + width, depth + 1, s);

	for (int i = 0; i < width; i++)
	{
		s[2 * depth][offset + left + i] = b[i];
	}

	if (depth && is_left)
	{

		for (int i = 0; i < width + right; i++)
		{
			s[2 * depth - 1][offset + left + width/2 + i] = '-';
		}

		s[2 * depth - 1][offset + left + width/2] = '+';
		s[2 * depth - 1][offset + left + width + right + width/2] = '+';

	}
	else if (depth && !is_left)
	{

		for (int i = 0; i < left + width; i++)
		{
			s[2 * depth - 1][offset - width/2 + i] = '-';
		}

		s[2 * depth - 1][offset + left + width/2] = '+';
		s[2 * depth - 1][offset - width/2 - 1] = '+';
	}

	return left + width + right;
}

void CAVLTree::print_t(TreeNode *tree)
{
	const int wide = 30;
	char s[wide][255] = {};
	for (int i = 0; i < wide; i++)
	{
		sprintf_s(s[i], sizeof(s[i]), "%249s", " ");
	}

	_print_t(tree, 0, 0, 0, s);

	std::ofstream myfile;
	myfile.open ("OutPutTree.txt");
	myfile << "\r ~~~Tree~~~\n";
	
	for (int i = 0; i < wide; i++)
	{
		//printf("%s\n", s[i]);
		myfile << s[i];
	}

	myfile.close();
}

TreeNode* CAVLTree::generate_tree( std::vector<float> nums)
	{
		std::vector<float> bases;

		//calculate count of elements to build absolutely balancing tree
		float integer, fraction; 
		float base = (float)(log(nums.size()) / log(2)); // log base 2   
		fraction = std::modf(base, &integer); // целая часть запишется в x, дробная - в y
		base = !fraction ? integer : (integer + 1);
		m_nHelpfullElements = (int)pow( 2, base);
		m_nHelpfullElements -= 1; // root hasn't brother 2^0

		std::sort (nums.begin(), nums.end());

		srand (static_cast <unsigned> (time(0)));

		// create base of tree
		for (unsigned int index = 0; index < m_nHelpfullElements; index++)
		{
			if ( (index + 1) < nums.size() ) // for existing numbers
			{
				base = nums[index] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nums[index + 1]-nums[index])));
			}
			else// for non existing 
			{
				base = bases[index - 1] + Difference;
			}

			bases.push_back(base);
		}

		bases.insert(bases.end(), nums.begin(), nums.end());

		for (unsigned int index = 0; index < bases.size(); index++)
		{
			m_root = Insert(m_root, bases[index]);
		}

		return m_root;
}




