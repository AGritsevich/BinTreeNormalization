// BinTreeTestNormalization.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "AVL_Tree.h"





int _tmain(int argc, TCHAR* argv[])
{
	srand (static_cast <unsigned> (time(0)));

	std::vector<float> nums;

	for (int i = 0; i < 8; i++)
	{
		float r = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));
		nums.push_back(r);
		std::cout << r << " ";
	}
	std::cout << "\n\n\n";

	CAVLTree sercher;

	TreeNode *root = sercher.generate_tree(nums);

	sercher.print_t(root);

	return 0;
}