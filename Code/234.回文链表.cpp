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

// �ҵķ��������ɻ�״������ָ����k-1������ָ����1����������ָ���Ƿ���ȣ���ʱ
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

// �ҵĽⷨ���������ŵ�vector�У�����Ƿ��ǻ������飬ʱ��O(n) 196 ms���ռ�O(n) 125.1 MB
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

// �ٷ��ⷨ�����ݹ飬ʱ��O(n) 196 ms���ռ�O(n) 119.7 MB
// һ��ȫ��ǰ��ָ��keep����ǰ�棬ֱ���ݹ鵽�����һ���ڵ㣬�ڵݹ�����������ʱ���ݹ�ָ�������ߣ�ǰ��ָ��ͬʱ��ǰ�ߣ�����Ƿ����
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

// �ٷ��ⷨ��������ָ�룬ʱ��O(n) 172 ms���ռ�O(1) 112.3 MB
// ������ĺ�벿�ַ�ת��Ȼ��ǰ�벿�ֺͺ�벿�ֱȽϣ��Ƚ���ɺ�����ָ�ԭ����
// �ڲ��������£���������ʱ��Ҫ���������̻߳���̶�����ķ��ʣ���Ϊ����ִ�й���������ᱻ�޸ġ�
// ���̣�
// 1.�ҵ�ǰ�벿�������β�ڵ�
// 2.��ת��벿������
// 3.�ж��Ƿ����
// 4.�ָ�����
// 5.���ؽ��
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

	// 206�ⷴת����ⷨ
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
		// �ҵ�ǰ�벿�������β�ڵ㲢��ת��벿������
		ListNode* firstHalfEnd = endOfFirstHalf(head);
		ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

		// �ж��Ƿ����
		ListNode* ptr1 = head;
		ListNode* ptr2 = secondHalfStart;
		bool ret = true;
		while (ret && ptr2 != nullptr) {
			if (ptr1->val != ptr2->val) return false;
			ptr1 = ptr1->next;
			ptr2 = ptr2->next;
		}

		// ��ԭ�������ؽ��
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

	system("pause");
	return 0;
}