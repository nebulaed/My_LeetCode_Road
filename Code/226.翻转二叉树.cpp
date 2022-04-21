#include<iostream>
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

// 我的解法：前序遍历，时间O(n) 4 ms，空间O(n) 9.6 MB
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

// 官方解法一：后序遍历，时间O(n) 4 ms，空间O(n) 9.5 MB
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

// 评论解法：BFS，迭代方法，时间O(n) 4 ms，空间O(n) 9.6 MB
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