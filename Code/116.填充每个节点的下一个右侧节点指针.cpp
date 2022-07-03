#include<queue>
#include<cstddef>

using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

// 我的解法：层序遍历，时间 O(n) 12 ms 97.49%，空间 O(n) 16.8 MB 11.20%
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) return root;

        queue<Node*> q;
        q.emplace(root);
        while (!q.empty()) {
            int currLevelSize = q.size();
            Node* prev = nullptr;
            while (currLevelSize--) {
                auto node = q.front();
                q.pop();
                if(prev) prev->next = node;
                prev = node;
                if (node->left) q.emplace(node->left);
                if (node->right) q.emplace(node->right);
            }
        }
        return root;
    }
};

// 官方解法二：使用已建立的 next 指针，时间 O(n) 16 ms 84.21%，空间 O(1) 16.2 MB 96.06%
class Solution {
public:
    Node* connect(Node* root) {
        if (root == nullptr) {
            return root;
        }

        // 从根节点开始
        Node* leftMost = root;
        while (leftMost->left != nullptr) {
            // 遍历这一层节点组织成的链表，为下一层的节点更新next指针
            Node* head = leftMost;
            while (head != nullptr) {
                head->left->next = head->right;
                if (head->next != nullptr) {
                    head->right->next = head->next->left;
                }
                // 指针向后移动
                head = head->next;
            }
            // 去下一层的最左节点
            leftMost = leftMost->left;
        }
        return root;
    }
};