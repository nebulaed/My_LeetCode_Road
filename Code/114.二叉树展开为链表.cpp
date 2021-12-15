#include<iostream>
#include<stack>
#include<vector>
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

class Solution2 {
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

// 我的解法1：迭代+先序遍历 时间 12 ms，空间 12.7 MB
class Solution {
public:
	void flatten(TreeNode* root) {
		if (!root) return;
		TreeNode* newroot = new TreeNode(0);
		TreeNode *temp1 = newroot, *temp2 = root;
		stack<TreeNode*> stk;
		stk.emplace(temp2);
		while (!stk.empty()) {
			temp2 = stk.top();
			stk.pop();
			if (temp2) {
				temp1->right = new TreeNode(temp2->val);
			}
			temp1 = temp1->right;
			if (temp2->right) {
				stk.emplace(temp2->right);
			}
			if (temp2->left) {
				stk.emplace(temp2->left);
			}
		}
		root->left = nullptr;
		root->right = newroot->right->right;
	}
};

// 我的解法2：寻找前驱节点，时间O(n) 4 ms，空间O(1) 12.4 MB
class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		TreeNode* cur = root;
		TreeNode* prev = nullptr;
		while (cur->left != nullptr || cur->right != nullptr) {
			if (cur->left != nullptr) {
				prev = cur->left;
				while (prev->left != nullptr || prev->right != nullptr) {
					if (prev->right != nullptr) {
						prev = prev->right;
					}
					else {
						prev = prev->left;
					}
				}
				prev->right = cur->right;
				cur->right = cur->left;
				cur->left = nullptr;
			}
			cur = cur->right;
		}
	}
};

// 官方解法1：递归+先序遍历，时间O(n) 12 ms，空间O(n) 12.9 MB
class Solution {
public:
	void preorderTraverse(TreeNode* root, vector<TreeNode*>& l) {
		if (root == nullptr) {
			return;
		}
		l.emplace_back(root);
		preorderTraverse(root->left, l);
		preorderTraverse(root->right, l);
	}
	void flatten(TreeNode* root) {
		vector<TreeNode*> l;
		preorderTraverse(root, l);
		int n = l.size();
		for (int i = 1; i < n; ++i) {
			TreeNode *prev = l[i - 1], *cur = l[i];
			prev->left = nullptr;
			prev->right = cur;
		}
	}
};

// 官方解法2：迭代+前序遍历，时间O(n) 4 ms，空间O(n) 12.7 MB
class Solution {
public:
	void flatten(TreeNode* root) {
		vector<TreeNode*> v;
		stack<TreeNode*> stk;
		TreeNode* node = root;
		while (node != nullptr || !stk.empty()) {
			while (node != nullptr) {
				v.emplace_back(node);
				stk.emplace(node);
				node = node->left;
			}
			node = stk.top();
			stk.pop();
			node = node->right;
		}
		int n = v.size();
		for (int i = 1; i < n; ++i) {
			TreeNode *prev = v[i - 1], *cur = v[i];
			prev->left = nullptr;
			prev->right = cur;
		}
	}
};

// 官方解法三：前序遍历和展开同步进行，时间O(n) 8 ms，空间O(n) 12.6 MB
class Solution {
public:
	void flatten(TreeNode* root) {
		if (root == nullptr) return;
		stack<TreeNode*> stk;
		stk.emplace(root);
		TreeNode* prev = nullptr;
		while (!stk.empty()) {
			TreeNode* cur = stk.top();
			stk.pop();
			if (prev != nullptr) {
				prev->left = nullptr;
				prev->right = cur;
			}
			if (cur->right != nullptr) {
				stk.emplace(cur->right);
			}
			if (cur->left != nullptr) {
				stk.emplace(cur->left);
			}
			prev = cur;
		}
	}
};

// 官方解法四：寻找前驱节点，时间O(n) 4 ms，空间O(1) 12.3MB
class Solution {
public:
	void flatten(TreeNode* root) {
		TreeNode* curr = root;
		while (curr != nullptr) {
			if (curr->left != nullptr) {
				auto next = curr->left;
				auto predecessor = next;
				while (predecessor->right != nullptr) {
					predecessor = predecessor->right;
				}
				predecessor->right = curr->right;
				curr->left = nullptr;
				curr->right = next;
			}
			curr = curr->right;
		}
	}
};

int main() {

	TreeNode* node5 = new TreeNode(6);
	TreeNode* node4 = new TreeNode(4);
	TreeNode* node3 = new TreeNode(3);
	TreeNode* node2 = new TreeNode(5,nullptr,node5);
	TreeNode* node1 = new TreeNode(2,node3,node4);
	TreeNode* node0 = new TreeNode(1, node1, node2);

	Solution s;
	s.flatten(node0);

	Solution2 s2;
	vector<vector<int>> levelorder = s2.levelOrder(node0);

	cout << "[";
	for (auto it = levelorder.begin(); it != levelorder.end(); ++it) {
		cout << "[";
		for (auto it2 = (*it).begin(); it2 != (*it).end(); ++it2) {
			cout << *it2;
			if (it2 != (*it).end() - 1) cout << ",";
		}
		cout << "]";
		if (it != levelorder.end() - 1) cout << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}