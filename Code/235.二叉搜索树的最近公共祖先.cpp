#include<cstdio>
#include<algorithm>
using namespace std;

// 二叉树结构
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 我的解法：时间 O(n) 24 ms 90.63%，空间 O(1) 22.7 MB 74.37%
class Solution {
private:
    TreeNode *dfs(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (p->val <= root->val && root->val <= q->val) {
            return root;
        } else if (p->val < root->val && q->val < root->val) {
            return dfs(root->left, p, q);
        } else {
            return dfs(root->right, p, q);
        }
    }

public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (p->val > q->val) swap(p, q);
        return dfs(root, p, q);
    }
};

// 官方解法：一次遍历，时间 O(n) 24 ms 90.63%，空间 O(1) 22.6 MB 91.56%
class Solution {
public:
    TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        TreeNode *ancestor = root;
        while (true) {
            if (p->val < ancestor->val && q->val < ancestor->val) {
                ancestor = ancestor->left;
            } else if (p->val > ancestor->val && q->val > ancestor->val) {
                ancestor = ancestor->right;
            } else break;
        }
        return ancestor;
    }
};

int main() {
    TreeNode* node3 = new TreeNode(3), *node5 = new TreeNode(5), *node4 = new TreeNode(4, node3, node5), *node0 = new TreeNode(0), *node2 = new TreeNode(2, node0, node4), *node7 = new TreeNode(7), *node9 = new TreeNode(9), *node8 = new TreeNode(8, node7, node9), *node6 = new TreeNode(6, node2, node8);

    Solution sol;
    printf("%d", sol.lowestCommonAncestor(node6, node2, node4)->val);
}