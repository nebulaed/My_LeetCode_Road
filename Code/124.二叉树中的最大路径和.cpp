#include<iostream>
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

// �ҵĽⷨ�ο����ۣ�ʱ�� 20 ms���ռ� 27.7 MB
class Solution {
private:
	int MINIMUM = -1e9;
	int maxSum1 = MINIMUM;
public:
	int postorderTraverse(TreeNode* T) {
		if (T == nullptr) return MINIMUM;
		int left = postorderTraverse(T->left);
		int right = postorderTraverse(T->right);
		maxSum1 = max({ maxSum1, T->val + left + right, left, right });
		return max({ T->val, T->val + left, T->val + right });
	}
	int maxPathSum(TreeNode* root) {
		int maxSum2 = postorderTraverse(root);
		return maxSum1 > maxSum2 ? maxSum1 : maxSum2;
	}
};

// �ٷ��ⷨһ���ݹ飬ʱ��O(n) 16 ms���ռ�O(n) 26.9 MB
class Solution {
private:
	int maxSum = INT_MIN;
public:
	int postorderTraverse(TreeNode* T) {
		if (T == nullptr) return 0;
		int left = max(postorderTraverse(T->left), 0);
		int right = max(postorderTraverse(T->right), 0);
		int priceNewpath = T->val + left + right;
		maxSum = max(maxSum, priceNewpath);
		return T->val + max(left, right);
	}
	int maxPathSum(TreeNode* root) {
		postorderTraverse(root);
		return maxSum;
	}
};