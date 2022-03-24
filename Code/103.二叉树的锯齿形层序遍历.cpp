#include<vector>
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

// 我的解法：时间 4 ms 59.00%，空间 11.7 MB 81.56%
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        queue<TreeNode*> q;
        q.emplace(root);
        int level = 0;
        while (!q.empty()) {
            int currLevelSize = q.size();
            ret.emplace_back(vector<int>());
            while (currLevelSize--) {
                TreeNode* node = q.front();
                ret[level].emplace_back(node->val);
                q.pop();
                if (node->left) q.emplace(node->left);
                if (node->right) q.emplace(node->right);
            }
            if (level & 1) reverse(ret[level].begin(), ret[level].end());
            ++level;
        }
        return ret;
    }
};

// 我的解法参考官方解法：采用双端队列，时间 0 ms 100%，空间 11.8 MB 53.51%
class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        if (!root) return {};
        vector<vector<int>> ret;
        deque<TreeNode*> q;
        q.emplace_back(root);
        int level = 0;
        while (!q.empty()) {
            int currLevelSize = q.size();
            ret.emplace_back(vector<int>());
            while (currLevelSize--) {
                TreeNode* node = nullptr;
                // 奇数层从前向后遍历，但该层节点在deque中已是逆序，因此放进ret的顺序是逆序
                if (level & 1) {
                    node = q.front();
                    q.pop_front();
                    if (node->right) q.emplace_back(node->right);
                    if (node->left) q.emplace_back(node->left);
                }
                // 偶数层从后向前遍历，但该层节点在deque中已是逆序，因此放进ret的顺序是正序
                else {
                    node = q.back();
                    q.pop_back();
                    if (node->left) q.emplace_front(node->left);
                    if (node->right) q.emplace_front(node->right);
                }
                ret[level].emplace_back(node->val);
            }
            ++level;
        }
        return ret;
    }
};