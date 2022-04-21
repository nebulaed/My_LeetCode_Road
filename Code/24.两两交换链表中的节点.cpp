#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：创建一个新链表存放
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummy = new ListNode(-1, head);
        ListNode* p = head, * q;
        ListNode* preHead = new ListNode(-1, nullptr);
        ListNode* prev = preHead;
        int count = 0;
        while (p) {
            if (count % 2 == 0 && p->next) {
                q = p->next;
                p->next = q->next;
                q->next = prev->next;
                prev->next = q;
                prev = prev->next;
                ++count;
            }
            ++count;
            p = p->next;
        }
        p = dummy;
        prev = preHead->next;
        while (p && prev) {
            preHead->next = prev->next;
            prev->next = p->next;
            p->next = prev;
            prev = preHead->next;
            p = p->next->next;
        }
        p = dummy->next;
        prev = preHead->next;
        return dummy->next;
    }
};

// 官方解法1：递归
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        ListNode* newHead = head->next;
        head->next = swapPairs(newHead->next);
        newHead->next = head;
        return newHead;
    }
};

// 官方解法2：迭代
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* dummyHead = new ListNode(-1, head);
        ListNode* temp = dummyHead;
        while (temp->next != nullptr && temp->next->next != nullptr) {
            ListNode* node1 = temp->next;
            ListNode* node2 = temp->next->next;
            temp->next = node2;
            node1->next = node2->next;
            node2->next = node1;
            temp = node1;
        }
        return dummyHead->next;
    }
};

// LeetCode 101解法：时间 0 ms 100%，空间 7.5 MB 5.31%
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode* p = head, * s = nullptr;
        if (p && p->next) {
            s = p->next;
            p->next = s->next;
            s->next = p;
            head = s;
            while (p->next && p->next->next) {
                s = p->next->next;
                p->next->next = s->next;
                s->next = p->next;
                p->next = s;
                p = s->next;
            }
        }
        return head;
    }
};

int main() {


    return 0;
}