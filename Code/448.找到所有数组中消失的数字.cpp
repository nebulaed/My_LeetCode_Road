#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法一：排序+计数，时间O(n logn) 64 ms，空间O(1) 32.8 MB
//class Solution {
//public:
//	vector<int> findDisappearedNumbers(vector<int>& nums) {
//		int n = nums.size();
//		vector<int> ret;
//		sort(nums.begin(), nums.end());
//		if (nums.front() != 1) {
//			for (int i = 1; i < nums[0]; ++i) {
//				ret.emplace_back(i);
//			}
//		}
//		for (size_t i = 1; i < nums.size(); ++i) {
//			if (nums[i] != nums[i - 1] && nums[i] != nums[i - 1] + 1) {
//				for (int j = nums[i - 1] + 1; j < nums[i]; ++j) {
//					ret.emplace_back(j);
//				}
//			}
//		}
//		if (nums.back() != n) {
//			for (int i = nums.back() + 1; i <= n; ++i) {
//				ret.emplace_back(i);
//			}
//		}
//		return ret;
//	}
//};

// 我的解法二：哈希表式数组，时间O(n) 44 ms，空间O(n) 33.2 MB，若将bool数组用vector<int>代替则为33.9 MB
//class Solution {
//public:
//	vector<int> findDisappearedNumbers(vector<int>& nums) {
//		vector<int> ret;
//		size_t n = nums.size();
//		bool* counts = new bool[n]();
//		for (int num : nums) {
//			counts[num - 1] = true;
//		}
//		for (int i = 0; i < n; ++i) {
//			if (!counts[i]) {
//				ret.emplace_back(i + 1);
//			}
//		}
//		return ret;
//	}
//};

// 官方解法一：原地修改，时间O(n) 48 ms，空间O(1) 32.9 MB
// 用一个哈希表记录nums中的数字，记录数字后再用哈希表检查[1,n]内每一个数是否出现，找到缺失的数字
// 这里可以用长度为n的数组代替哈希表。
// 为让空间复杂度优化到O(1)，可以让输入nums充当哈希表
// 由于nums的数字范围均在[1,n]中，我们可以利用这一范围之外的数字，来表达是否存在的含义
// 具体方法：遍历nums，每遇到一个数x，就让nums[x-1]增加n。由于nums中所有数均在[1,n]中。增加以后，这些数必然大于n。最后我们遍历nums，若nums[i]未大于n，说明没遇到过数i+1。这样就找到了缺失的数字。
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        int n = nums.size();
        for (int num : nums) {
            // 注意，由于num有可能是之前的nums[num-1]，被加过n，所以要对num-1进行除以n取余数
            int x = (num - 1) % n;
            nums[num - 1] += n;
        }
        vector<int> ret;
        for (int i = 0; i < n; ++i) {
            if (nums[i] <= n) {
                ret.emplace_back(i + 1);
            }
        }
        return ret;
    }
};

// LeetCode 101解法：时间 O(n) 40 ms 85.10%，空间 32.8 MB 85.50%
// 思路：将已出现的数字对应的位置的数字变为负数，然后遍历整个数组将非负的位置对应的数字放入结果中
// 相当于把原数组当成哈希表来使用或者桶来使用
class Solution {
public:
    vector<int> findDisappearedNumbers(vector<int>& nums) {
        for (int num : nums) {
            int& cur = nums[abs(num) - 1];
            if (cur > 0) {
                cur = -cur;
            }
        }
        vector<int> ret;
        int n = nums.size();
        for (int i = 0; i < n; ++i) {
            if (nums[i] > 0) {
                ret.emplace_back(i + 1);
            }
        }
        return ret;
    }
};

int main() {

    vector<int> nums = { 4,3,2,7,8,2,3,1 };

    Solution s;
    vector<int> ret = s.findDisappearedNumbers(nums);

    for (int num : ret) {
        cout << num << ",";
    }

    return 0;
}