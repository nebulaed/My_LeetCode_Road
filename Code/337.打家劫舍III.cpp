#include<iostream>
#include<unordered_map>
#include<algorithm>
using namespace std;

// �������ṹ
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
		// ��ǰ�ڵ�T��͵����T->left��T->right���ܱ�͵
		curSelected[T] = T->val + curNonSelected[T->left] + curNonSelected[T->right];
		// ��ǰ�ڵ�Tû��͵����T->left��T->right���Ա�͵���Բ���͵��ȡ���ֵ���
		curNonSelected[T] = max(curSelected[T->left], curNonSelected[T->left]) + max(curSelected[T->right], curNonSelected[T->right]);
	}
public:
	int rob(TreeNode* root) {
		dfs(root);
		return max(curSelected[root], curNonSelected[root]);
	}
};