#include<string>
#include<cmath>
using namespace std;

// 我的解法：时间 4 ms 41.60%，空间 6 MB 14.24%
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int len = columnTitle.size(), ret = 0;
        for (int i = 0; i < len; ++i) {
            ret += (columnTitle[i] - 'A' + 1) * pow(26, len - i - 1);
        }
        return ret;
    }
};

// 我的解法：自己实现int版pow，时间 4 ms 41.60%，空间 5.7 MB 91.18%
class Solution {
private:
    int myPow(int x, unsigned int p)
    {
        if (p == 0) return 1;
        if (p == 1) return x;

        int tmp = myPow(x, p / 2);
        if (p % 2 == 0) return tmp * tmp;
        else return x * tmp * tmp;
    }

public:
    int titleToNumber(string columnTitle) {
        int len = columnTitle.size(), ret = 0;
        const int n = 26;
        for (int i = 0; i < len; ++i) {
            ret += (columnTitle[i] - 'A' + 1) * myPow(26, len - i - 1);
        }
        return ret;
    }
};

// 官方解法：不用每次计算幂，时间 O(n) 4 ms 41.60%，空间 O(1) 5.8 MB 57.37%
class Solution {
public:
    int titleToNumber(string columnTitle) {
        int len = columnTitle.size(), ret = 0;
        for (int i = 0; i < len; ++i) {
            ret = ret * 26 + (columnTitle[i] - 'A' + 1);
        }
        return ret;
    }
};