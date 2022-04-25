struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 我的解法：两次遍历，第二次中序遍历，时间 40 ms 35.09%，空间 32.5 MB 92.63%
class Solution {
private:
    void inorderTraversal(TreeNode* T, int& sum){
        if (!T) return;
        inorderTraversal(T->left, sum);
        sum -= T->val;
        T->val += sum;
        inorderTraversal(T->right, sum);
    }

    int dfs(TreeNode* T){
        if (!T) return 0;
        return T->val + dfs(T->left) + dfs(T->right);
    }
public:
    TreeNode* convertBST(TreeNode* root) {
        int totalSum = dfs(root);
        inorderTraversal(root, totalSum);
        return root;
    }
};

// 官方解法一：一次遍历，反序中序遍历，时间 O(n) 32 ms 79.76%，空间 平均O(log n)，最坏O(n) 32.5 MB 87.18%
class Solution {
private:
    int sum = 0;
public:
    TreeNode* convertBST(TreeNode* root) {
        if (root == nullptr) return root;
        convertBST(root->right);
        sum += root->val;
        root->val = sum;
        convertBST(root->left);
        return root;
    }
};

// 官方解法二：Morris遍历，反序中序遍历，时间 O(n) 32 ms 79.76%，空间 O(1) 32.5 MB 90.39%
// Morris 遍历的核心思想是利用树的大量空闲指针，实现空间开销的极限缩减。
class Solution {
private:
    TreeNode *getSuccessor(TreeNode *node) {
        TreeNode *succ = node->right;
        while (succ->left != nullptr && succ->left != node) {
            succ = succ->left;
        }
        return succ;
    }

public:
    TreeNode *convertBST(TreeNode *root) {
        int sum = 0;
        TreeNode *node = root;
        while (node != nullptr) {
            // 若当前节点的右子节点为空，处理当前节点，并遍历当前节点的左子树
            if (node->right == nullptr) {
                sum += node->val;
                node->val = sum;
                node = node->left;
            } else {    // 若当前节点的右子节点不为空，找到当前节点右子树的最左节点，即当前节点反序中序遍历的前驱节点
                TreeNode *succ = getSuccessor(node);
                // 若最左的节点的左指针为空，将最左节点的左指针指向当前节点，遍历当前节点的右子节点
                if (succ->left == nullptr) {
                    succ->left = node;
                    node = node->right;
                } else {    // 若最左节点的左指针不为空，将最左节点的左指针重新置空，处理当前节点，并遍历当前节点的左子树
                    succ->left = nullptr;
                    sum += node->val;
                    node->val = sum;
                    node = node->left;
                }
            }
        }
        return root;
    }
};