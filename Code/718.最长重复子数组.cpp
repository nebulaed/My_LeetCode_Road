#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ����̬�滮��ʱ�� O(mn) 296 ms 58%���ռ� O(mn) 106.5 MB 36%
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        int maxLength = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                    maxLength = max(dp[i][j], maxLength);
                }
                else {
                    dp[i][j] = 0;
                }
            }
        }
        return maxLength;
    }
};

// �ҵĽⷨ2����̬�滮+�������飬ʱ��O(mn) 208 ms 84.26%���ռ� O(n) 11.5 MB 85%
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        vector<int> dp(n + 1, 0);
        int maxLength = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = n; j > 0; --j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    maxLength = max(dp[j], maxLength);
                }
                else {
                    dp[j] = 0;
                }
            }
        }
        return maxLength;
    }
};

// �ҵĽⷨ3����̬�滮+��������С�Ż���ʱ��O(mn) 192 ms 85.88%���ռ� O(min{m,n}) 11.4 MB 94.06%
class Solution {
public:
    int findLength(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        bool reversed = false;
        if (m < n) {
            swap(m, n);
            reversed = true;
        }
        vector<int> dp(n + 1, 0);
        int maxLength = 0;
        for (int i = 1; i <= m; ++i) {
            for (int j = n; j > 0; --j) {
                if (reversed ? nums1[j - 1] == nums2[i - 1] : nums1[i - 1] == nums2[j - 1]) {
                    dp[j] = dp[j - 1] + 1;
                    maxLength = max(dp[j], maxLength);
                }
                else {
                    dp[j] = 0;
                }
            }
        }
        return maxLength;
    }
};