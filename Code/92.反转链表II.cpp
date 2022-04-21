struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：两次遍历，时间 4 ms 49.06%，空间 7.3 MB 26.13%
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next || left == right) return head;
        ListNode* prev = nullptr, * curr = head, * end = head;
        int count = 0;
        while (++count != right) {
            if (count < left) {
                prev = curr;
                curr = curr->next;
            }
            end = end->next;
        }
        end = end->next;
        ListNode* next = nullptr, * prev2 = end;
        while (curr != end) {
            next = curr->next;
            curr->next = prev2;
            prev2 = curr;
            curr = next;
        }
        if (prev) prev->next = prev2;
        return 1 == left ? prev2 : head;
    }
};

// 我的解法二：一次遍历，时间 O(n) 0 ms 100%，空间 O(1) 7.3 MB 39.14%
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next || left == right) return head;
        ListNode* dummy = new ListNode(0, head), * prev = dummy, * curr = head, * prev2 = nullptr, * next = nullptr;
        int count = 0;
        // 查询反转区域起点
        while (++count != left) {
            prev = curr;
            curr = curr->next;
        }
        // 对到反转区域终点为止的所有链表节点进行反转
        while (count++ != right + 1) {
            next = curr->next;
            curr->next = prev2;
            prev2 = curr;
            curr = next;
        }
        // 将反转区域的原第一个节点接到反转区域后的第一个节点
        prev->next->next = curr;
        // 将反转区域前的最后一个节点接到反转区域的原最后一个节点
        prev->next = prev2;
        return dummy->next;
    }
};