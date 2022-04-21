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

// 我的方法：连成环状链表，快指针走k-1步，慢指针走1步，检查快慢指针是否相等，超时
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        int length = 1;
        ListNode* right = head, * left = head;
        while (right->next != nullptr) {
            ++length;
            right = right->next;
        }
        ListNode* tail = right;
        tail->next = head;
        while (left != right && right != left->next) {
            if (left->val != right->val) break;
            left = left->next;
            for (int i = 0; i < length - 1; ++i) {
                right = right->next;
            }
        }
        tail->next = nullptr;
        return left->val == right->val;
    }
};

// 我的解法：将链表存放到vector中，检查是否是回文数组，时间O(n) 196 ms，空间O(n) 125.1 MB
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        ListNode* ptr = head;
        vector<int> nodeList;
        while (ptr != nullptr) {
            nodeList.emplace_back(ptr->val);
            ptr = ptr->next;
        }
        for (size_t i = 0, j = nodeList.size() - 1; i < j; ++i, --j) {
            if (nodeList[i] != nodeList[j]) return false;
        }
        return true;
    }
};

// 官方解法二：递归，时间O(n) 196 ms，空间O(n) 119.7 MB
// 一个全局前向指针keep在最前面，直到递归到达最后一个节点，在递归由深往回走时，递归指针往回走，前向指针同时向前走，检查是否相等
class Solution {
private:
    ListNode* frontPointer;
    bool recCheck(ListNode* curr) {
        if (curr != nullptr) {
            if (!recCheck(curr->next)) {
                return false;
            }
            if (curr->val != frontPointer->val) {
                return false;
            }
            frontPointer = frontPointer->next;
        }
        return true;
    }
public:
    bool isPalindrome(ListNode* head){
        frontPointer = head;
        return recCheck(head);
    }
};

// 官方解法三：快慢指针，时间O(n) 172 ms，空间O(1) 112.3 MB
// 将链表的后半部分反转，然后将前半部分和后半部分比较，比较完成后将链表恢复原样。
// 在并发环境下，函数运行时需要锁定其他线程或进程对链表的访问，因为函数执行过程中链表会被修改。
// 流程：
// 1.找到前半部分链表的尾节点
// 2.反转后半部分链表
// 3.判断是否回文
// 4.恢复链表
// 5.返回结果
class Solution {
private:
    ListNode* endOfFirstHalf(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    // 206题反转链表解法
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
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr) return true;
        // 找到前半部分链表的尾节点并反转后半部分链表
        ListNode* firstHalfEnd = endOfFirstHalf(head);
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

        // 判断是否回文
        ListNode* ptr1 = head;
        ListNode* ptr2 = secondHalfStart;
        bool ret = true;
        while (ret && ptr2 != nullptr) {
            if (ptr1->val != ptr2->val) return false;
            ptr1 = ptr1->next;
            ptr2 = ptr2->next;
        }

        // 还原链表并返回结果
        firstHalfEnd->next = reverseList(secondHalfStart);
        return ret;
    }
};

int main() {

    ListNode* node3 = new ListNode(1);
    ListNode* node2 = new ListNode(2, node3);
    ListNode* node1 = new ListNode(2, node2);
    ListNode* node0 = new ListNode(1, node1);

    Solution s;
    bool ret = s.isPalindrome(node0);

    cout << ret << endl;

    return 0;
}