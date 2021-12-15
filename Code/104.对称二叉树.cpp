#include<iostream>
#include<vector>
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

// �ҵĽⷨһ�����������4 ms��16.2 MB
class Solution {
public:
	bool isSymmetric(TreeNode* root) {
		vector<int> inorder;
		vector<int> depth;
		stack<pair<TreeNode*, int>> stk;
		int cur = 1;
		while (root != nullptr || !stk.empty()) {
			while (root != nullptr) {
				stk.emplace(root, cur);
				root = root->left;
				++cur;
			}
			root = stk.top().first;
			cur = stk.top().second;
			stk.pop();
			inorder.emplace_back(root->val);
			depth.emplace_back(cur);
			root = root->right;
			++cur;
		}
		int left = 0, right = inorder.size() - 1;
		while (left < right) {
			if (inorder[left] != inorder[right] || depth[left] != depth[right]) {
				return false;
			}
			++left;
			--right;
		}
		return true;
	}
};

// �ҵĽⷨ�����ݹ飬ʱ��8 ms���ռ�16.5 MB
class Solution {
public:
	void inorderTraverse(TreeNode* T, vector<pair<int, int>>& inorder, int curDepth) {
		if (T == nullptr) return;
		inorderTraverse(T->left, inorder, curDepth + 1);
		inorder.emplace_back(T->val, curDepth);
		inorderTraverse(T->right, inorder, curDepth + 1);
	}
	bool isSymmetric(TreeNode* root) {
		vector<pair<int, int>> inorder;
		inorderTraverse(root, inorder, 1);
		int left = 0, right = inorder.size() - 1;
		while (left < right) {
			if (inorder[left] != inorder[right]) return false;
			++left;
			--right;
		}
		return true;
	}
};

// �ٷ��ⷨһ���ݹ飬ʱ��O(n) 8 ms���ռ�O(n) 15.9 MB
// ͬ���ƶ�����ָ��p��q������������һ��ʼ��ָ�����p����ʱ��q���ƣ�p����ʱ��q���ƣ�ÿ�μ�鵱ǰp��q�ڵ��ֵ�Ƿ���ȣ���������ж����������Ƿ�Գ�
class Solution {
public:
	bool check(TreeNode* p, TreeNode* q) {
		if (!p && !q) return true;
		if (!p || !q) return false;
		return p->val == q->val && check(p->left, q->right) && check(p->right, q->left);
	}

	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};

// �ٷ��ⷨ����������ʱ��O(n) 4 ms���ռ�O(n) 16.2 MB
class Solution {
public:
	bool check(TreeNode* u, TreeNode* v) {
		// �Ƚ��ȳ������ݽṹ
		queue <TreeNode*> q;
		q.emplace(u);
		q.emplace(v);
		while (!q.empty()) {
			u = q.front();
			q.pop();
			v = q.front();
			q.pop();
			if (!u && !v) continue;
			if ((!u || !v) || (u->val != v->val)) return false;
			q.emplace(u->left);
			q.emplace(v->right);
			q.emplace(u->right);
			q.emplace(v->left);
		}
		return true;
	}

	bool isSymmetric(TreeNode* root) {
		return check(root, root);
	}
};