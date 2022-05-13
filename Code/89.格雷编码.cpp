#include<vector>
using namespace std;


// 官方解法一：对称生成，时间 O(2^n) 4 ms 88.94%，空间 O(1) 10.9 MB 84.26%
// n = 1 [0, 1]
// n = 2 [00, 01, 11, 10]
// n = 3 [000, 001, 011, 010, 110, 111, 101, 100]
// n每加1，包含的数字数量会翻倍，假设n位格雷码包含c个数，n-1位格雷码包含c'个数，则c = 2c'
// 这时n中的前c'个数是n-1种所有数字前面补0，其实就是一样的
// n种的后c'个数是n-1中所有数字前面补1，然后翻转为逆序
class Solution {
public:
    vector<int> grayCode(int n) {
        vector<int> ret(1 << n);
        ret.front() = 0;
        int m = 1;
        for (int i = 1; i <= n; ++i){
            for (int j = m - 1; j >= 0; --j) {
                ret[2 * m - j - 1] = ret[j] | (1 << (i - 1));
            }
            m <<= 1;
        }
        return ret;
    }
};

// 官方解法二：序号二进制转格雷码，时间 O(2^n) 8 ms 59.86%，空间 O(1) 10.9 MB 78.01%
// 如果我们有一个二进制数序列，我们也可以将它直接转换成格雷码序列。假设n位二进制数为b，对应的格雷码为g，转换规则如下：
// g(i) = b(i + 1) ^ b(i), 0 <= i < n
// 其中^是按位异或运算，g(i)和b(i)分别表示g和b的第i位，且b(n) = 0
// 以n = 3为例，格雷码和序号二进制码为
// [000, 001, 011, 010, 110, 111, 101, 100]
// [000, 001, 010, 011, 100, 101, 110, 111]
// 以序号5，即二进制码为101为例说明，补上b(n) = 0为0101
// 0 1 0 1，b(3)^b(2) = 0 ^ 1 = 1 = g(2), b(2)^b(1) = 1 ^ 0 = 1 = g(1), b(1)^b(0) = 0 ^ 1 = 1 = g(0), 所以格雷码为111
class Solution {
public:
    vector<int> grayCode(int n) {
        int m = 1 << n;
        vector<int> ret(m);
        for (int i = 0; i < m; ++i){
            // i>>1其实将i每一位向后移动一位，这时和i取异或，相当于和自己的后一位取余
            ret[i] = (i >> 1) ^ i;
        }
        return ret;
    }
};