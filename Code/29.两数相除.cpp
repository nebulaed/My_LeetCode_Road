#include<iostream>
#include<climits>

using namespace std;

class Solution {
public:
    // 快速乘算法
    bool quickAdd(int y, int z, int x) {
        int ret = 0, add = y;
        while (z) {
            // 按位与操作，即z与二进制的00000001逐位取与，相当于z%2
            if (z & 1) {
                // 需保证ret + add >= x
                if (ret < x - add) {
                    return false;
                }
                ret += add;
            }
            if (z != 1) {
                // 同样需保证add + add >= x;
                // 否则就不满足二分法了
                if (add < x - add) {
                    return false;
                }
                add += add;
            }
            // 不能用除法，这个表示z的二进制数向右移一位，最后一位舍去，相当于z/=2
            z >>= 1;
        }
        return true;
    }

    int divide(int dividend, int divisor) {
        // 考虑被除数为INT最小值的情况
        if (dividend == INT_MIN) {
            if (divisor == 1) {
                return INT_MIN;
            }
            if (divisor == -1) {
                return INT_MAX;
            }
        }
        // 考虑除数为INT最小值的情况
        if (divisor == INT_MIN) {
            return dividend == INT_MIN ? 1 : 0;
        }
        // 考虑被除数为0的情况
        if (dividend == 0) {
            return 0;
        }

        // 一般情况，使用二分查找
        // 将所有的正数取相反数，这样只需要考虑一种情况
        bool rev = false;
        if (dividend > 0) {
            dividend = -dividend;
            rev = !rev;
        }
        if (divisor > 0) {
            divisor = -divisor;
            rev = !rev;
        }

        int left = 1, right = INT_MAX, ans = 0;
        while (left <= right) {
            // 注意溢出，并且不能使用除法
            // (right-left)>>1相当于(right-left)/2
            int mid = left + ((right - left) >> 1);
            bool check = quickAdd(divisor, mid, dividend);
            if (check) {
                ans = mid;
                // 注意溢出
                if (mid == INT_MAX)
                    break;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return rev ? -ans : ans;
    }
};