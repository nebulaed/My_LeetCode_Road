struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
// 我的解法：时间 4 ms 99.06%，空间 10.3 MB 8.57%
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) {
        if (!head) return head;
        ListNode* slow = head, * fast = head->next;
        while (fast && fast->next) {
            ListNode* odd = fast->next;
            fast->next = fast->next->next;
            odd->next = slow->next;
            slow->next = odd;
            fast = fast->next;
            slow = slow->next;
        }
        return head;
    }
};