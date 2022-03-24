#include<vector>
#include<stack>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：两次反转链表+链表相加，时间 O(2m + 2n) 28 ms 66.75%，空间 O(1) 69.3 MB 80.92%
class Solution {
private:
    ListNode* reverseList(ListNode* root) {
        ListNode* prev = nullptr, * curr = root, * next = nullptr;
        while (curr) {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }
        return prev;
    }
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* rl1 = reverseList(l1), * rl2 = reverseList(l2), * head = nullptr;
        int carry = 0;
        while (rl1 || rl2) {
            int n1 = rl1 ? rl1->val : 0, n2 = rl2 ? rl2->val : 0, sum = n1 + n2 + carry;
            head = new ListNode(sum % 10, head);
            carry = sum / 10;
            if (rl1) rl1 = rl1->next;
            if (rl2) rl2 = rl2->next;
        }
        if (carry) head = new ListNode(carry, head);
        return head;
    }
};

// 官方解法：栈(不反转链表)，时间 O(max{m,n}) 36 ms 30.02%，空间 O(m+n) 70.1 MB 62.27%
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        stack<int, vector<int>> stk1, stk2;
        while (l1) {
            stk1.emplace(l1->val);
            l1 = l1->next;
        }
        while (l2) {
            stk2.emplace(l2->val);
            l2 = l2->next;
        }
        int carry = 0;
        ListNode* head = nullptr;
        while (!stk1.empty() || !stk2.empty() || carry != 0) {
            int val1 = stk1.empty() ? 0 : stk1.top(), val2 = stk2.empty() ? 0 : stk2.top(), sum = val1 + val2 + carry;
            if (!stk1.empty()) stk1.pop();
            if (!stk2.empty()) stk2.pop();
            carry = sum / 10, sum %= 10;
            head = new ListNode(sum, head);
        }
        return head;
    }
};