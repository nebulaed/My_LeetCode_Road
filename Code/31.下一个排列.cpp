#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法(参考官方思路)
//class Solution {
//public:
//	void nextPermutation(vector<int>& nums) {
//		int pos = -1;
//		for (int i = 0; i < nums.size() - 1; ++i) {
//			if (nums[i] < nums[i + 1]) {
//				pos = i;
//			}
//		}
//		if (pos != -1) {
//			int pos2;
//			for (pos2 = nums.size() - 1; pos2 > pos; --pos2) {
//				if (nums[pos] < nums[pos2]) {
//					break;
//				}
//			}
//			int temp = nums[pos];
//			nums[pos] = nums[pos2];
//			nums[pos2] = temp;
//			reverse(nums.begin() + pos + 1, nums.end());
//		}
//		else {
//			reverse(nums.begin(), nums.end());
//		}
//	}
//};

// 官方解法
class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 2;
		while (i >= 0 && nums[i] >= nums[i + 1]) {
			--i;
		}

		if (i >= 0) {
			int j = nums.size() - 1;
			while (j >= 0 && nums[i] >= nums[j]) {
				--j;
			}
			swap(nums[i], nums[j]);
		}
		reverse(nums.begin() + i + 1, nums.end());
	}
};

int main() {
	vector<int> nums = { 1,3,1,4,3 };

	Solution s;
	s.nextPermutation(nums);

	cout << '[';
	for (int i = 0; i < nums.size(); ++i) {
		cout << nums[i] << ',';
	}
	cout << ']' << endl;

	system("pause");
	return 0;
}