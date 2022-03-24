#include<vector>
#include<queue>
using namespace std;

// �������ṹ
struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// �ҵĽⷨ��ʱ�� 4 ms 59.00%���ռ� 11.7 MB 81.56%
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

// �ҵĽⷨ�ο��ٷ��ⷨ������˫�˶��У�ʱ�� 0 ms 100%���ռ� 11.8 MB 53.51%
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
                // �������ǰ�����������ò�ڵ���deque������������˷Ž�ret��˳��������
                if (level & 1) {
                    node = q.front();
                    q.pop_front();
                    if (node->right) q.emplace_back(node->right);
                    if (node->left) q.emplace_back(node->left);
                }
                // ż����Ӻ���ǰ���������ò�ڵ���deque������������˷Ž�ret��˳��������
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