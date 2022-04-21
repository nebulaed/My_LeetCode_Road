#include<vector>
using namespace std;

// 评论解法：旋转数组的特点很简单，就是数组至少有一半是有序的，因此当每次二分后只需要判断索要寻找的目标是否在有序的那一般数组中即可；
// 1. 如果 target 在有序的那一半数组中，则我们直接去这一半数组中寻找即可。
// 2. 如果 target 不在有序的那一半数组中，则我们只需要去另一半数组中去寻找即可。
// 3. 特别小心数组中有大量的重复元素的情形，此时我们需要判断数组的下标 mid 是否和数组的边界相等。如 [1,1,1,1,1,2,3,1,1] 这种情况下我们需要将数组缩短，直到下标 mid 和边界不相等为止。
class Solution {
public:
    int search(vector<int>& arr, int target) {
        int left = 0;
        int right = arr.size() - 1;
        while (left <= right) {
            //当目标不存在
            if (left == right && arr[left] != target) {
                return -1;
            }
            int mid = (left + right) / 2;
            if (arr[mid] == target) {
                while (mid > 0 && arr[mid] == arr[mid - 1]) {
                    mid--;
                }
                if (arr[0] == target) return 0;
                return mid;
            }
            //arr[mid] == arr[left] 则缩短数组左边界
            while (left < mid && arr[mid] == arr[left]) {
                left++;
            }
            //arr[mid] == arr[right] 则缩短数组右边界
            while (right > mid && arr[mid] == arr[right]) {
                right--;
            }
            //左边有序
            if (arr[mid] >= arr[left]) {
                //目标在左边部分
                if (target < arr[mid] && target >= arr[left]) {
                    right = mid - 1;
                }
                else {
                    left = mid + 1;
                }
            }
            else {//右边有序
                //目标在右边部分
                if (target > arr[mid] && target <= arr[right]) {
                    left = mid + 1;
                }
                else {
                    right = mid - 1;
                }
            }
        }
        return -1;
    }
};