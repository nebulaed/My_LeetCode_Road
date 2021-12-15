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

// 我的解法一：前序遍历，时间 8 ms，空间 12.2 MB
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return {};
		vector<vector<int>> ret;
		vector<int> preorder, depth;
		stack<pair<TreeNode*, int>> stk;
		int curDepth = 1;
		stk.emplace(root, curDepth);
		while (!stk.empty()) {
			root = stk.top().first;
			curDepth = stk.top().second;
			stk.pop();
			preorder.emplace_back(root->val);
			depth.emplace_back(curDepth);
			if (root->right) {
				stk.emplace(root->right, curDepth + 1);
			}
			if (root->left) {
				stk.emplace(root->left, curDepth + 1);
			}
		}
		int nums = preorder.size();
		for (int i = 0; i < nums; ++i) {
			if (ret.size() < depth[i]) ret.resize(depth[i]);
			ret[depth[i] - 1].emplace_back(preorder[i]);
		}
		return ret;
	}
};

// 我的解法二：中序遍历，时间 4 ms，空间 12.4 MB
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return {};
		vector<vector<int>> ret;
		vector<int> inorder, depth;
		stack<pair<TreeNode*, int>> stk;
		int curDepth = 1;
		while (root != nullptr || !stk.empty()) {
			while (root != nullptr) {
				stk.emplace(root, curDepth);
				root = root->left;
				++curDepth;
			}
			root = stk.top().first;
			curDepth = stk.top().second;
			stk.pop();
			inorder.emplace_back(root->val);
			depth.emplace_back(curDepth);
			root = root->right;
			++curDepth;
		}
		int nums = inorder.size();
		for (int i = 0; i < nums; ++i) {
			if (ret.size() < depth[i]) ret.resize(depth[i]);
			ret[depth[i] - 1].emplace_back(inorder[i]);
		}
		return ret;
	}
};

// 我的解法三：后序遍历，时间 0 ms，空间 12.1 MB
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return {};
		vector<vector<int>> ret;
		vector<int> postorder, depth;
		stack<pair<TreeNode*, int>> stk;
		int curDepth = 1;
		stk.emplace(root, curDepth);
		while (!stk.empty()) {
			root = stk.top().first;
			curDepth = stk.top().second;
			stk.pop();
			postorder.emplace_back(root->val);
			depth.emplace_back(curDepth);
			if (root->left) {
				stk.emplace(root->left, curDepth + 1);
			}
			if (root->right) {
				stk.emplace(root->right, curDepth + 1);
			}
		}
		int nums = postorder.size();
		for (int i = nums - 1; i >= 0; --i) {
			if (ret.size() < depth[i]) ret.resize(depth[i]);
			ret[depth[i] - 1].emplace_back(postorder[i]);
		}
		return ret;
	}
};

// 官方解法一：广度优先搜索BFS，时间O(n) 4 ms，空间O(n) 12.1 MB
class Solution {
public:
	vector<vector<int>> levelOrder(TreeNode* root) {
		if (!root) return {};
		vector<vector<int>> ret;

		queue<TreeNode*> q;
		q.emplace(root);
		while (!q.empty()) {
			int currentLevelSize = q.size();
			ret.emplace_back(vector<int>());
			for (int i = 1; i <= currentLevelSize; ++i) {
				auto node = q.front();
				q.pop();
				if (node->left) q.emplace(node->left);
				if (node->right) q.emplace(node->right);
			}
		}
		return ret;
	}
};