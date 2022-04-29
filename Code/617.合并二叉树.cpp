struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 我的解法：先序遍历，时间 O(max(m, n)) 32 ms 76.44%，空间 O(max(m, n)) 31.3 MB 98.50%
class Solution {
private:
    void dfs(TreeNode *root1, TreeNode *root2) {
        if (!root1 || !root2) return;
        root1->val += root2->val;
        if (root1->left == nullptr && root2->left != nullptr) {
            root1->left = new TreeNode(0);
        }
        if (root1->right == nullptr && root2->right != nullptr) {
            root1->right = new TreeNode(0);
        }
        dfs(root1->left, root2->left);
        dfs(root1->right, root2->right);
    }

public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr) return root2;
        dfs(root1, root2);
        return root1;
    }
};

// 官方评论解法：dfs不修改原树，时间 O(max(m, n)) 44 ms 15.57%，空间 O(max(m, n)) 33.4 MB 5.7%
class Solution {
public:
    TreeNode *mergeTrees(TreeNode *root1, TreeNode *root2) {
        if (root1 == nullptr && root2 == nullptr)
            return nullptr;
        int a = root1 ? root1->val : 0;
        int b = root2 ? root2->val : 0;
        TreeNode *merged = new TreeNode(a + b);
        merged->left = mergeTrees(root1 ? root1->left : nullptr, root2 ? root2->left : nullptr);
        merged->right = mergeTrees(root1 ? root1->right : nullptr, root2 ? root2->right : nullptr);
        return merged;
    }
};