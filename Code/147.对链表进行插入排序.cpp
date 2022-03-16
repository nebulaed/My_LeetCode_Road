struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：时间 52 ms 8.95%，空间 9.2 MB 98.75%
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head->next) return head;
        ListNode* dummy = new ListNode(0, head), * curr = head;
        while (curr->next) {
            ListNode* temp = curr->next;
            bool flag = false;
            for (ListNode* it = dummy; it->next != temp; it = it->next) {
                if (temp->val < it->next->val) {
                    curr->next = temp->next;
                    temp->next = it->next;
                    it->next = temp;
                    flag = true;
                    break;
                }
            }
            if (!flag) curr = curr->next;
        }
        return dummy->next;
    }
};

// 我的解法：官方解法改进，时间 20 ms 51.06%，空间 9.4 MB 23.27%
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head->next) return head;
        // 用lastSorted的记录已排序链表的最后一个节点，这样就不需要每次拿到待排序节点时，都从头开始比较，而是看它是否小于最后一个已排序节点
        ListNode* dummy = new ListNode(0, head), * curr = head, * lastSorted = head;
        while (curr->next) {
            ListNode* temp = curr->next;
            if (temp->val >= lastSorted->val) {
                lastSorted = lastSorted->next;
            }
            else {
                ListNode* it = dummy;
                while (temp->val >= it->next->val) {
                    it = it->next;
                }
                curr->next = temp->next;
                temp->next = it->next;
                it->next = temp;
            }
            curr = lastSorted;
        }
        return dummy->next;
    }
};