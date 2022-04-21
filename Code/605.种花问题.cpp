#include<iostream>
#include<vector>
using namespace std;

// 我的解法：贪心算法，时间 12 ms，空间 19.8 MB
class Solution {
public:
    bool canPlaceFlowers(vector<int>& flowerbed, int n) {
        size_t length = flowerbed.size();
        int count = 0;
        for (size_t i = 0; i < length; ++i) {
            // 若当前位置为0且前面位置为0且后面位置为0，则种花
            if ((i == 0 || !flowerbed[i - 1]) && (i == length - 1 || !flowerbed[i + 1]) && !flowerbed[i]) {
                ++count;
                ++flowerbed[i];
            }
            if (count >= n) return true;
        }
        return false;
    }
};