#include<iostream>
#include<stack>
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

// 我的解法一：先序遍历，时间 4 ms，空间 8.9 MB
class Solution {
private:
    int sum = 0;
public:
    void dfs(TreeNode* T, int num) {
        if (T == nullptr) return;
        num = num * 10 + T->val;
        if (T->left == nullptr && T->right == nullptr) {
            sum += num;
            return;
        }
        dfs(T->left, num);
        dfs(T->right, num);
    }
    int sumNumbers(TreeNode* root) {
        dfs(root, 0);
        return sum;
    }
};

// 官方解法：深度优先搜索DFS，时间O(n) 0 ms，空间O(n) 8.9 MB
class Solution {
public:
    int dfs(TreeNode* root, int prevSum) {
        if (root == nullptr) {
            return 0;
        }
        int sum = prevSum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            return sum;
        }
        else {
            return dfs(root->left, sum) + dfs(root->right, sum);
        }
    }
    int sumNumbers(TreeNode* root) {
        return dfs(root, 0);
    }
};

// 官方解法二：广度优先搜索BFS，时间O(n) 4 ms，空间O(n) 9.1 MB
class Solution {
public:
    int sumNumbers(TreeNode* root) {
        if (root == nullptr) return 0;
        int sum = 0;
        queue<TreeNode*> nodeQueue;
        queue<int> numQueue;
        nodeQueue.emplace(root);
        numQueue.emplace(root->val);
        while (!nodeQueue.empty()) {
            TreeNode* node = nodeQueue.front();
            int num = numQueue.front();
            nodeQueue.pop();
            numQueue.pop();
            TreeNode* left = node->left, * right = node->right;
            if (left == nullptr && right == nullptr) {
                sum += num;
            }
            else {
                if (left != nullptr) {
                    nodeQueue.emplace(left);
                    numQueue.emplace(num * 10 + left->val);
                }
                if (right != nullptr) {
                    nodeQueue.emplace(right);
                    numQueue.emplace(num * 10 + right->val);
                }
            }
        }
        return sum;
    }
};

int main() {

    return 0;
}