#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

// 我的解法一：动态规划，时间 176 ms 53.51%，空间 22.2 MB 57.84%
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int> & lhs, const vector<int> & rhs) {
            return lhs[1] < rhs[1];
        });
        size_t n = pairs.size();
        vector<int> dp(n, 1);
        int maxLength = 0;
        for (size_t i = 1; i <= n; ++i) {
            int& cur = dp[i - 1];
            for (size_t j = i - 1; j > 0; --j) {
                if (pairs[i - 1][0] > pairs[j - 1][1]) {
                    cur = max(dp[j - 1] + 1, cur);
                }
            }
            maxLength = max(maxLength, cur);
        }
        return maxLength;
    }
};

// 我的解法二：动态规划，时间 168 ms 54.73%，空间 22.2 MB 64.73%
class Solution {
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), [](const vector<int> & lhs, const vector<int> & rhs) {
            return lhs[0] < rhs[0];
        });
        size_t n = pairs.size();
        vector<int> dp(n, 1);
        int maxLength = 0;
        for (size_t i = 1; i <= n; ++i) {
            int& cur = dp[i - 1];
            for (size_t j = i - 1; j > 0; --j) {
                if (pairs[i - 1][0] > pairs[j - 1][1]) {
                    cur = max(dp[j - 1] + 1, cur);
                }
            }
            maxLength = max(maxLength, cur);
        }
        return maxLength;
    }
};

// 我的解法三：贪心+二分查找，时间 44 ms 99%，空间 22 MB 74%
// 思路：类似300题最长递增子序列，先将pairs按照右端点排序，将区间的右端点放到endArr中，若在pairs中找到的下一个pair，如果pair的左端点小于endArr的最后一个元素，那么将该pair的右端点也放到endArr最后，如果不小于endArr的最后一个元素，那就在endArr中找到不小于pair右端点的第一个元素，若找得到就将该元素替换为该pair右端点。
// 最后返回endArr的长度
class Solution {
private:
    static bool cmp(const vector<int>& lhs, const vector<int>& rhs) {
        return lhs[1] < rhs[1];
    }
public:
    int findLongestChain(vector<vector<int>>& pairs) {
        sort(pairs.begin(), pairs.end(), cmp);
        size_t n = pairs.size();
        vector<int> endArr{ pairs.front()[1] };
        for (size_t i = 1; i < n; ++i) {
            const auto& pair = pairs[i];
            int lEnd = pair[0], rEnd = pair[1];
            if (endArr.back() < lEnd) {
                endArr.emplace_back(rEnd);
            }
            else {
                auto it = lower_bound(endArr.begin(), endArr.end(), rEnd);
                if (it != endArr.end()) {
                    *it = rEnd;
                }
            }
        }
        return endArr.size();
    }
};