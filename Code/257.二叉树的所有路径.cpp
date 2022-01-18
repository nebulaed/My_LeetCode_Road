#include<iostream>
#include<string>
#include<vector>
using std::vector;
using std::string;
using std::to_string;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// �ҵĽⷨ��DFS+���ݣ�ʱ�� 8 ms ���ռ� 13 MB
class Solution {
private:
	vector<string> ret;
	void preOrdTraverse(TreeNode* root, string cur) {
		bool leftNonEmpty = root->left, rightNonEmpty = root->right;
		if (!leftNonEmpty && !rightNonEmpty) {
			ret.emplace_back(cur);
		}
		if (leftNonEmpty) {
			size_t delPoint = cur.size();
			string curVal = to_string(root->left->val);
			size_t delSize = 2 + curVal.size();
			cur += "->" + curVal;
			preOrdTraverse(root->left, cur);
			cur.erase(delPoint, delSize);
		}
		if (rightNonEmpty) {
			size_t delPoint = cur.size();
			string curVal = to_string(root->right->val);
			size_t delSize = 2 + curVal.size();
			cur += "->" + curVal;
			preOrdTraverse(root->right, cur);
			cur.erase(delPoint, delSize);
		}
	}
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		if (!root) return {};
		string cur = to_string(root->val);
		preOrdTraverse(root, cur);
		return ret;
	}
};

// �ҵĽⷨ�ο��ٷ��𰸣�DFS�����ݣ�ʱ�� 4 ms 73.08%���ռ� 12.9 MB 20.08%
class Solution {
private:
	vector<string> ret;
	void preOrdTraverse(TreeNode* root, string cur) {
		if (!root) {
			return;
		}
		cur += to_string(root->val);
		if (!root->left && !root->right) {
			ret.emplace_back(cur);
		}
		else {
			cur += "->";
			preOrdTraverse(root->left, cur);
			preOrdTraverse(root->right, cur);
		}
	}
public:
	vector<string> binaryTreePaths(TreeNode* root) {
		if (!root) return {};
		preOrdTraverse(root, "");
		return ret;
	}
};