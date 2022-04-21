#include<iostream>
#include<algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr) : val(val), left(left), right(right) {}
};

// 我的解法：后序遍历，时间 O(n) 16 ms 24.49%，空间 O(n) 20.4 MB 37.77%
class Solution {
private:
    int dfs(TreeNode* T) {
        if (!T) return 0;
        int leftDepth = dfs(T->left), rightDepth = dfs(T->right);
        if (leftDepth == -1 || rightDepth == -1 || abs(rightDepth - leftDepth) > 1) {
            return -1;
        }
        return max(leftDepth, rightDepth) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        return dfs(root) != -1;
    }
};

// 我的解法+评论优化：后序遍历，左子树不平衡时不需要遍历右子树，时间 O(n) 24 ms 5.27%，空间 O(n) 20.1 MB 98.90%
class Solution {
private:
    int dfs(TreeNode* T) {
        if (!T) return 0;
        int leftDepth = dfs(T->left), rightDepth = leftDepth == -1 ? -1 : dfs(T->right);
        if (leftDepth == -1 || rightDepth == -1 || abs(rightDepth - leftDepth) > 1) {
            return -1;
        }
        return max(leftDepth, rightDepth) + 1;
    }
public:
    bool isBalanced(TreeNode* root) {
        return dfs(root) != -1;
    }
};