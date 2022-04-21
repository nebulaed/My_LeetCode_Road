#include<iostream>
#include<climits>
using namespace std;

// 我的解法：参考官方快速幂递归方法
//class Solution {
//public:
//	double powResolution(double x, int n) {
//		if (n == 0) return 1.00000;
//		double y = powResolution(x, n / 2);
//		return n % 2 == 0 ? y * y : y * y * x;
//	}
//	double myPow(double x, int n) {
//		return n >= 0 ? powResolution(x, n) : 1 / powResolution(x, -n);
//	}
//};

// 官方解法2：快速幂迭代方法
class Solution {
public:
    double quickMul(double x, long long n) {
        double ret = 1.0;
        // 贡献的初始值为x
        double x_contribute = x;
        // 在对n进行二进制拆分的同时计算答案
        while (n > 0) {
            // 若n二进制表示的最低位为1，那么需要计入贡献
            if (n % 2 == 1) {
                ret *= x_contribute;
            }
            // 将贡献不断平方
            x_contribute *= x_contribute;
            // 舍弃N二进制表示的最低位，这样我们每次只要判断最低位即可
            n /= 2;
        }
        return ret;
    }
    double myPow(double x, int n) {
        long long N = n;
        return N >= 0 ? quickMul(x, N) : 1 / quickMul(x, -N);
    }
};

int main() {
    double x = 1;
    int n = INT_MIN;
    Solution s;
    double ret = s.myPow(x, n);

    cout << ret << endl;

    return 0;
}