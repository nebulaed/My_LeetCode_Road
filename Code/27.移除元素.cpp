#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ���ڹٷ��ⷨ1
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int fast = 0, slow = 0;
		while (fast < nums.size()) {
			if (nums[fast] != val) {
				nums[slow] = nums[fast];
				++slow;
			}
			++fast;
		}
		return slow;
	}
};

// �ٷ��ⷨ2����1�Ļ�����С�Ż�
class Solution {
public:
	int removeElement(vector<int>& nums, int val) {
		int left = 0, right = nums.size();
		while (left < right) {
			if (nums[left] == val) {
				nums[left] = nums[right - 1];
				--right;
			}
			else {
				++left;
			}
		}
		return left;
	}
};

int main() {
	vector<int> nums = { 2,3,3,3,4,5,6,7,8,9 };
	int val = 3;

	Solution s;
	int len = s.removeElement(nums,val);
	cout << len << endl;
	for (int i = 0; i < len; ++i) {
		cout << nums[i] << ",";
	}
	cout << endl;

	system("pause");
	return 0;
}