#include<vector>
using namespace std;

// 我的解法：遍历，时间 O(n) 0 ms 100%，空间 O(1) 8.5 MB 88.26%
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        int n = nums.size();
        if (n == 1) return 0;
        else if (n == 2) {
            return nums[0] > nums[1] ? 0 : 1;
        }
        if (nums[0] > nums[1]) return 0;
        else if (nums[n - 1] > nums[n - 2]) return n - 1;
        for (int i = 1; i < n - 1; ++i) {
            if (nums[i - 1] < nums[i] && nums[i] > nums[i + 1]) {
                return i;
            }
        }
        return 0;
    }
};

// 官方解法一：遍历，时间 O(n) 4 ms 58.36%，空间 O(1) 8.6 MB 31.48%
class Solution {
public:
    int findPeakElement(vector<int>& nums) {
        return max_element(nums.begin(), nums.end()) - nums.begin();
    }
};

// 官方解法二：迭代爬坡优化，时间 O(log n) 4 ms 58.36%，空间 O(1) 8.4 MB 99.22%
// 从一个位置开始，不断地向高处走，那么最终一定可以到达一个峰值位置。
// 首先在 [0, n) 的范围内随机一个初始位置 i，随后根据 nums[i−1],nums[i],nums[i+1] 三者的关系决定向哪个方向走：
// 1. 如果 nums[i−1]<nums[i]>nums[i+1]，那么位置 i 就是峰值位置，我们可以直接返回 i 作为答案；
// 2. 如果 nums[i−1]<nums[i]<nums[i+1]，那么位置 i 处于上坡，我们需要往右走；
// 3. 如果 nums[i−1]>nums[i]>nums[i+1]，那么位置 i 处于下坡，我们需要往左走；
// 4. 如果 nums[i−1]>nums[i]<nums[i+1]，那么位置 i 位于山谷，两侧都是上坡，我们可以朝任意方向走。
// 如果我们规定对于最后一种情况往右走，那么当位置 i 不是峰值位置时：
// 1. 如果 nums[i]<nums[i+1]，那么我们往右走；
// 2. 如果 nums[i]>nums[i+1]，那么我们往左走。
// 如果 nums[i]<nums[i+1]，并且我们从位置 i 向右走到了位置 i+1，那么位置 i 左侧的所有位置是不可能在后续的迭代中走到的。
// 根据方法二，知道位置 i+1 以及其右侧的位置中一定有一个峰值，因此可以设计出如下的一个算法：
// 1. 对于当前可行的下标范围 [l, r]，我们随机一个下标 i；
// 2. 如果下标 i 是峰值，我们返回 i 作为答案；
// 3. 如果 nums[i]<nums[i+1]，那么我们抛弃 [l, i] 的范围，在剩余 [i+1, r] 的范围内继续随机选取下标；
// 4. 如果 nums[i]>nums[i+1]，那么我们抛弃 [i, r] 的范围，在剩余 [l, i-1] 的范围内继续随机选取下标。
// 在上述算法中，如果我们固定选取 i 为 [l, r] 的中点，那么每次可行的下标范围会减少一半，成为一个类似二分查找的方法，时间复杂度为 O(log n)。
class Solution {
private:
    // 辅助函数，输入下标 i，返回一个二元组 (0/1, nums[i])
    // 方便处理 nums[-1] 以及 nums[n] 的边界情况
    pair<int, int> get(int i, int n, const vector<int> &nums) {
        if (i == -1 || i == n) {
            return {0, 0};
        }
        return {1, nums[i]};
    }

public:
    int findPeakElement(vector<int> &nums) {
        const int n = nums.size();
        int idx = rand() % n;

        while (!(get(idx - 1, n, nums) < get(idx, n, nums) && get(idx, n, nums) > get(idx + 1, n, nums))) {
            if (get(idx, n, nums) < get(idx + 1, n, nums)) {
                ++idx;
            } else {
                --idx;
            }
        }
        return idx;
    }
};