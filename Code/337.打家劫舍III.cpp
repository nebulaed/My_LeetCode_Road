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

// �ٷ��ⷨһ���������Ķ�̬�滮��ʱ��O(n) 16 ms���ռ�O(2n) = O(n) 28 MB
// ˼·����curSelected(o)��ʾѡ��o�ڵ������£�o�ڵ�������ϱ�ѡ��Ľڵ�����Ȩֵ��
// curNonSelected(o)��ʾ��ѡ��o�ڵ������£�o�ڵ�������ϱ�ѡ��Ľڵ�����Ȩֵ��
// 1.��o��ѡ��ʱ��o�����Һ��Ӷ����ܱ�ѡ�У���o��ѡ������������ϱ�ѡ�е�����Ȩֵ��Ϊo->left��o->right����ѡ�е����Ȩֵ����ӣ���
// curSelected(o) = curNonSelected(o->left) + curNonSelected(o->right)
// 2.��o����ѡ��ʱ��o�����Һ��ӿ���ѡ��Ҳ���Բ�ѡ�С���ô
// curNonSelected(o) = max{curSelected(o->left),curNonSelected(o->left)} + max{curSelected(o->right),curNonSelected(o->right)}
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

// �ٷ��ⷨһ���������Ķ�̬�滮+�������飬ʱ��O(n) 12 ms���ռ�O(n) 21.7 MB
class Solution {
private:
	// array<int, 2>[0]��ʾ��ѡ�е�Ȩֵ�ͣ�array<int, 2>[1]��ʾδ��ѡ�е�Ȩֵ��
	pair<int, int> dfs(TreeNode* T) {
		if (T == nullptr) return { 0, 0 };
		auto leftSum = dfs(T->left);
		auto rightSum = dfs(T->right);
		pair<int, int> sum;
		// ��ǰ�ڵ�T��͵����T->left��T->right���ܱ�͵
		sum.first = T->val + leftSum.second + rightSum.second;
		// ��ǰ�ڵ�Tû��͵����T->left��T->right���Ա�͵���Բ���͵��ȡ���ֵ���
		sum.second = max(leftSum.first, leftSum.second) + max(rightSum.first, rightSum.second);
		return sum;
	}
public:
	int rob(TreeNode* root) {
		auto ret = dfs(root);
		return max(ret.first, ret.second);
	}
};