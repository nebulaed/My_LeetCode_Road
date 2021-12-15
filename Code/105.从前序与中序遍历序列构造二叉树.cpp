#include<iostream>
#include<unordered_map>
#include<stack>
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

// ��������������
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

// ��������������
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

// ���ǰ���������
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

// �ٷ��ⷨһ���ݹ飬ʱ��O(n) 16 ms���ռ�O(n) 25.7 MB
class Solution {
private:
	// �������������ֵ-�����Ķ�Ӧ��ϵ
	unordered_map<int, int> index;
public:
	TreeNode* createTree(const vector<int>& preorder, const vector<int>& inorder, int preorder_left, int preorder_right, int inorder_left, int inorder_right) {
		if (preorder_left > preorder_right) {
			return nullptr;
		}

		// ǰ������е�һ���ڵ���Ǹ��ڵ�
		int preorder_root = preorder_left;
		// ����������ж�λ���ڵ�
		int inorder_root = index[preorder[preorder_root]];

		// �Ƚ������ڵ�
		TreeNode* root = new TreeNode(preorder[preorder_root]);
		// �õ��������еĽڵ���Ŀ
		int sizeLeftSubTree = inorder_root - inorder_left;
		// �ݹ�ع����������������ӵ����ڵ�
		// ���������[����߽�+1��ʼ��sizeLeftSubTree]��Ԫ�ؾͶ�Ӧ�����������[����߽翪ʼ�����ڵ�λ��-1]��Ԫ�أ�������������
		root->left = createTree(preorder, inorder, preorder_left + 1, preorder_left + sizeLeftSubTree, inorder_left, inorder_root - 1);
		// �ݹ�ع����������������ӵ����ڵ�
		// ���������[����߽�+1+�������ڵ���Ŀ ��ʼ�� �ұ߽�]��Ԫ�ؾͶ�Ӧ�����������[�Ӹ��ڵ�λ��+1 ���ұ߽�]��Ԫ�أ�������������
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

// �ٷ��ⷨ����������ʱ��O(n) 20 ms���ռ�O(h)�ΪO(n) 24.8 MB
// ��һ��ջ��һ��ָ�븨�����ж������Ĺ��죬��ʼʱջ�д���˸��ڵ�(ǰ������ĵ�һ���ڵ�)��ָ��ָ����������ĵ�һ���ڵ�
// ����ö��ǰ������г��˵�һ���ڵ������ÿһ���ڵ㣬���indexǡ��ָ��ջ���ڵ㣬��ô���ϵص���ջ���ڵ㲢�����ƶ�index��������ǰ�ڵ���Ϊ���һ�������Ľڵ���Ҷ��ӣ����index��ջ���ڵ㲻ͬ�����Ƕ��Ὣ��ǰ�Ľڵ���ջ
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