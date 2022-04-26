#include<climits>
#include<vector>
#include<algorithm>

using namespace std;

// 我的解法：快速选择遍历数组，时间 O(n^2) 超时
class Solution {
private:
    int quickSelection(vector<int> &nums, int left, int right) {
        int mid = (left + right) >> 1;
        if (nums[left] > nums[right]) {
            swap(nums[left], nums[right]);
        }
        if (nums[mid] > nums[right]) {
            swap(nums[mid], nums[right]);
        }
        if (nums[mid] > nums[left]) {
            swap(nums[mid], nums[left]);
        }
        int first = left, last = right, key = nums[first];
        while (first < last) {
            while (first < last && key <= nums[last]) {
                --last;
            }
            nums[first] = nums[last];
            while (first < last && key >= nums[first]) {
                ++first;
            }
            nums[last] = nums[first];
        }
        nums[first] = key;
        return last;
    }

    int findKthSmallest(vector<int> &nums, int k) {
        int left = 0, right = nums.size() - 1;
        while (left < right) {
            int mid = quickSelection(nums, left, right);
            if (mid == k) {
                return nums[mid];
            } else if (mid < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return nums[left];
    }

public:
    int findUnsortedSubarray(vector<int> &nums) {
        int cnt = nums.size(), n = nums.size();
        vector<int> duplication(nums);
        bool monoIncr = true;
        for (int i = 0; i < n; ++i) {
            if (findKthSmallest(duplication, i) != nums[i]) {
                monoIncr = false;
                break;
            }
            --cnt;
        }
        if (monoIncr) return 0;
        for (int i = n - 1; i >= 0; --i) {
            if (findKthSmallest(duplication, i) != nums[i]) {
                break;
            }
            --cnt;
        }
        return cnt;
    }
};

// 我的解法：排序对比，时间 O(n log n) 24 ms 73.26%，空间 O(n) 26.6 MB 32.81%
class Solution {
public:
    int findUnsortedSubarray(vector<int> &nums) {
        int cnt = nums.size(), n = nums.size();
        vector<int> duplication(nums);
        sort(duplication.begin(), duplication.end());
        bool monoIncr = true;
        for (int i = 0; i < n; ++i) {
            if (duplication[i] != nums[i]) {
                monoIncr = false;
                break;
            }
            --cnt;
        }
        if (monoIncr) return 0;
        for (int i = n - 1; i >= 0; --i) {
            if (duplication[i] != nums[i]) {
                break;
            }
            --cnt;
        }
        return cnt;
    }
};

// 官方解法：一次遍历，时间 O(n) 24 ms 73.26%，空间 O(1) 25.7 MB 94.97%
// 假设需排序部分的数字numsB在nums中对应区间为[left, right]，left左边部分的数字为numsA，右边部分的数字为numsC
// 注意到numsB和numsC中任意一个数都大于等于numsA中任意一个数。因此有numsA中每一个数numsi都满足：numsi <= numsj (i+1<=j<=n-1)
// 我们可以从大到小枚举i，用一个变量currMin记录min(i+1<=j<=n-1)numsj，每次移动j，都可以O(1)地更新currMin。
// 最后一个使得不等式不成立的i就是left。left左侧就是numsA的最大范围，同理可得right
class Solution {
public:
    int findUnsortedSubarray(vector<int> &nums) {
        int n = nums.size(), currMax = INT_MIN, currMin = INT_MAX, left = -1, right = -1;
        for (int i = 0; i < n; ++i) {
            if (currMax > nums[i]) {
                right = i;
            } else {
                currMax = nums[i];
            }
            if (currMin < nums[n - i - 1]) {
                left = n - i - 1;
            } else {
                currMin = nums[n - i - 1];
            }
        }
        return right == -1 ? 0 : (right - left + 1);
    }
};