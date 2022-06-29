#include<vector>
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

// 我的解法：时间 O(n) 12 ms 67.66%，空间 O(log n) 19.9 MB 99.75%
class Solution {
private:
    void dfs(vector<int> &nums, TreeNode *root, size_t left, size_t mid, size_t right) {
        size_t lMid = (left + mid) / 2, rMid = (mid + 1 + right) / 2;
        if (left != mid) {
            root->left = new TreeNode(nums[lMid]);
            dfs(nums, root->left, left, lMid, mid);
        }
        if (mid < right - 1) {
            root->right = new TreeNode(nums[rMid]);
            dfs(nums, root->right, mid + 1, rMid, right);
        }
    }

public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        size_t mid = nums.size() / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        dfs(nums, root, 0, mid, nums.size());
        return root;
    }
};

// 官方解法一：时间 O(n) 12 ms 67.66%，空间 O(log n) 20.8 MB 88.38%
class Solution {
private:
    TreeNode *helper(vector<int> &nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) >> 1;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = helper(nums, left, mid - 1);
        root->right = helper(nums, mid + 1, right);
        return root;
    }

public:
    TreeNode *sortedArrayToBST(vector<int> &nums) {
        return helper(nums, 0, nums.size() - 1);
    }
};
