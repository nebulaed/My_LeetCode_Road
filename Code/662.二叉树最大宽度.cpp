#include<cstdio>
#include<deque>
#include<queue>
#include<algorithm>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// 我的解法：超时
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        if (!root) return 0;
        int maxLen = 1;
        deque<TreeNode*> q;
        q.emplace_back(root);
        while (!q.empty()) {
            int currLevelSize = q.size(), len = 0, nullLen1 = 0, nullLen2 = 0;
            while (nullLen1 < currLevelSize && !q[nullLen1]) {
                ++nullLen1;
            }
            if (nullLen1 == currLevelSize) break;
            while (nullLen2 < currLevelSize && !q[currLevelSize - nullLen2 - 1]) {
                ++nullLen2;
            }
            maxLen = max(maxLen, currLevelSize - nullLen1 - nullLen2);
            for (int i = 0; i < currLevelSize; ++i) {
                TreeNode* node = q.front();
                q.pop_front();
                if (node) {
                    if (node->left) q.emplace_back(node->left);
                    else q.emplace_back(nullptr);
                    if (node->right) q.emplace_back(node->right);
                    else q.emplace_back(nullptr);
                }
                else {
                    q.emplace_back(nullptr);
                    q.emplace_back(nullptr);
                }
            }
        }
        return maxLen;
    }
};

// 我的解法参考官方解法一：BFS，时间 8 ms 71.41%，空间 16.9 MB 63.74%
class Solution {
public:
    int widthOfBinaryTree(TreeNode* root) {
        using ull = unsigned long long;
        if (!root) return 0;
        ull maxLen = 1;
        queue<pair<TreeNode*, ull>> q;
        q.emplace(root, 0);
        while (!q.empty()) {
            int currLevelSize = q.size();
            ull leftPos = ULLONG_MAX, rightPos = 0;
            for (int i = 0; i < currLevelSize; ++i) {
                const auto [node, pos] = q.front();
                leftPos = min(leftPos, pos);
                rightPos = max(rightPos, pos);
                q.pop();
                if (node->left) q.emplace(node->left, pos * 2);
                if (node->right) q.emplace(node->right, pos * 2 + 1);
            }
            maxLen = max(maxLen, rightPos - leftPos + 1);
        }
        return static_cast<int>(maxLen);
    }
};

int main() {

    TreeNode* node6 = new TreeNode(6);
    TreeNode* node7 = new TreeNode(7);
    TreeNode* node5 = new TreeNode(5, node6, nullptr);
    TreeNode* node9 = new TreeNode(9, node7, nullptr);
    TreeNode* node3 = new TreeNode(3, node5, nullptr);
    TreeNode* node2 = new TreeNode(2, nullptr, node9);
    TreeNode* node1 = new TreeNode(1, node3, node2);

    Solution sol;

    int ret = sol.widthOfBinaryTree(node1);

    printf("%d\n", ret);

    return 0;
}