#include<iostream>
#include<vector>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// 官方解法1：顺序合并
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            else {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = aPtr ? aPtr : bPtr;
        return head.next;
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        ListNode* ans = nullptr;
        for (int i = 0; i < lists.size(); ++i) {
            ans = mergeTwoLists(ans, lists[i]);
        }
        return ans;
    }
};

// 官方解法2：分治合并
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        if ((!a) || (!b)) return a ? a : b;
        ListNode head, * tail = &head, * aPtr = a, * bPtr = b;
        while (aPtr && bPtr) {
            if (aPtr->val < bPtr->val) {
                tail->next = aPtr;
                aPtr = aPtr->next;
            }
            else {
                tail->next = bPtr;
                bPtr = bPtr->next;
            }
            tail = tail->next;
        }
        tail->next = aPtr ? aPtr : bPtr;
        return head.next;
    }

    ListNode* merge(vector<ListNode*>& lists, int l, int r) {
        if (l == r) return lists[l];
        if (l > r) return nullptr;
        // (l + r) >> 1表示(l + r)的二进制数右移一位, 相当于除以2
        int mid = (l + r) / 2;
        return mergeTwoLists(merge(lists, l, mid), merge(lists, mid + 1, r));
    }

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        return merge(lists, 0, lists.size() - 1);
    }
};

// LeetCode 101解法：优先队列，时间 20 ms 80.19%，空间 13 MB 60.08%
// 把所有的链表存储在一个优先队列中，每次提取所有链表头部节点值最小的那个节点，直到所有链表都被提取完为止。注意因为Comp 函数默认是对最大堆进行比较并维持递增关系，如果我们想要获取最小的节点值，则我们需要实现一个最小堆，因此比较函数应该维持递减关系，所以operator() 中返回时用大于号而不是等增关系时的小于号进行比较。
class Comp {
public:
    bool operator() (ListNode* lhs, ListNode* rhs) {
        return lhs->val > rhs->val;
    }
};

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.empty()) return nullptr;
        // 构建小顶堆
        priority_queue<ListNode*, vector<ListNode*>, Comp> q;
        // 将所有链表的开头放到优先队列中，会自动按照值的大小排列
        for (ListNode* list : lists) {
            if (list) {
                q.emplace(list);
            }
        }
        // 构造头节点，方便循环
        ListNode* dummy = new ListNode(0), * cur = dummy;
        while (!q.empty()) {
            // 从优先队列中取出值最小的节点q.top()接到cur后面
            cur->next = q.top();
            q.pop();
            cur = cur->next;
            // 若cur->next非空，说明这个链表后面还有节点，将cur->next放回优先队列中按值大小构造小顶堆
            if (cur->next) {
                q.emplace(cur->next);
            }
        }
        return dummy->next;
    }
};