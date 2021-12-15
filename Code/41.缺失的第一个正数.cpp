#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

// 我的普通解法, 时间O(n) 252 ms，空间O(n) 129.5 MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		unordered_set<int> hashset;
		for (int i = 0; i < nums.size(); ++i) {
			hashset.insert(nums[i]);
		}
		int i = 1;
		while (hashset.count(i)) {
			++i;
		}
		return i;
	}
};

// 官方解法一：利用输入数组构造哈希表，时间O(n) 112ms, 空间O(n) 80.9MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			if (nums[i] <= 0) {
				nums[i] = n + 1;
			}
		}
		for (int i = 0; i < n; ++i) {
			if (abs(nums[i]) <= n && nums[abs(nums[i]) - 1] > 0) {
				nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
			}
		}
		for (int i = 0; i < n; ++i) {
			if (nums[i] > 0) {
				return i + 1;
			}
		}
		return n + 1;
	}
};

// 官方解法二：置换，时间O(n) 136 ms，空间O(1) 80.9 MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
				swap(nums[nums[i] - 1], nums[i]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}
		return n + 1;
	}
};

int main() {
	vector<int> nums = { 3,4,-1,1 };

	Solution s;
	int ret = s.firstMissingPositive(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}