#include<iostream>
#include<vector>

using namespace std;

// LeetCode 101解法一：Fisher-Yates洗牌算法，正向洗牌，时间 112 ms 36.93%，空间 88.1 MB 65.02%
// 原理是通过随机交换位置来实现随机打乱
class Solution {
private:
    vector<int> memory;
public:
    Solution(vector<int>& nums) : memory(nums) {}
    // 使用std::move能把时间加快到96 ms 77.71%
    //Solution(vector<int>& nums) : memory(move(nums)) {}

    vector<int> reset() {
        return memory;
    }

    vector<int> shuffle() {
        if (memory.empty()) return {};
        vector<int> shuffled(memory);
        int n = memory.size();
        // 正向洗牌
        for (int i = 0; i < n; ++i) {
            int pos = rand() % (n - i);
            swap(shuffled[i], shuffled[i + pos]);
        }
        return shuffled;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(nums);
 * vector<int> param_1 = obj->reset();
 * vector<int> param_2 = obj->shuffle();
 */

// LeetCode 101解法二：Fisher-Yates洗牌算法，反向洗牌，时间 116 ms 29.94%，空间 88 MB 83.66%
class Solution {
private:
    vector<int> memory;
public:
    Solution(vector<int>& nums) : memory(nums) {}
    // 使用std::move后，时间 100 ms 67.10%，空间 88.2 MB 22.06%
    //Solution(vector<int>& nums) : memory(move(nums)) {}

    vector<int> reset() {
        return memory;
    }

    vector<int> shuffle() {
        if (memory.empty()) return {};
        vector<int> shuffled(memory);
        int n = memory.size();
        // 反向洗牌
        for (int i = n - 1; i >= 0; --i) {
            swap(shuffled[i], shuffled[rand() % (i + 1)]);
        }
        return shuffled;
    }
};
