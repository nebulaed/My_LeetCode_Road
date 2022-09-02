#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：时间 12 ms，空间 11.6 MB
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* dummyHead = new ListNode(-1, head);
        ListNode* temp = dummyHead, * p = dummyHead;
        while (checkout(temp, k)) {
            vector<ListNode*> list(k, nullptr);
            for (int i = 0; i < k; ++i) {
                list[i] = p->next;
                p = p->next;
            }
            temp->next = list[k - 1];
            list[0]->next = list[k - 1]->next;
            for (int i = k - 1; i > 0; --i) {
                list[i]->next = list[i - 1];
            }
            temp = list[0];
            p = temp;
        }
        return dummyHead->next;
    }

    bool checkout(ListNode* temp, const int& k) {
        for (int i = 0; i < k; ++i) {
            if (!temp->next) {
                return false;
            }
            temp = temp->next;
        }
        return true;
    }
};

// 官方解法：模拟，时间 16 ms，空间 11.1 MB
class Solution {
public:
    // 翻转一个子链表，并且返回新的头和尾
    pair<ListNode*, ListNode*> myReverse(ListNode* head, ListNode* tail) {
        ListNode* prev = tail->next;
        ListNode* p = head;
        while (prev != tail) {
            ListNode* nex = p->next;
            p->next = prev;
            prev = p;
            p = nex;
        }
        return { tail,head };
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode* hair = new ListNode(0, head);
        ListNode* pre = hair;

        while (head) {
            ListNode* tail = pre;
            for (int i = 0; i < k; ++i) {
                tail = tail->next;
                if (!tail) {
                    return hair->next;
                }
            }
            ListNode* nex = tail->next;
            pair<ListNode*, ListNode*> result = myReverse(head, tail);
            head = result.first;
            tail = result.second;
            pre->next = head;
            tail->next = nex;
            pre = tail;
            head = tail->next;
        }
        return hair->next;
    }
};