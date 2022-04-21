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

// 我的解法一：vector存放链表节点，反向连接，时间 O(n) 4 ms，空间 O(n) 8.3 MB
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* dummy = new ListNode(0, head);
        ListNode* ptr = dummy;
        vector<ListNode*> nodeVec;
        while (ptr->next != nullptr) {
            nodeVec.emplace_back(ptr->next);
            ptr = ptr->next;
        }
        ptr = dummy;
        size_t nodeNum = nodeVec.size();
        ptr->next = nodeVec[nodeNum - 1];
        nodeVec[0]->next = nullptr;
        for (size_t i = nodeNum - 1; i > 0; --i) {
            nodeVec[i]->next = nodeVec[i - 1];
        }
        return dummy->next;
    }
};

// 我的解法二：迭代指针，时间O(n) 4 ms，空间O(1) 8 MB
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (head == nullptr) return head;
        ListNode* tail = head, * prev = nullptr, * ptr = head, *nex;
        while (tail->next != nullptr) tail = tail->next;
        while (prev != tail) {
            nex = ptr->next;
            ptr->next = prev;
            prev = ptr;
            ptr = nex;
        }
        return tail;
    }
};

// 官方解法一：迭代，时间O(n) 0 ms，空间O(1) 8 MB
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr, * curr = head;
        while (curr) {
            ListNode* next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};


// 官方解法二：递归，时间O(n) 4 ms，空间O(n) 8.3 MB
// 先逐层深入到尾节点，然后在递归往回走的过程中逆序将节点的下一个节点的next指针指向当前节点
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        if (!head || !head->next) {
            return head;
        }
        ListNode* newHead = reverseList(head->next);
        head->next->next = head;
        head->next = nullptr;
        return newHead;
    }
};

// LeetCode 101解法：时间 4 ms 94.31%，空间 8.1 MB 60.05%
class Solution {
public:
    ListNode* reverseList(ListNode* head, ListNode* prev = nullptr) {
        if (!head) return prev;
        ListNode* next = head->next;
        head->next = prev;
        return reverseList(next, head);
    }
};

// 我的第二次解法：时间 4 ms 94.36%，空间 8 MB 90.09%
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr, * curr = head, * next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
};