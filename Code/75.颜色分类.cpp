#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：双指针两次遍历
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int fast = 0, slow = 0;
		while (fast != nums.size()) {
			if (nums[fast] == 0) {
				swap(nums[slow], nums[fast]);
				++slow;
			}
			++fast;
		}
		fast = slow = nums.size() - 1;
		while (fast >= 0) {
			if (nums[fast] == 2) {
				swap(nums[slow], nums[fast]);
				--slow;
			}
			--fast;
		}
	}
};

// 我的解法：一次遍历，需要将0移到开头，2移到结尾
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int end = 0;
		for (auto it = nums.begin(); it != nums.end() - end;) {
			if (*it == 0) {
				it = nums.erase(it);
				nums.insert(nums.begin(), 0);
				++it;
			}
			else if (*it == 2) {
				it = nums.erase(it);
				nums.push_back(2);
				++end;
			}
			else {
				++it;
			}
		}
	}
};

// 官方解法一：单指针
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int ptr = 0;
		for (int i = 0; i < n; ++i) {
			if (nums[i] == 0) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
		for (int i = ptr; i < n; ++i) {
			if (nums[i] == 1) {
				swap(nums[i], nums[ptr]);
				++ptr;
			}
		}
	}
};

// 官方解法二：双指针
class Solution {
public:
	void sortColors(vector<int>& nums) {
		int n = nums.size();
		int p0 = 0, p1 = 0;
		for (int i = 0; i < n; ++i) {
			if (nums[i] == 1) {
				swap(nums[i], nums[p1]);
				++p1;
			}
			else if (nums[i] == 0) {
				swap(nums[i], nums[p0]);
				if (p0 < p1) {
					swap(nums[i], nums[p1]);
				}
				++p0;
				++p1;
			}
		}
	}
};