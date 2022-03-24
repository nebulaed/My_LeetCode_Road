struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// �ҵĽⷨ�����α�����ʱ�� 4 ms 49.06%���ռ� 7.3 MB 26.13%
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

// �ҵĽⷨ����һ�α�����ʱ�� O(n) 0 ms 100%���ռ� O(1) 7.3 MB 39.14%
class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (!head || !head->next || left == right) return head;
        ListNode* dummy = new ListNode(0, head), * prev = dummy, * curr = head, * prev2 = nullptr, * next = nullptr;
        int count = 0;
        // ��ѯ��ת�������
        while (++count != left) {
            prev = curr;
            curr = curr->next;
        }
        // �Ե���ת�����յ�Ϊֹ����������ڵ���з�ת
        while (count++ != right + 1) {
            next = curr->next;
            curr->next = prev2;
            prev2 = curr;
            curr = next;
        }
        // ����ת�����ԭ��һ���ڵ�ӵ���ת�����ĵ�һ���ڵ�
        prev->next->next = curr;
        // ����ת����ǰ�����һ���ڵ�ӵ���ת�����ԭ���һ���ڵ�
        prev->next = prev2;
        return dummy->next;
    }
};