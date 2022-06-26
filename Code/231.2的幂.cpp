#include<unordered_set>
using namespace std;

// 我的解法：循环，时间 4 ms 32.90%，空间 5.8 MB 43.23%
class Solution {
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        while (n != 1) {
            if (n % 2 == 1) {
                return false;
            }
            n /= 2;
        }
        return true;
    }
};

// 我的解法：查表法，时间 O(1) 8 ms 32.90%，空间 O(31) 7.6 MB 5.34%
class Solution {
private:
    static const unordered_set<int> hashMap;
public:
    bool isPowerOfTwo(int n) {
        if (n <= 0) return false;
        return hashMap.count(n);
    }
};
const unordered_set<int> Solution::hashMap{1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768, 65536,
                                           131072, 262144, 524288, 1048576, 2097152, 4194304, 8388608, 16777216, 33554432, 67108864,
                                           134217728, 268435456, 536870912, 1073741824};

// 官方解法一：二进制表示，时间 O(1) 0 ms 100%，空间 O(1) 5.8 MB 69.29%
class Solution {
public:
    bool isPowerOfTwo(int n) {
        return n > 0 && (n & (n - 1)) == 0;
    }
};

// 官方解法二：判断是否为最大2的幂的约数，时间 O(1) 0 ms 100%，空间 O(1) 5.7 MB 82.62%
class Solution {
private:
    static constexpr int BIG = 1 << 30;
public:
    bool isPowerOfTwo(int n){
        return n > 0 && BIG % n == 0;
    }
};