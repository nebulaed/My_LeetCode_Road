#include<iostream>
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

// �ҵĽⷨ��ǰ�������ʱ��O(n) 4 ms���ռ�O(n) 9.6 MB
class Solution {
private:
	void traverseTree(TreeNode* ptr) {
		if (!ptr) return;
		swap(ptr->left, ptr->right);
		traverseTree(ptr->left);
		traverseTree(ptr->right);
	}
public:
	TreeNode* invertTree(TreeNode* root) {
		TreeNode* ptr = root;
		traverseTree(ptr);
		return root;
	}
};

// �ٷ��ⷨһ�����������ʱ��O(n) 4 ms���ռ�O(n) 9.5 MB
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) return root;
		TreeNode* left = invertTree(root->left);
		TreeNode* right = invertTree(root->right);
		root->left = right;
		root->right = left;
		return root;
	}
};

// ���۽ⷨ��BFS������������ʱ��O(n) 4 ms���ռ�O(n) 9.6 MB
class Solution {
public:
	TreeNode* invertTree(TreeNode* root) {
		if (root == nullptr) return root;
		queue<TreeNode*> q;
		q.emplace(root);
		while (!q.empty()) {
			size_t size = q.size();
			for (size_t i = 0; i < size; ++i) {
				TreeNode* temp = q.front();
				q.pop();
				if (temp->left) q.emplace(temp->left);
				if (temp->right) q.emplace(temp->right);
				TreeNode* tempNode = temp->left;
				temp->left = temp->right;
				temp->right = tempNode;
			}
		}
		return root;
	}
};