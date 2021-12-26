#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：时间O(n logn) 124 ms，空间O(1) 59.8 MB
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (size_t i = 1; i < nums.size(); ++i) {
			if (nums[i] == nums[i - 1]) {
				return nums[i];
			}
		}
		return 0;
	}
};

// 官方题解一：二分查找，时间O(n logn) 92 ms，空间O(1) 59.8 MB
// 假定重复数为target，那么[1, target-1]的所有数都满足小于等于i的数cnt[i]<=i，[target,n]里的所有数满足cnt[i]>i，具有单调性
// 因此可以在[1,n]内使用二分查找
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		size_t n = nums.size();
		size_t left = 1, right = n - 1, ret = -1;
		while (left <= right) {
			size_t mid = (left + right) >> 1;
			int cnt = 0;
			for (size_t i = 0; i < n; ++i) {
				cnt += (nums[i] <= mid);
			}
			if (cnt <= mid) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
				ret = mid;
			}
		}
		return ret;
	}
};

// 官方题解二：二进制，时间O(n log n) 176 ms，空间O(1) 59.8 MB
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int n = nums.size(), ret = 0;
		// 确定二进制下最高位是多少
		int bit_max = 31;
		while (!((n - 1) >> bit_max)) {
			bit_max -= 1;
		}
		for (int bit = 0; bit <= bit_max; ++bit) {
			int x = 0, y = 0;
			for (int i = 0; i < n; ++i) {
				if (nums[i] & 1 << bit) {
					x += 1;
				}
				if (i >= 1 && (i & (1 << bit))) {
					y += 1;
				}
			}
			if (x > y) {
				ret |= 1 << bit;
			}
		}
		return ret;
	}
};

// 官方题解三：快慢指针，时间O(n) 84 ms，空间O(1) 59.8 MB
// 方法类似环形链表中的Floyd判圈算法
// 思路：对nums数组建图，每个位置i连接一条i->nums[i]的边，由于存在重复数字target，因此target这个位置一定有起码两条指向它的边，因此整张图一定存在环。
// 设置快指针和慢指针，慢指针每次走一步，快指针每次走两步。相遇后再将slow放到起点，两个指针每次同时移动一步，相遇的点就是答案。
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int slow = 0, fast = 0;
		do {
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (slow != fast);
		slow = 0;
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[fast];
		}
		return slow;
	}
};