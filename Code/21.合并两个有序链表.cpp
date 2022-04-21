#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法，效率最低
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* dummy1 = new ListNode(0, l1);
        ListNode* dummy2 = new ListNode(0, l2);
        ListNode* p, * q, * temp;
        p = dummy1;
        q = dummy2;
        while (p->next && q->next) {
            if (p->next->val <= q->next->val && (q->next->val <= p->next->next->val || !p->next->next)) {
                temp = q->next;
                q->next = temp->next;
                temp->next = p->next->next;
                p->next->next = temp;
            }
            else if (p->next->val < q->next->val && (p->next->next->val < q->next->val || !p->next->next)) {
                p = p->next;
            }
            else if (p->next->val > q->next->val) {
                temp = q->next;
                q->next = temp->next;
                temp->next = p->next;
                p->next = temp;
            }
        }
        if (q->next) p->next = q->next;
        ListNode* ret = dummy1->next;
        delete dummy1, dummy2;
        return ret;
    }
};

// 官方解法1：递归，效率最高
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if (l1 == nullptr) {
            return l2;
        }
        else if (l2 == nullptr) {
            return l1;
        }
        else if (l1->val < l2->val) {
            l1->next = mergeTwoLists(l1->next, l2);
            return l1;
        }
        else {
            l2->next = mergeTwoLists(l1, l2->next);
            return l2;
        }
    }
};

// 官方解法2：迭代，效率第二
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* preHead = new ListNode(-1);

        ListNode* prev = preHead;
        while (l1 != nullptr && l2 != nullptr) {
            if (l1->val < l2->val) {
                prev->next = l1;
                l1 = l1->next;
            }
            else {
                prev->next = l2;
                l2 = l2->next;
            }
            prev = prev->next;
        }

        prev->next = l1 == nullptr ? l2 : l1;

        return preHead->next;
    }
};