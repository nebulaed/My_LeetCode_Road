#include<iostream>
#include<vector>
#include<stack>
#include<queue>
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

// 我的解法一：中序遍历，4 ms，16.2 MB
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

// 我的解法二：递归，时间8 ms，空间16.5 MB
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

// 官方解法一：递归，时间O(n) 8 ms，空间O(n) 15.9 MB
// 同步移动两个指针p和q遍历整棵树，一开始都指向根，p右移时，q左移，p左移时，q右移，每次检查当前p和q节点的值是否相等，若相等再判断左右子树是否对称
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

// 官方解法二：迭代，时间O(n) 4 ms，空间O(n) 16.2 MB
class Solution {
public:
	bool check(TreeNode* u, TreeNode* v) {
		// 先进先出的数据结构
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