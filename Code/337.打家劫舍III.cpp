#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

// 二叉树结构
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
private:
	unordered_map<TreeNode*, int> curSelected, curNonSelected;

	void dfs(TreeNode* T) {
		if (T == nullptr) return;
		dfs(T->left);
		dfs(T->right);
		// 当前节点T被偷，则T->left和T->right不能被偷
		curSelected[T] = T->val + curNonSelected[T->left] + curNonSelected[T->right];
		// 当前节点T没被偷，则T->left，T->right可以被偷可以不被偷，取最大值情况
		curNonSelected[T] = max(curSelected[T->left], curNonSelected[T->left]) + max(curSelected[T->right], curNonSelected[T->right]);
	}
public:
	int rob(TreeNode* root) {
		dfs(root);
		return max(curSelected[root], curNonSelected[root]);
	}
};