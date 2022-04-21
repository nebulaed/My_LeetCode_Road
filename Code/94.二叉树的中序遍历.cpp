#include<iostream>
#include<vector>
#include<stack>
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

// 我的解法=官方解法一：递归，时间O(n) 4 ms，空间O(n) 8.2 MB
class Solution{
public:
    void inorder(TreeNode* T, vector<int>& ret){
        if (T == nullptr) return;
        inorder(T->left, ret);
        ret.emplace_back(T->val);
        inorder(T->right, ret);
    }

    vector<int> inorderTraversal(TreeNode* root){
        vector<int> ret;
        inorder(root, ret);
        return ret;
    }
};

// 官方解法二：迭代，递归隐式地维护了一个栈，迭代时将其实现出来，时间O(n) 0 ms，空间O(n) 7.9 MB
class Solution{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> ret;
        stack<TreeNode*> stk;
        while (root != nullptr || !stk.empty()){
            while (root != nullptr){
                stk.push(root);
                root = root->left;
            }
            root = stk.top();
            stk.pop();
            ret.emplace_back(root->val);
            root = root->right;
        }
        return ret;
    }
};

// 官方解法三：Morris中序遍历，加入类似二叉树的线索化，时间O(2n)=O(n) 0 ms，空间O(1) 8.1 MB
class Solution{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> ret;
        TreeNode *pre = nullptr;

        while (root != nullptr){
            if (root->left != nullptr){
                // pre 节点就是当前root节点向左走一步，然后一直向右走到无法走为止
                pre = root->left;
                while (pre->right != nullptr && pre->right != root){
                    pre = pre->right;
                }

                // 让pre的右指针指向root，继续遍历左子树
                if (pre->right == nullptr){
                    pre->right = root;
                    root = root->left;
                }
                    // 说明左子树已经访问完了，我们需要断开链接
                else{
                    ret.emplace_back(root->val);
                    pre->right = nullptr;
                    root = root->right;
                }
            }
                // 如果没有左孩子，那么直接访问右孩子
            else{
                ret.emplace_back(root->val);
                root = root->right;
            }
        }
        return ret;
    }
};

int main(){
    TreeNode *left2 = new TreeNode(3);
    TreeNode *right1 = new TreeNode(2, left2, nullptr);
    TreeNode *root = new TreeNode(1, nullptr, right1);

    Solution s;
    vector<int> ret = s.inorderTraversal(root);

    cout << "[";
    for (int i = 0; i < ret.size(); ++i){
        cout << ret[i] << ",";
    }
    cout << "]" << endl;

    delete left2, right1, root;
    return 0;
}