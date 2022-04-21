#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

//class Solution {
//public:
//    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//        bool flag = false;
//        ListNode* result = new ListNode;
//        ListNode* temp = new ListNode;
//        for (ListNode* it = result; l1 != temp || l2 != temp || flag; l1 = l1->next == nullptr ? temp : l1->next, l2 = l2->next == nullptr ? temp : l2->next, it->next = (l1 != temp || l2 != temp || flag) ? new ListNode : nullptr, it = it->next) {
//            it->val = flag ? l1->val + l2->val + 1 : l1->val + l2->val;
//            if (it->val > 9) {
//                it->val -= 10;
//                flag = true;
//            }
//            else {
//                flag = false;
//            }
//        }
//        return result;
//    }
//};

// 官方解法：时间 24 ms，69.3 MB 
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        ListNode* head = nullptr, * tail = nullptr;
        int carry = 0; // 表示进位值
        while (l1 || l2) {
            // 若两个链表长度不同，则给长度短的链表后面加上补齐的0，例如789和56789相加，链表分别为9->8->7->0->0和9->8->7->6->5
            int n1 = l1 ? l1->val : 0;
            int n2 = l2 ? l2->val : 0;
            int sum = n1 + n2 + carry;
            if (!head) {
                head = tail = new ListNode(sum % 10);
            }
            else {
                tail->next = new ListNode(sum % 10);
                tail = tail->next;
            }
            carry = sum / 10;
            if (l1) {
                l1 = l1->next;
            }
            if (l2) {
                l2 = l2->next;
            }
        }
        // 若链表遍历结束后，剩下的carry>0，则还需在链表后面附加一个节点值为carry
        if (carry > 0) {
            tail->next = new ListNode(carry);
        }
        return head;
    }
};

int main()
{
    ListNode l1(2);
    ListNode l1_2(4);
    ListNode l1_3(3);
    l1.next = &l1_2;
    l1_2.next = &l1_3;
    ListNode l2(5);
    ListNode l2_2(6);
    ListNode l2_3(4);
    l2.next = &l2_2;
    l2_2.next = &l2_3;

    Solution s;
    ListNode* result = s.addTwoNumbers(&l1, &l2);
    while (result != nullptr)
    {
        cout << result->val << " ";
        result = result->next;
    }
    cout << endl;

    return 0;
}

//int main() {
//	vector<int> input = { 0,4,3,0 };
//	vector<int> output;
//	int target = 0;
//
//	Solution s;
//	output = s.twoSum(input, target);
//
//	for (int i = 0; i < output.size(); i++) {
//		printf("%d ", output[i]);
//	}
//	printf("\n");
//
//	return 0;
//}