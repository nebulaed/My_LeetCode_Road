struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：时间 O(n) 4 ms 92.45%，空间 O(1) 11.4 MB 41.44%
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == nullptr) return head;
        ListNode* slow = head, *fast = head;
        int len = 0;
        while (k-- && fast){
            fast = fast->next;
            ++len;
        }
        if (fast == nullptr) {
            ++k %= len;
            fast = head;
            while (k--) {
                fast = fast->next;
            }
        }
        while (fast->next) {
            fast = fast->next;
            slow = slow->next;
        }
        fast->next = head;
        ListNode* currHead = slow->next;
        slow->next = nullptr;
        return currHead;
    }
};