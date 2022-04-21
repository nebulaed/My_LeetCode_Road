#include<iostream>
using namespace std;

// 我的解法：二分查找，时间 0 ms 100%，空间 5.7 MB 97.69%
class Solution {
private:
    int binarySearch(int maxRoot, int target) {
        int left = 0, right = maxRoot;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (mid * mid > target) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return right;
    }
public:
    int mySqrt(int x) {
        return binarySearch(46340, x);
    }
};

// 官方解法1：二分查找，时间O(log x) 0 ms 100%，空间O(1) 5.9 MB 30%
class Solution {
public:
    int mySqrt(int x) {
        int left = 0, right = x < 46340 ? x : 46340;
        while (left <= right) {
            int mid = (left + right) >> 1;
            if (mid * mid > x) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return right;
    }
};

// 官方解法2：袖珍计算器算法，时间O(1) 4 ms 55.66%，空间O(1) 6.1 MB 5.43%
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }
        int ans = exp(0.5 * log(x));
        return ((long long)(ans + 1) * (ans + 1) <= x ? ans + 1 : ans);
    }
};

// 官方解法3：牛顿迭代，时间O(log x)，空间O(1)
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) {
            return 0;
        }

        double C = x, x0 = x;
        while (true) {
            double xi = 0.5 * (x0 + C / x0);
            if (fabs(x0 - xi) < 1e-7) {
                break;
            }
            x0 = xi;
        }
        return int(x0);
    }
};

// LeetCode 101解法1：二分查找，时间 0 ms 100%，空间 5.9 MB 14.12%
class Solution {
public:
    int mySqrt(int x) {
        if (x == 0) return x;
        int left = 1, right = x, mid, sqrt;
        while (left <= right) {
            // 为避免mid = (left + right) >> 1可能因为left + right溢出int而错误，故改用这种写法
            mid = left + ((right - left) >> 1);
            sqrt = x / mid;
            if (sqrt == mid) {
                return mid;
            }
            else if (mid > sqrt) {
                right = mid - 1;
            }
            else {
                left = mid + 1;
            }
        }
        return right;
    }
};

// LeetCode 101解法2：牛顿迭代法，时间 4 ms 55.66%，空间 5.8 MB 54.36%
class Solution {
public:
    int mySqrt(int x) {
        long root = x;
        while (root * root > x) {
            root = (root + x / root) / 2;
        }
        return root;
    }
};