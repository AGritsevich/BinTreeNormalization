
#include<cstdlib>
#include<ctime>
#include <vector>
#include <algorithm>
#include <iostream>
#include <ostream>
#include <functional>
#include <math.h>
#include <fstream>

struct TreeNode // структура для представления узлов дерева
{
	float value;
	unsigned int height;
	TreeNode* left;
	TreeNode* right;

	TreeNode() : left(NULL), right(NULL), height(1){};
	TreeNode(float val) : left(NULL), right(NULL), height(1) { value = val;}
};

class CAVLTree
{
private:
	TreeNode *m_root;
	unsigned int m_nHelpfullElements;
	const float Difference;

private:
	inline unsigned char GetHeight(TreeNode* p);
	inline int bfactor(TreeNode* p);
	void SetHight(TreeNode* p);
	TreeNode* Balancing(TreeNode* p); // балансировка узла p;
	TreeNode* RotateToTheLeft(TreeNode* q); // левый поворот вокруг q;
	TreeNode* RotateToTheRight(TreeNode* p); // правый поворот вокруг p;
	TreeNode* Insert(TreeNode* p, float k); // вставка ключа k в дерево с корнем p;
	TreeNode* GetDippestNod(TreeNode* p); // поиск узла с минимальным ключом в дереве p;
	void Clear(TreeNode* node);
	TreeNode* removemin(TreeNode* p); // удаление узла с минимальным ключом из дерева p;
	TreeNode* remove(TreeNode* p, float k); // удаление ключа k из дерева p;
	int _print_t(TreeNode *tree, int is_left, int offset, int depth, char s[30][255]);

public:
	CAVLTree();
	~CAVLTree(); // write destructor

	TreeNode* generate_tree( std::vector<float> nums);
	void print_t(TreeNode *tree);
};