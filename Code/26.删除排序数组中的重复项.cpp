#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) return 0;
		auto it = nums.begin() + 1;
		while (it != nums.end()) {
			if (*(it - 1) == *it) {
				it = nums.erase(it);
			}
			else {
				++it;
			}
		}
		int len = nums.size();
		return len;
	}
};

// �ٷ��ⷨ
class Solution {
public:
	int removeDuplicates(vector<int>& nums) {
		if (nums.empty()) return 0;
		int fast = 1, slow = 1;
		while (fast < nums.size()) {
			if (nums[fast] != nums[fast - 1]) {
				nums[slow] = nums[fast];
				++slow;
			}
			++fast;
		}
		return slow;
	}
};

int main() {
	vector<int> nums = { 3,3,3,4,4,4,4,5,6,7,8,9,9,9,9,9 };
	
	Solution s;
	int len = s.removeDuplicates(nums);

	cout << len << endl;

	system("pause");
	return 0;
}