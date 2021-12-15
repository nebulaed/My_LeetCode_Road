#include<iostream>
#include<unordered_map>
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

// 输出层序遍历序列
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

// 输出中序遍历序列
class Solution3 {
public:
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		stack<TreeNode*> stk;
		while (root != nullptr || !stk.empty()) {
			while (root != nullptr) {
				stk.push(root);
				root = root->left;
			}
			root = stk.top();
			stk.pop();
			ret.emplace_back(root->val);
			root = root->right;
		}
		return ret;
	}
};

// 输出前序遍历序列
class Solution4 {
public:
	vector<int> preorderTraversal(TreeNode* root) {
		if (!root) return {};
		vector<int> preorder;
		stack<TreeNode*> stk;
		int curDepth = 1;
		stk.emplace(root);
		while (!stk.empty()) {
			root = stk.top();
			stk.pop();
			preorder.emplace_back(root->val);
			if (root->right) {
				stk.emplace(root->right);
			}
			if (root->left) {
				stk.emplace(root->left);
			}
		}
		return preorder;
	}
};

// 官方解法一：递归，时间O(n) 16 ms，空间O(n) 25.7 MB
class Solution {
private:
	// 中序遍历序列中值-索引的对应关系
	unordered_map<int, int> index;
public:
	TreeNode* createTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
		if (preorder_left > preorder_right) {
			return nullptr;
		}

		// 前序遍历中第一个节点就是根节点
		int preorder_root = preorder_left;
		// 在中序遍历中定位根节点
		int inorder_root = index[preorder[preorder_root]];

		// 先建立根节点
		TreeNode* root = new TreeNode(preorder[preorder_root]);
		// 得到左子树中的节点数目
		int sizeLeftSubTree = inorder_root - inorder_left;
		// 递归地构造左子树，并连接到根节点
		// 先序遍历中[从左边界+1开始的sizeLeftSubTree]个元素就对应了中序遍历中[从左边界开始到根节点位置-1]的元素，都属于左子树
		root->left = createTree(preorder, inorder, preorder_left + 1, preorder_left + sizeLeftSubTree, inorder_left, inorder_root - 1);
		// 递归地构造右子树，并连接到根节点
		// 先序遍历中[从左边界+1+左子树节点数目 开始到 右边界]的元素就对应了中序遍历中[从根节点位置+1 到右边界]的元素，都属于右子树
		root->right = createTree(preorder, inorder, preorder_left + sizeLeftSubTree + 1, preorder_right, inorder_root + 1, inorder_right);
		return root;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int n = preorder.size();
		for (int i = 0; i < n; ++i) {
			index[inorder[i]] = i;
		}
		return createTree(preorder, inorder, 0, n - 1, 0, n - 1);
	}
};

// 官方解法二：迭代，时间O(n) 20 ms，空间O(h)最坏为O(n) 24.8 MB
// 用一个栈和一个指针辅助进行二叉树的构造，初始时栈中存放了根节点(前序遍历的第一个节点)，指针指向中序遍历的第一个节点
// 依次枚举前序遍历中除了第一个节点以外的每一个节点，如果index恰好指向栈顶节点，那么不断地弹出栈顶节点并向右移动index，并将当前节点作为最后一个弹出的节点的右儿子；如果index和栈顶节点不同，我们都会将当前的节点入栈
class Solution {
public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		if (!preorder.size()) return nullptr;
		TreeNode* root = new TreeNode(preorder[0]);
		stack<TreeNode*> stk;
		stk.emplace(root);
		int inorderIndex = 0;
		for (int i = 1; i < preorder.size(); ++i) {
			int preorderVal = preorder[i];
			TreeNode* node = stk.top();
			if (node->val != inorder[inorderIndex]) {
				node->left = new TreeNode(preorderVal);
				stk.emplace(node->left);
			}
			else {
				while (!stk.empty() && stk.top()->val == inorder[inorderIndex]) {
					node = stk.top();
					stk.pop();
					++inorderIndex;
				}
				node->right = new TreeNode(preorderVal);
				stk.emplace(node->right);
			}
		}
		return root;
	}
};



int main() {

	TreeNode* node3 = new TreeNode(15);
	TreeNode* node4 = new TreeNode(7);
	TreeNode* node2 = new TreeNode(20, node3, node4);
	TreeNode* node1 = new TreeNode(9);
	TreeNode* node0 = new TreeNode(3, node1, node2);

	Solution4 s4;
	vector<int> preorder = s4.preorderTraversal(node0);
	Solution3 s3;
	vector<int> inorder = s3.inorderTraversal(node0);

	Solution s;
	TreeNode* root = s.buildTree(preorder, inorder);

	Solution2 s2;
	vector<vector<int>> levelorder = s2.levelOrder(root);

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