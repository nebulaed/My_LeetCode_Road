#include<iostream>
#include<vector>
#include<unordered_map>

using namespace std;

// LeetCode 101解法：分治+记忆化，时间 0 ms 100%，空间 7.8 MB 83.85%
// 1. 题目要求A[k]*2 != A[i] + A[j], 对任意i<k<j，可知等式左边为偶数，只要令A[i]+A[j]为奇数，可保证不成立
// 由于奇数+偶数=奇数，令A[i]和A[j]一个为奇数一个为偶数即可，可令A[i]为奇数，A[j]为偶数。
// 也就是要新建一个数组，长度为n，所有奇数都在前半部分，偶数都在后半部分。
// 2. 若一个数组为漂亮数组，其线性变换后的数组也是漂亮数组，如果[x1,x2,x3]是一个漂亮数组，那么[k*x1+b，k*x2+b,k*x3+b]也是漂亮数组
// 3. 对于从1到n的所有整数，奇数个数为(n+1)/2，偶数个数为n/2
// 3.1 对于从1到(n+1)/2的所有整数x，得出其漂亮数组，并映射成1到n范围内的所有奇数2*x-1
// 3.2 对于1到n/2的所有整数x，得出其漂亮数组，并映射成1到n范围内的所有偶数2*x
// 4. 从1到(n+1)/2以及1到n/2范围的漂亮数组，是进一步递归得到的。可以利用哈希表记录已计算的大小为n的漂亮数组。
class Solution {
private:
    unordered_map<int, vector<int>> memory;
public:
    vector<int> beautifulArray(int n) {
        if (memory.count(n)) {
            return memory[n];
        }

        vector<int> ret(n);
        if (n == 1) ret[0] = 1;
        else {
            int ind = 0;
            for (int x : beautifulArray((n + 1) / 2)) {
                ret[ind++] = 2 * x - 1;
            }
            for (int x : beautifulArray(n / 2)) {
                ret[ind++] = 2 * x;
            }
        }
        memory[n] = ret;
        return ret;
    }
};

int main() {

    Solution s;
    vector<int> ret = s.beautifulArray(5);

    cout << "[";
    for (int num : ret) {
        cout << num << ",";
    }
    cout << "]" << endl;

    return 0;
}