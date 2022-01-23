#include<iostream>
#include<vector>
#include<numeric>

using std::vector;
using std::iota;

// LeetCode 101�ⷨ��ʱ�� 0 ms 100%���ռ� 6.3 MB 70.63%
class Solution {
public:
	int minSteps(int n) {
		vector<int> dp(n + 1);
		iota(dp.begin(), dp.end(), 0);
		dp[1] = 0;
		for (int i = 2; i <= n; ++i) {
			// ���ڶ�j > sqrt(i)�������i�ֽ���������õ�����������j��i/j���֮ǰ��i/j��j�ظ������j�оٵ�sqrt(i)����
			// ��12 = 2 * 6��j = 2��i/j = 6��12 = 6 * 2: j = 6, i/j = 2�Ľ������dp[12] = dp[2] + dp[6]
			for (int j = 2; j * j <= i; ++j) {
				// ��i�ܱ�j��������ô����i���ɳ���j�����õ������������ȼ��ڰѳ���Ϊ1��A��չ������Ϊi/j
				// ���磬AAAA��AAAA AAAA AAAA�Ĳ�������A��AAA�Ĳ�����һ��
				if (i % j == 0) {
					dp[i] = dp[j] + dp[i / j];
					break;
				}
			}
		}
		return dp[n];
	}
};