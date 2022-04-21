#include<algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left, * right;
    TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr) : val(val), left(left), right(right) {}
};

// 我的解法：后序遍历，时间 O(n) 0 ms 100%，空间 O(h), h为二叉树高度，19.8 MB 37.71%
class Solution {
private:
    int dfs(TreeNode* T, int& diameter) {
        if (!T) return 0;
        int leftLen = dfs(T->left, diameter), rightLen = dfs(T->right, diameter);
        diameter = max(leftLen + rightLen, diameter);
        return max(leftLen, rightLen) + 1;
    }
public:
    int diameterOfBinaryTree(TreeNode* root) {
        int diameter = 0;
        dfs(root, diameter);
        return diameter;
    }
};