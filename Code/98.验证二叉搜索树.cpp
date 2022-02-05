#include<iostream>
#include<stack>
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

// 我的解法：中序遍历，时间O(n) 16 ms，空间O(n) 21.2 MB
class Solution {
public:
	bool isValidBST(TreeNode* root) {
		bool start = true;
		int temp = 0;
		stack<TreeNode*> stk;
		while (root != nullptr || !stk.empty()) {
			while (root != nullptr) {
				stk.push(root);
				root = root->left;
			}
			root = stk.top();
			stk.pop();
			if (root->val > temp || start) {
				temp = root->val;
				start = false;
			}
			else {
				return false;
			}
			root = root->right;
		}
		return true;
	}
};

// 官方解法二：中序遍历，时间O(n) 12 ms，空间O(n) 21.1 MB
class Solution {
public:
	bool isValidBST(TreeNode* root) {
		stack<TreeNode*> stack;
		long long inorder = (long long)INT_MIN - 1;

		while (!stack.empty() || root != nullptr) {
			while (root != nullptr) {
				stack.push(root);
				root = root->left;
			}
			root = stack.top();
			stack.pop();
			// 如果中序遍历得到的节点的值小于等于前一个 inorder，说明不是二叉搜索树
			if (root->val <= inorder) {
				return false;
			}
			inorder = root->val;
			root = root->right;
		}
		return true;
	}
};

// 官方解法一：递归，时间O(n) 12 ms，空间O(n) 21 MB
class Solution {
public:
	bool helper(TreeNode* root, long long lower, long long upper) {
		if (root == nullptr) return true;
		if (root->val <= lower || root->val >= upper) return false;
		return helper(root->left, lower, root->val) && helper(root->right, root->val, upper);
	}
	bool isValidBST(TreeNode* root) {
		return helper(root, LONG_MIN, LONG_MAX);
	}
};

int main() {
	TreeNode* left2 = new TreeNode(3);
	TreeNode* right1 = new TreeNode(2, left2, nullptr);
	TreeNode* root = new TreeNode(1, nullptr, right1);

	Solution s;
	bool ret = s.isValidBST(root);

	cout << ret << endl;

	delete left2, right1, root;

	system("pause");
	return 0;
}