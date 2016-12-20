// 2015.07.26
// Hrytsevich Anton
// ClearAVLTree.cpp
//

#include "stdafx.h"

#include <ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <math.h>
#include <assert.h>

namespace AVL_Tree
{
	struct TreeNode
	{
		float value;
		unsigned int deep; // it need for balancing tree by Adelson-Velsky and Landis' algorithm 
		TreeNode* left;
		TreeNode* right;

		TreeNode() : left(NULL), right(NULL), deep(1){};
		TreeNode(float val) : left(NULL), right(NULL), deep(1) { value = val;}
	};

	//Georgy Adelson-Velsky and Landis' tree 
	// https://en.wikipedia.org/wiki/AVL_tree
	class CAVLTree 
	{
	private:
		TreeNode *m_root;

		const float Difference;			// different for auto generated nodes
		const short MinCriticalDifferent; // different -2 it's max critical different for AVL Tree
		const short MaxCriticalDifferent; // different 2 it's max critical different for AVL Tree

	private:
		void CAVLTree::Clear( TreeNode* node ) // for destructor
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

		inline unsigned char GetDeep(TreeNode* node)
		{
			return ( node ? node->deep : 0 );
		}

		inline int GetImbalance(TreeNode* node)
		{
			if ( !node ) return 0;

			return ( GetDeep( node->right ) - GetDeep( node->left) );
		}

		void SetDeep(TreeNode* node)
		{
			unsigned int leftSubTree = GetDeep( node->left );
			unsigned int rightSubTree = GetDeep( node->right );

			node->deep = ( leftSubTree > rightSubTree ? leftSubTree : rightSubTree ) + 1;
		}

		TreeNode* RotateToTheRight(TreeNode* node)
		{
			TreeNode* leftSubTree = node->left;
			
			node->left = leftSubTree->right;
			leftSubTree->right = node;
			
			SetDeep(node);
			SetDeep(leftSubTree);

			return leftSubTree;
		}

		TreeNode* RotateToTheLeft(TreeNode* node)
		{
			TreeNode* rightSubTree = node->right;
			
			node->right = rightSubTree->left;
			rightSubTree->left = node;
			
			SetDeep(node);
			SetDeep(rightSubTree);

			return rightSubTree;
		}

		TreeNode* Balancing(TreeNode* node)
		{
			SetDeep(node);

			if( GetImbalance(node) == MaxCriticalDifferent ) 
			{
				if( GetImbalance(node->right) < 0 )
				{
					node->right = RotateToTheRight(node->right);
				}

				return RotateToTheLeft(node);
			}

			if( GetImbalance(node) == MinCriticalDifferent ) //different -2 it's critical for AVL Tree
			{
				if( GetImbalance(node->left) > 0  )
				{
					node->left = RotateToTheLeft(node->left);
				}

				return RotateToTheRight(node);
			}
			return node; // other cases balancing no need
		}

		TreeNode* Insert(TreeNode* node, float val)
		{
			if( !node ) 
			{
				return new TreeNode(val);
			}

			if( val < node->value )
			{
				node->left = Insert(node->left,val);
			}
			else if ( val > node->value )
			{
				node->right = Insert(node->right,val);
			}
			else // it's equal
			{
				// have to miss
				//assert(0);
				std::cout << " Miss " << val;
			}

			return Balancing(node);
		}

	public:
		CAVLTree() : 
			m_root(NULL), 
			Difference(5.0),
			MinCriticalDifferent(-2), //
			MaxCriticalDifferent(2) //
		{}

		~CAVLTree()
		{
			Clear(m_root);
		}

		TreeNode* generate_tree( std::vector<float> nums)
		{
			if ( !nums.size() ) return NULL;
			if ( nums.size() == 1) return Insert(m_root, nums[0]);

			std::vector<float> bases;

			//calculate count of elements to build absolutely balancing tree
			float integer, fraction; 
			float base = (float)(log(nums.size()) / log(2)); // log base 2  
			fraction = std::modf(base, &integer);

			base = !fraction ? integer : (integer + 1); // round

			unsigned int nHelpfullElements = 0;

			for ( float i = base; i > -1; i-- ) // until zero 2^0 - it's root
			{
				nHelpfullElements += (int)pow( 2, i);
			}

			std::sort (nums.begin(), nums.end());

			srand (static_cast <unsigned> (time(0)));

			// create base of tree
			for (unsigned int index = 0; index < nHelpfullElements; index++)
			{
				if ( (index + 1) < nums.size() ) // for existing numbers
				{
					//base = nums[index] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nums[index + 1]-nums[index])));
					base = nums[index] + ( nums[index + 1]-nums[index])/2;
				}
				else// for non existing 
				{
					base = bases[index - 1] + Difference;
				}

				bases.push_back(base);
			}

			bases.insert(bases.end(), nums.begin(), nums.end());

			for ( auto it = bases.begin(); it != bases.end(); ++it )
			{
				m_root = Insert( m_root, *it );
			}

			return m_root;
		}

		long Count(TreeNode* node)
		{
			if ( !node ) return 0;

			long result = Count(node->right);

			result += Count(node->left);

			return result + 1;
		}

		TreeNode* Find(TreeNode* node, float val)
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
	};
}


int _tmain(int argc, _TCHAR* argv[])
{
	srand (static_cast <unsigned> (time(0)));

	for ( unsigned int max = 1; max < UINT_MAX; max++ )
	{
		std::vector<float> nums;

		std::cout << " Now is " << max;

		for (unsigned int i = 0; i < max; i++)
		{
			//float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/max));
			nums.push_back((float)i);
			//std::cout << r << " ";
		}

		//std::cout << "\n\n\n";

		AVL_Tree::CAVLTree searcher;

		AVL_Tree::TreeNode *root = searcher.generate_tree(nums);

		//sercher.print_t(root);

		unsigned int deepInit = 1; // have to be here
		unsigned int deepVariable = 1;

		for( auto it = nums.begin(); it != nums.end(); ++it)
		{
			deepVariable = searcher.Find(root, *it)->deep;

			if ( deepVariable != deepInit )
			{
				long result = searcher.Count(root);

				std::cout << " Imbalance detected!!!";
			}
		}

		std::cout << "\n";

		nums.clear();
	}
	
	return 0;
}

