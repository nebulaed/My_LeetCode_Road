#include<iostream>
#include<algorithm>
using namespace std;

struct TreeNode {
	int val;
	TreeNode* left, * right;
	TreeNode(int val = 0, TreeNode* left = nullptr, TreeNode* right = nullptr) : val(val), left(left), right(right) {}
};

// �ҵĽⷨ�����������ʱ�� O(n) 16 ms 24.49%���ռ� O(n) 20.4 MB 37.77%
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

// �ҵĽⷨ+�����Ż��������������������ƽ��ʱ����Ҫ������������ʱ�� O(n) 24 ms 5.27%���ռ� O(n) 20.1 MB 98.90%
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