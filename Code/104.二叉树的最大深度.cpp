#include<iostream>
#include<stack>
#include<queue>
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

// �ҵĽⷨһ���ݹ�+���������0 ms��18.3 MB
class Solution {
public:
	void postOrderTraverse(TreeNode* T, int depth, int& maxdepth) {
		if (T == nullptr) return;
		postOrderTraverse(T->left, depth + 1, maxdepth);
		postOrderTraverse(T->right, depth + 1, maxdepth);
		maxdepth = depth > maxdepth ? depth : maxdepth;
	}

	int maxDepth(TreeNode* root) {
		int maxdepth = 0;
		postOrderTraverse(root, 1, maxdepth);
		return maxdepth;
	}
};

// �ҵĽⷨ��������+���������12 ms��18.6 MB
class Solution {
public:
	int maxDepth(TreeNode* root) {
		int maxdepth = 0;
		if (!root) return maxdepth;
		stack<pair<TreeNode*, int>> stk;
		int curdepth = 1;
		stk.emplace(root, curdepth);
		while (!stk.empty()) {
			root = stk.top().first;
			curdepth = stk.top().second;
			stk.pop();
			maxdepth = curdepth > maxdepth ? curdepth : maxdepth;
			if (root->left) {
				stk.emplace(root->left, curdepth + 1);
			}
			if (root->right) {
				stk.emplace(root->right, curdepth + 1);
			}
		}
		return maxdepth;
	}
};

// �ҵĽⷨ�� = �ٷ��ⷨһ���������������ʱ��O(n) 12 ms���ռ�O(height) 18.3 MB
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) return 0;
		int num1 = maxDepth(root->left), num2 = maxDepth(root->right);
		return (num1 > num2 ? num1 : num2) + 1;
	}
};

// �ٷ��ⷨ�����������������ʱ��O(n) 8 ms���ռ� �ΪO(n) 18.5 MB
class Solution {
public:
	int maxDepth(TreeNode* root) {
		if (root == nullptr) return 0;
		queue<TreeNode*> Q;
		Q.emplace(root);
		int ans = 0;
		while (!Q.empty()) {
			int sz = Q.size();
			while (sz > 0) {
				TreeNode* node = Q.front();
				Q.pop();
				if (node->left) Q.emplace(node->left);
				if (node->right) Q.emplace(node->right);
				sz -= 1;
			}
			ans += 1;
		}
		return ans;
	}
};