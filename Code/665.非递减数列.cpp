#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：贪心算法+双指针，时间O(n) 20 ms 83%，空间O(1) 26.4 MB 68%
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		int count = 0;
		size_t left = 0, right = 1, n = nums.size();
		while (right < n) {
			// 若left指向元素大于right指向元素
			if (nums[left] > nums[right]) {
				// 需要改变的元素+1
				++count;
				// 若改变元素大于2，返回false
				if (count > 1) return false;
				// 若right等于n-1或left指向元素小于等于right+1指向元素(能保证非递减)
				if (right == n - 1 || nums[left] <= nums[right + 1]) {
					// 将left指向元素赋给right指向位置
					nums[right] = nums[left];
				}
				// 若left等于0或right指向元素大于等于left-1指向元素(能保证非递减)
				else if (left == 0 || nums[right] >= nums[left - 1]) {
					// 将right指向元素赋给left指向位置
					nums[left] = nums[right];
				}
				// 两个都不满足，返回false
				else return false;
			}
			++left;
			++right;
		}
		return true;
	}
};

// 我的解法：上面方法小优化, 贪心算法，时间 16 ms 95.53%，空间 26.2 MB 97.94%
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		int count = 0;
		size_t n = nums.size();
		for (size_t i = 0; i < n - 1; ++i) {
			int curr = nums[i], next = nums[i + 1];
			if (curr > next) {
				++count;
				if (count > 1) return false;
				if (i + 1 == n - 1 || curr <= nums[i + 2]) {
					nums[i + 1] = curr;
				}
				else if (i == 0 || next >= nums[i - 1]) {
					nums[i] = next;
				}
				else return false;
			}
		}
		return true;
	}
};


// 官方解法：数组，时间 16 ms 95.53%，空间 26.4 MB 43.92%
// 思考如下问题：要使nums变成一个非递减数列，数组中至多有多少个i满足nums[i]>nums[i+1]？
// 稍加思考可知至多一个
// 但仅仅这个条件无法保证修改后能将其变为非递减数列，如[3,4,1,2]，虽然只有4满足nums[i]>nums[i+1]，但无论4怎么修改都不能变成非递减数列
// 因此，若找到满足nums[i]>nums[i+1]的i，还需检查修改nums[i]或nums[i+1]后，nums是否变成非递减数列
// 修改时，将nums[i]修改成nums[i+1]是最好的，对nums[i+1]，将其修改成nums[i]是最好的
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		size_t n = nums.size();
		for (size_t i = 0; i < n - 1; ++i) {
			int x = nums[i], y = nums[i + 1];
			if (x > y) {
				nums[i] = y;
				// 尝试修改nums[i]为nums[i+1]看是否已成非递减数列，是则返回true
				if (is_sorted(nums.begin(), nums.end())) {
					return true;
				}
				nums[i] = x;	// 复原
				nums[i + 1] = x;
				// 修改nums[i]为nums[i+1]不可行，尝试修改nums[i+1]为nums[i]，若已成非递减数列，返回true，否则返回false
				return is_sorted(nums.begin(), nums.end());
			}
		}
		// nums已是非递减数列
		return true;
	}
};