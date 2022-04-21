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

// 官方解法：两遍扫描，时间O(n)，空间 O(1)
// 我们希望找到一种方法，能够找到一个大于当前序列的新序列，且变大的幅度尽可能小：
// 1.我们需要将一个左边的「较小数」与一个右边的「较大数」交换，以能够让当前排列变大，从而得到下一个排列。
// 2.同时我们要让这个「较小数」尽量靠右，而「较大数」尽可能小。当交换完成后，「较大数」右边的数需要按照升序重新排列。这样可以在保证新排列大于原来排列的情况下，使变大的幅度尽可能小。
// 对于长度为 n 的排列 a：
// 1. 首先从后向前查找第一个顺序对 (i,i+1)，满足 a[i] < a[i+1]。这样「较小数」即为 a[i]。此时 [i+1,n) 必然是下降序列。
// 2. 如果找到了顺序对，那么在区间 [i+1,n) 中从后向前查找第一个元素 j 满足 a[i] < a[j]。这样「较大数」即为 a[j]。
// 3. 交换 a[i] 与 a[j]，此时可以证明区间 [i+1,n) 必为降序。我们可以直接使用双指针反转区间 [i+1,n) 使其变为升序，而无需对该区间进行排序。

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

    return 0;
}