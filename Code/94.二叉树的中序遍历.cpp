#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// �������ṹ
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// �ҵĽⷨ=�ٷ��ⷨһ���ݹ飬ʱ��O(n) 4 ms���ռ�O(n) 8.2 MB
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

// �ٷ��ⷨ�����������ݹ���ʽ��ά����һ��ջ������ʱ����ʵ�ֳ�����ʱ��O(n) 0 ms���ռ�O(n) 7.9 MB
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

// �ٷ��ⷨ����Morris����������������ƶ���������������ʱ��O(2n)=O(n) 0 ms���ռ�O(1) 8.1 MB
class Solution{
public:
    vector<int> inorderTraversal(TreeNode* root){
        vector<int> ret;
        TreeNode *pre = nullptr;

        while (root != nullptr){
            if (root->left != nullptr){
                // pre �ڵ���ǵ�ǰroot�ڵ�������һ����Ȼ��һֱ�����ߵ��޷���Ϊֹ
                pre = root->left;
                while (pre->right != nullptr && pre->right != root){
                    pre = pre->right;
                }

                // ��pre����ָ��ָ��root����������������
                if (pre->right == nullptr){
                    pre->right = root;
                    root = root->left;
                }
                // ˵���������Ѿ��������ˣ�������Ҫ�Ͽ�����
                else{
                    ret.emplace_back(root->val);
                    pre->right = nullptr;
                    root = root->right;
                }
            }
            // ���û�����ӣ���ôֱ�ӷ����Һ���
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