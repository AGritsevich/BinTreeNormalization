#include "stdafx.h"
#include "RandomTree.h"
/*
int CSearchBinTreeHelperV1::GetWeight(TreeNodeV1* node)
{
	if( !node ) return 0; 
	return node->weight; 
}

void CSearchBinTreeHelperV1::SetWeight(TreeNodeV1* node)
{
	node->weight = GetWeight(node->left) + GetWeight(node->right) + 1;// + this node 
}

TreeNodeV1* CSearchBinTreeHelperV1::RotatetoRight(TreeNodeV1* M)
{
	TreeNodeV1* N = M->left; 

	if( !N ) return M;

	M->left = N->right; 
	N->right = M; 
	N->weight = M->weight;
	SetWeight(M);

	return N; 
};

TreeNodeV1* CSearchBinTreeHelperV1::RotateToLeft(TreeNodeV1* N)
{
	TreeNodeV1* M = N->right;

	if( !M ) return N;

	N->right = M->left;
	M->left = N;
	M->weight = N->weight;
	SetWeight(N);

	return M;
};

TreeNodeV1* CSearchBinTreeHelperV1::InsertRoot(TreeNodeV1* node, float val)
{
	if ( !node ) return new TreeNodeV1(val);

	if ( val < node->value )
	{
		node->left = InsertRoot(node->left, val);
		return RotatetoRight(node);
	}
	else
	{
		node->right = InsertRoot(node->right, val);
		return RotateToLeft(node);
	}

	return NULL;
};

TreeNodeV1* CSearchBinTreeHelperV1::Insert(TreeNodeV1* node, float val)
{
	if ( !node ) return new TreeNodeV1(val);

	srand (static_cast <unsigned> (time(0)));


	if ( rand() % ( node->weight + 1 ) == 0 )
	{
		return CSearchBinTreeHelperV1::InsertRoot(node, val);
	}

	if ( node->value > val)
	{
		node->left = Insert(node->left, val);
	}
	else
	{
		node->right = Insert(node->right, val);
	}

	SetWeight(node);

	return node;
};

TreeNodeV1* CSearchBinTreeHelperV1::Find(TreeNodeV1* node, float val)
{
	if ( !node ) return NULL;

	if (val == node->value) return node;

	if ( val < node->value)
	{
		return Find(node->left, val);
	}
	else
	{
		return Find(node->right, val);
	}

	return node;
};

int CSearchBinTreeHelperV1::_print_t(TreeNodeV1 *tree, int is_left, int offset, int depth, char s[30][255])
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

void CSearchBinTreeHelperV1::print_t(TreeNodeV1 *tree)
{
	const int wide = 30;
	char s[wide][255] = {};
	for (int i = 0; i < wide; i++)
	{
		sprintf_s(s[i], sizeof(s[i]), "%80s", " ");
	}

	_print_t(tree, 0, 0, 0, s);

	for (int i = 0; i < wide; i++)
	{
		printf("%s\n", s[i]);
	}
}

TreeNodeV1* CSearchBinTreeHelperV1::generate_tree( std::vector<float> nums)
{
	std::vector<float> bases;
	std::vector<float> result;
	MAX_N = nums.size();

	std::sort (nums.begin(), nums.end());
	float min = *nums.begin(); //min
	float max = nums[MAX_N - 1]; //max

	srand (static_cast <unsigned> (time(0)));

	for (int index = 0; index < MAX_N - 1; index++)
	{
		float base = nums[index] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nums[index + 1]-nums[index])));

		bases.push_back(base);
		//m_root = Insert(m_root, base);
	}

	std::random_shuffle ( bases.begin(), bases.end() );

	bases.insert(bases.end(), nums.begin(), nums.end());

	for (unsigned int index = 0; index < bases.size(); index++)
	{
		m_root = InsertRoot(m_root, bases[index]);
	}

	return m_root;
}*/