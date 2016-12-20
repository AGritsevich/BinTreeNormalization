#pragma once

#include<cstdlib>
#include<ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <functional>

struct TreeNodeV2
{
	float value;
	TreeNodeV2 *left;
	TreeNodeV2 *right;

	TreeNodeV2() : left(NULL), right(NULL) {};
	TreeNodeV2(float _val) : left(NULL), right(NULL)
	{
		value = _val;
	}
};

class CSearchBinTreeHelper
{
private:
	TreeNodeV2 *m_root;
	int MAX_N;

public:
	TreeNodeV2* Insert(TreeNodeV2* node, float val);
	TreeNodeV2* Find(TreeNodeV2* node, float val);
	TreeNodeV2* generate_tree( std::vector<float> nums);

	CSearchBinTreeHelper(void);
	~CSearchBinTreeHelper(void);
};
