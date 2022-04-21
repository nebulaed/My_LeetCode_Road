#include<iostream>
#include<unordered_set>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

// 我的解法1：哈希表，时间O(n) 20 ms，空间O(n) 10.2 MB
class Solution {
public:
    bool hasCycle(ListNode* head) {
        unordered_set<ListNode*> nodeList;
        while (head != nullptr) {
            if (nodeList.count(head)) return true;
            else nodeList.emplace(head);
            head = head->next;
        }
        return false;
    }
};

// 我的解法2：破坏链表内容，时间O(n) 8 ms，空间O(1) 8 MB
class Solution {
public:
    bool hasCycle(ListNode* head) {
        while (head != nullptr) {
            if (head->val == 1e7) return true;
            head->val = 1e7;
            head = head->next;
        }
        return false;
    }
};

// 官方解法2(根据思路自写版本)：快慢指针(Floyd判圈算法)，时间O(n) 12 ms，空间O(1) 7.9 MB
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr) return false;
        ListNode* slow = head, * fast = head->next;
        while (slow != fast) {
            if (fast == nullptr) return false;
            slow = slow->next;
            fast = !fast->next ? nullptr : fast->next->next;
        }
        return true;
    }
};

// 官方解法2(官方版本)：快慢指针(Floyd判圈算法)，时间O(n) 12 ms，空间O(1) 7.9 MB
class Solution {
public:
    bool hasCycle(ListNode* head) {
        if (head == nullptr || head->next == nullptr) {
            return false;
        }
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (slow != fast) {
            if (fast == nullptr || fast->next == nullptr) {
                return false;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        return true;
    }
};

int main() {

    ListNode* node0 = new ListNode(3);
    ListNode* node1 = new ListNode(2);
    ListNode* node2 = new ListNode(0);
    ListNode* node3 = new ListNode(-4);
    node0->next = node1;
    node1->next = node2;
    node2->next = node3;
    node3->next = node1;

    Solution s;
    bool ret = s.hasCycle(node0);
    cout << ret << "\n";

    return 0;
}