struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 我的解法：时间 8 ms 79.04%，空间 7.4 MB 83.75%
class Solution {
public:
    void deleteNode(ListNode* node) {
        *node = *(node->next);
    }
};

// 防内存泄漏做法：时间 4 ms 98.70%，空间 7.4 MB 97.18%
class Solution {
public:
    void deleteNode(ListNode* node) {
        ListNode* tmp = node->next;
        *node = *tmp;
        delete(tmp);
    }
};