#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<numeric>
using namespace std;

// 我的解法：哈希表，时间 O(n) 32 ms，空间 O(n) 22.6 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_multiset<int> numSet(nums.begin(), nums.end());
		for (const auto& num : numSet) {
			if (numSet.count(num) == 1) {
				return num;
			}
		}
		return 0;
	}
};

// 我的解法参考官解思路一：使用集合存储数字，时间O(n) 24 ms，空间O(n) 19.5 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_set<int> numSet;
		for (const auto& num : nums) {
			if (numSet.count(num)) {
				numSet.erase(num);
			}
			else {
				numSet.emplace(num);
			}
		}
		return *numSet.begin();
	}
};

// 我的解法参考官解思路三：使用集合存储数组中所有数字，并计算集合的元素之和乘以2减去数组的元素之和，时间O(n) 32 ms，空间O(n) 20.2 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		set<int> numSet(nums.begin(),nums.end());
		return 2 * accumulate(numSet.begin(), numSet.end(), 0) - accumulate(nums.begin(), nums.end(), 0);
	}
};

// 官方解法一：位运算(异或)，时间 O(n) 20 ms，空间 O(1) 16.4 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (const auto& num : nums) ret ^= num;
		return ret;
	}
};

int main() {

	vector<int> nums = { 4,1,2,1,2 };

	Solution s;
	int ret = s.singleNumber(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}