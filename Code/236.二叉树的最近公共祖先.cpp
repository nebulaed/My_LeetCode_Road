#include<iostream>
#include<unordered_map>
#include<unordered_set>
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

// 我的解法：参考官方解法一思路，时间O(n) 16 ms，空间O(n) 14 MB
// 思路：递归遍历二叉树，在往深走前，检查当前节点是否为p或q，即知道T == p，T == q
// 然后开始递归，类似于后序遍历在递归后检查当前节点的左子树是否包含p或q，表示为f_left，当前节点的右子树是否包含p或q，表示为f_right，则当前节点如果满足
// (f_left && f_right) || ((T == p || T == q) && (f_left || f_right))
// 则当前节点为所寻找的最近公共祖先
// 然后再返回当前节点或者当前节点的左子树、右子树中是否包含p或q，以供上层节点获知
class Solution {
private:
    TreeNode* ptr = nullptr;

    bool check(TreeNode* T, TreeNode* p, TreeNode* q) {
        if (T == nullptr || ptr != nullptr) return false;
        bool ret = false;
        if (T == p || T == q) ret = true;
        bool leftSon = check(T->left, p, q);
        bool rightSon = check(T->right, p, q);
        if (leftSon && rightSon || (ret && (leftSon || rightSon))) {
            ptr = T;
        }
        return ret || leftSon || rightSon;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        check(root, p, q);
        return ptr;
    }
};

// 官方题解二：哈希表存储父节点，时间O(n) 16 ms，空间O(n) 17.2 MB
// 思路：1.从根节点开始遍历整颗二叉树，用哈希表记录每个节点的父节点指针，即key为left或right节点值，value放当前节点指针
// 2.从p节点借助上面存储的哈希表不断开始往父节点移动直到root，用哈希表记录下已访问的节点，key放该节点值，value放true
// 也可以将已访问的节点放入哈希集合
// 3.再从q节点借助上面的哈希表不断往父节点移动直到root，遇到第一个祖先满足在上面的访问哈希表的对应的value已为true，说明这是p和q的最近公共祖先
// 也可以是遇到第一个祖先在上面的哈希集合中
class Solution {
private:
    unordered_map<int, TreeNode*> parent;
    unordered_set<int> visited;

    void dfs(TreeNode* T) {
        if (T->left != nullptr) {
            parent[T->left->val] = T;
            dfs(T->left);
        }
        if (T->right != nullptr) {
            parent[T->right->val] = T;
            dfs(T->right);
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        parent[root->val] = nullptr;
        dfs(root);
        while (p != nullptr) {
            visited.emplace(p->val);
            p = parent[p->val];
        }
        while (q != nullptr) {
            if (visited.count(q->val)) return q;
            q = parent[q->val];
        }
        return nullptr;
    }
};



// 根据官方思路自写代码，时间O(n) 28 ms,空间O(n) 16.9 MB
class Solution {
private:
    unordered_map<int, TreeNode*> parent;
    unordered_set<int> visited;

    void dfs(TreeNode* T) {
        if (T->left != nullptr) {
            parent[T->left->val] = T;
            dfs(T->left);
        }
        if (T->right != nullptr) {
            parent[T->right->val] = T;
            dfs(T->right);
        }
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root);
        while (true) {
            visited.emplace(p->val);
            if (p != root) {
                p = parent[p->val];
            }
            else break;
        }
        while (true) {
            if (visited.count(q->val)) return q;
            if (q != root) {
                q = parent[q->val];
            }
            else break;
        }
        return nullptr;
    }
};

// 2022.6.26解法：递归，时间O(n) 16 ms 67.29%，空间O(n) 13.9 MB 59.73%
class Solution {
private:
    TreeNode* ptr{nullptr};

    bool dfs(TreeNode* T, TreeNode* p, TreeNode* q) {
        if (T == nullptr || ptr != nullptr) return false;
        bool curr{false};
        if (T == p || T == q){
            curr = true;
        }
        bool leftSon = dfs(T->left, p, q);
        bool rightSon = dfs(T->right, p, q);
        if ((leftSon && rightSon) || (curr && (leftSon || rightSon))) {
            ptr = T;
        }
        return curr || leftSon || rightSon;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        dfs(root, p, q);
        return ptr;
    }
};