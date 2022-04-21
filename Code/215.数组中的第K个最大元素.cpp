#include<iostream>
#include<vector>
#include<ctime>
#include<algorithm>
using namespace std;

// 直接排序，时间O(n log n) 8 ms，空间 9.8 MB
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end(), compare);
        return nums[k - 1];
    }

    static bool compare(int val1, int val2) {
        return val1 > val2;
    }
};

// 直接调用std库里的部分排序算法，nth_element，时间O(n) 4 ms，空间 9.7 MB
class Solution {
public:
    int findKthLargest(vector<int>& nums, int k) {
        std::nth_element(nums.begin(), nums.end() - k, nums.end());
        return nums[nums.size() - k];
    }
};

// 我的解法：时间 O(n logk) 8 ms，空间O(log n) 9.8 MB
class Solution {
private:
    void HeapAdjust(vector<int>& nums, int s, int m) {
        int temp = nums[s];
        for (int j = 2 * s + 1; j < m; j = j * 2 + 1) {
            if (j < m - 1 && nums[j] < nums[j + 1]) {
                ++j;
            }
            if (temp >= nums[j]) {
                break;
            }
            nums[s] = nums[j];
            s = j;
        }
        nums[s] = temp;
    }

    int HeapSort(vector<int>& nums, int k) {
        int length = nums.size();
        for (int i = length / 2 - 1; i >= 0; --i) {
            HeapAdjust(nums, i, length);
        }
        for (int i = length; i > 1; --i) {
            swap(nums[0], nums[i - 1]);
            if (i - 1 == length - k) return nums[i - 1];
            HeapAdjust(nums, 0, i - 1);
        }
        return nums[0];
    }

public:
    int findKthLargest(vector<int>& nums, int k) {
        int ret = HeapSort(nums, k);
        return ret;
    }
};

// 官方解法一：快速选择算法(快排的部分排序)，时间 O(n) 8 ms，空间O(log n) 9.7 MB
class Solution {
private:
    int quickSelect(vector<int>& nums, int left, int right, int index) {
        int q = randomPartition(nums, left, right);
        if (q == index) {
            return nums[q];
        }
        else {
            return q < index ? quickSelect(nums, q + 1, right, index) : quickSelect(nums, left, q - 1, index);
        }
    }

    // 随机选取枢轴
    inline int randomPartition(vector<int>& nums, int left, int right) {
        int i = rand() % (right - left + 1) + left;
        swap(nums[i], nums[right]);
        return partition(nums, left, right);
    }

    inline int partition(vector<int>& nums, int left, int right) {
        int x = nums[right], i = left - 1;
        for (int j = left; j < right; ++j) {
            if (nums[j] <= x) {
                swap(nums[++i], nums[j]);
            }
        }
        swap(nums[i + 1], nums[right]);
        return i + 1;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        srand(time(0));
        return quickSelect(nums, 0, nums.size() - 1, nums.size() - k);
    }
};

// LeetCode 101解法：快速选择，时间O(n) 36 ms，空间O(1) 9.7 MB
class Solution {
private:
    int quickSelection(vector<int>& nums, int left, int right)
    {
        int first = left, last = right, key = nums[first];
        while (first < last) {
            while (first < last && key <= nums[last]) {
                --last;
            }
            nums[first] = nums[last];
            while (first < last && nums[first] <= key) {
                ++first;
            }
            nums[last] = nums[first];
        }
        nums[first] = key;
        return last;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1, target = nums.size() - k;
        while (left < right) {
            int mid = quickSelection(nums, left, right);
            if (mid == target) {
                return nums[mid];
            }
            else if (mid < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return nums[left];
    }
};

// LeetCode 101解法优化：三数取中+快速选择，时间 4 ms 96.42%，空间 9.7 MB 80.90%
class Solution {
private:
    int quickSelection(vector<int>& nums, int left, int right)
    {
        //=====================================//
        // 三数取中选取枢轴
        int mid = (left + right) >> 1;
        if (nums[left] > nums[right]) {
            swap(nums[left], nums[right]);
        }
        if (nums[mid] > nums[right]) {
            swap(nums[right], nums[mid]);
        }
        if (nums[mid] > nums[left]) {
            swap(nums[mid], nums[left]);
        }
        //=====================================//
        int first = left, last = right, key = nums[first];
        while (first < last) {
            while (first < last && key <= nums[last]) {
                --last;
            }
            nums[first] = nums[last];
            while (first < last && nums[first] <= key) {
                ++first;
            }
            nums[last] = nums[first];
        }
        nums[first] = key;
        return last;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left = 0, right = nums.size() - 1, target = nums.size() - k;
        while (left < right) {
            int mid = quickSelection(nums, left, right);
            if (mid == target) {
                return nums[mid];
            }
            else if (mid < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return nums[left];
    }
};