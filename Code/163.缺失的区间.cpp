#include<vector>
#include<string>
using namespace std;

// 我的解法：遍历nums，时间 0 ms 100%，空间 6.7 MB 77.07%
class Solution {
public:
    vector<string> findMissingRanges(vector<int>& nums, int lower, int upper) {
        vector<string> ret;
        if (nums.empty()) {
            if (upper == lower) {
                ret.emplace_back(to_string(lower));
            } else {
                ret.emplace_back(to_string(lower) + "->" + to_string(upper));
            }
            return ret;
        }
        if (lower != nums[0]) {
            if (lower + 1 != nums[0]) {
                ret.emplace_back(to_string(lower) + "->" + to_string(nums[0] - 1));
            } else {
                ret.emplace_back(to_string(lower));
            }
        }
        for (size_t i = 0, n = nums.size(); i < n - 1; ++i) {
            int curr = nums[i], next = nums[i + 1];
            if (curr + 1 != next) {
                if (curr + 2 != next) {
                    ret.emplace_back(to_string(curr + 1) + "->" + to_string(next - 1));
                } else {
                    ret.emplace_back(to_string(curr + 1));
                }
            }
        }
        if (upper != nums.back()) {
            if (upper != nums.back() + 1) {
                ret.emplace_back(to_string(nums.back() + 1) + "->" + to_string(upper));
            } else {
                ret.emplace_back(to_string(upper));
            }
        }
        return ret;
    }
};