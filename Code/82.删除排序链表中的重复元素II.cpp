#include<iostream>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

// �ҵĽⷨ��ʱ�� O(n) 8 ms 55.44%���ռ� O(1) 10.9 MB 19.10%
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        if (!head) return head;
        ListNode* dummy = new ListNode(101, head), * curr = dummy;
        // ע������������п��ܰѵ�ǰ�ڵ����Ľڵ�ȫ��ɾ��������curr->nextΪ�գ����Լ������Ϊcurr->next && curr->next->next
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
        // �ϸ���˵Ӧ����ô����
        ListNode* ret = dummy->next;
        delete dummy;
        dummy = nullptr;
        return ret;
        // dummyָ����ϵı��������غ�û�˶���ָ����ڴ����ɾ���������׵����ڴ�й©
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