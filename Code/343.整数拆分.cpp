#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// �ٷ����һ����̬�滮��ʱ��O(n^2) 0 ms 100%���ռ�O(n) 6.2 MB 15.55%
// ˼·��dp[i]��ʾ��������i��ֳ����������������ĺ�֮����Щ�����������˻���
// ����0������������1����С��������0��1�����ܲ�֣����dp[0]=dp[1]=0
// ��i>=2ʱ�������������i��ֳ��ĵ�һ����������j(1<=j<i)�����������ַ���:
// 1.��i��ֳ�j��i-j�ĺͣ���i-j���ٲ�ֳɶ������������ʱ�˻���j��(i-j)
// 2.��i��ֳ�j��i-j�ĺͣ���i-j������֣���ʱ�˻���j��dp[i-j]
// ����dp[i] = max(1<=j<i){max(j��(i-j),j��dp[i-j])}
class Solution {
public:
	int integerBreak(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j < i; ++j) {
				dp[i] = max(dp[i], max(j * (i - j), j * dp[i - j]));
			}
		}
		return dp.back();
	}
};

// ���������Ż��Ķ�̬�滮��ʱ�� O(n) 0 ms 100%���ռ� O(n) 6.1 MB 52.80%
// ˼·������dp[i]��ʾ��������i��ֳ����������������ĺ�֮����Щ�����������˻�������dp[i]>=j*dp[i-j]
class Solution {
public:
	int integerBreak(int n) {
		if (n < 4) return n - 1;
		vector<int> dp(n + 1);
		dp[2] = 1;
		for (int i = 3; i <= n; ++i) {
			dp[i] = max(max(2 * (i - 2), 2 * dp[i - 2]), max(3 * (i - 3), 3 * dp[i - 3]));
		}
		return dp[n];
	}
};