#include<cstdint>

// 我的解法：时间 O(log n) 0 ms 100%，空间 O(1) 5.8 MB 93.19%
class Solution {
public:
    int hammingWeight(uint32_t n) {
        int k = 0;
        while (n) {
            n &= n - 1;
            ++k;
        }
        return k;
    }
};