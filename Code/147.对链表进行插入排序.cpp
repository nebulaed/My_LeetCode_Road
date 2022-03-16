struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// �ҵĽⷨ��ʱ�� 52 ms 8.95%���ռ� 9.2 MB 98.75%
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

// �ҵĽⷨ���ٷ��ⷨ�Ľ���ʱ�� 20 ms 51.06%���ռ� 9.4 MB 23.27%
class Solution {
public:
    ListNode* insertionSortList(ListNode* head) {
        if (!head->next) return head;
        // ��lastSorted�ļ�¼��������������һ���ڵ㣬�����Ͳ���Ҫÿ���õ�������ڵ�ʱ������ͷ��ʼ�Ƚϣ����ǿ����Ƿ�С�����һ��������ڵ�
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