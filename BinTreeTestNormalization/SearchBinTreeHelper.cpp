#include "stdafx.h"
#include "SearchBinTreeHelper.h"


CSearchBinTreeHelper::CSearchBinTreeHelper(void) :m_root(NULL), MAX_N(1000)
{
}


CSearchBinTreeHelper::~CSearchBinTreeHelper(void)
{
}

TreeNodeV2* CSearchBinTreeHelper::Insert(TreeNodeV2* node, float val)
{
	if ( !node ) return new TreeNodeV2(val);

	if ( val < node->value )
	{
		node->left = Insert(node->left, val);
	}
	else
	{
		node->right = Insert(node->right, val);
	}

	return node;
};

TreeNodeV2* CSearchBinTreeHelper::Find(TreeNodeV2* node, float val)
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

TreeNodeV2* CSearchBinTreeHelper::generate_tree( std::vector<float> nums)
{
	std::vector<float> bases;
	MAX_N = nums.size();

	std::sort (nums.begin(), nums.end());
	float min = *nums.begin(); //min
	float max = nums[MAX_N - 1]; //max

	srand (static_cast <unsigned> (time(0)));

	for (int index = 0; index < MAX_N - 1; index++)
	{
		float base = nums[index] + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(nums[index + 1]-nums[index])));

		bases.push_back(base);
	}

	// cheap balancing
	std::random_shuffle ( bases.begin(), bases.end() );

	bases.insert(bases.end(), nums.begin(), nums.end());

	for (unsigned int index = 0; index < bases.size(); index++)
	{
		m_root = Insert(m_root, bases[index]);
	}

	return m_root;
}