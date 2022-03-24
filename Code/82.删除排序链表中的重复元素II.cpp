#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// 我的解法：时间 O(n) 8 ms 55.44%，空间 O(1) 10.9 MB 19.10%
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        ListNode* dummy = new ListNode(101, head), * curr = dummy;
        // 注意特殊情况：有可能把当前节点后面的节点全部删除，导致curr->next为空，所以检查条件为curr->next && curr->next->next
        while (curr->next && curr->next->next) {
            int preDeleted = curr->next->val;
            if (curr->next->next->val == preDeleted) {
                ListNode* next = nullptr;
                for (ListNode* temp = curr->next; temp && temp->val == preDeleted; temp = next) {
                    next = temp->next;
                    curr->next = next;
                    delete temp;
                }
            }
            else curr = curr->next;
        }
        // 严格来说应该这么返回
        ListNode* ret = dummy->next;
        delete dummy;
        dummy = nullptr;
        return ret;
        // dummy指向堆上的变量，返回后没人对它指向的内存进行删除管理，容易导致内存泄漏
        //return dummy->next;
    }
};

int main() {

    ListNode* node1 = new ListNode(1);
    ListNode* node0 = new ListNode(1, node1);

    Solution sol;
    ListNode* root = sol.deleteDuplicates(node0);

    for (ListNode* it = root; it != nullptr; it = it->next) {
        cout << it->val << ",";
    }

    system("pause");
    return 0;
}