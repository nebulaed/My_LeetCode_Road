#include<iostream>
#include<vector>

using std::vector;

// 我的解法：暴力遍历，时间O(n) 24 ms 24.76%，空间O(1) 21.7 MB 46.85%
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        for (size_t i = 0; i < nums.size() - 1; i += 2) {
            if (nums[i] != nums[i + 1]) {
                return nums[i];
            }
        }
        return nums.back();
    }
};

// 我的解法：异或，时间O(n) 24 ms 24.76%，空间O(1) 21.9 MB 5.41%
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int ret = 0;
        for (int num : nums) {
            ret ^= num;
        }
        return ret;
    }
};

// 我的解法：二分查找，时间O(log n) 20 ms 40%，空间O(1) 21.8 MB 19%
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int length = nums.size();
        int left = 0, right = length - 1;
        while (left <= right) {
            int mid = (left + right) >> 1;
            int midVal = nums[mid];
            bool parity = mid & 1;
            if ((parity && midVal == nums[mid - 1]) || (mid < length - 1 && !parity && midVal == nums[mid + 1])) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return nums[left];
    }
};


// 官方解法2：二分搜索，时间O(log n) 16 ms 47.53%，空间O(1) 21.9 MB 5.41%
// 当从中心移除一对元素后，剩下左子数组和右子数组
// 与原数组一样，包含单个元素的子数组元素个数必为奇数，不包含单个元素的子数组必为偶数。具体算法：
// 1. 将low 和high指向数组首尾两个元素，然后进行二分搜索将数组搜索空间减半，直到找到单一元素或仅剩一个元素为止。当搜索空间只剩一个元素，该元素就是答案。
// 2. 在每次循环迭代中，确定mid，变量halvesAreEven = (high-mid)%2 == 0，通过查看中间元素同一元素为左侧子数组的最后一个元素还是右侧数组的第一个元素，可以确定现在哪一侧元素个数为奇数，并更新low和high
// 3. 最难的是根据mid和halvesAreEven来更新low和high.
// 3.1 中间元素的同一元素在右边，且mid为偶数：low = mid + 2
// 3.2 中间元素的同一元素在右边，且mid为奇数：high = mid - 1
// 3.3 中间元素的同一元素在左边，且mid为偶数：high = mid - 2
// 3.4 中间元素的同一元素在左边，且mid为奇数：low = mid + 1
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) >> 1;
            int midVal = nums[mid];
            // mid是否为偶数，是为1，否为0
            bool midIsEven = !(mid & 1);
            // 中间元素的同一元素在右边
            if (nums[mid + 1] == midVal) {
                if (midIsEven) {
                    low = mid + 2;
                }
                else {
                    high = mid - 1;
                }
            }
                // 中间元素的同一元素在左边
            else if (nums[mid - 1] == midVal) {
                if (midIsEven) {
                    high = mid - 2;
                }
                else {
                    low = mid + 1;
                }
            }
            else return midVal;
        }
        return nums[low];
    }
};


// 官方解法3：仅对偶数索引进行二分搜索，时间O(log n/2)=O(log n) 20 ms 39.31%，空间O(1) 21.8 MB 33.51%
// 在单个元素的后面，成对元素变成奇数索引后跟他们的同一元素
// 说明我们在检索单个元素后面的偶数索引时，其后没有它的同一元素。
class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int low = 0, high = nums.size() - 1;
        while (low < high) {
            int mid = (low + high) >> 1;
            if (mid & 1) --mid;
            if (nums[mid] == nums[mid + 1]) {
                low = mid + 2;
            }
            else {
                high = mid;
            }
        }
        return nums[low];
    }
};