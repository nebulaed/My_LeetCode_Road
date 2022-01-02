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

// 官方解法一：二叉树的动态规划，时间O(n) 16 ms，空间O(2n) = O(n) 28 MB
// 思路：用curSelected(o)表示选择o节点的情况下，o节点的子树上被选择的节点的最大权值和
// curNonSelected(o)表示不选择o节点的情况下，o节点的子树上被选择的节点的最大权值和
// 1.当o被选中时，o的左右孩子都不能被选中，故o被选中情况下子树上被选中点的最大权值和为o->left和o->right不被选中的最大权值和相加，即
// curSelected(o) = curNonSelected(o->left) + curNonSelected(o->right)
// 2.当o不被选中时，o的左右孩子可以选中也可以不选中。那么
// curNonSelected(o) = max{curSelected(o->left),curNonSelected(o->left)} + max{curSelected(o->right),curNonSelected(o->right)}
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

// 官方解法一：二叉树的动态规划+滚动数组，时间O(n) 12 ms，空间O(n) 21.7 MB
class Solution {
private:
	// array<int, 2>[0]表示被选中的权值和，array<int, 2>[1]表示未被选中的权值和
	pair<int, int> dfs(TreeNode* T) {
		if (T == nullptr) return { 0, 0 };
		auto leftSum = dfs(T->left);
		auto rightSum = dfs(T->right);
		pair<int, int> sum;
		// 当前节点T被偷，则T->left和T->right不能被偷
		sum.first = T->val + leftSum.second + rightSum.second;
		// 当前节点T没被偷，则T->left，T->right可以被偷可以不被偷，取最大值情况
		sum.second = max(leftSum.first, leftSum.second) + max(rightSum.first, rightSum.second);
		return sum;
	}
public:
	int rob(TreeNode* root) {
		auto ret = dfs(root);
		return max(ret.first, ret.second);
	}
};