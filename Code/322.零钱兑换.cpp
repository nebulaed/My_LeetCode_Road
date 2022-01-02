#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ������+��̬�滮��ʱ�� 68 ms���ռ� 13.9 MB
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		sort(coins.begin(), coins.end());
		vector<int> dp(amount + 1, 0);
		for (int i = 1; i <= amount; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < coins.size() && i - coins[j] >= 0; ++j) {
				int temp = dp[i - coins[j]];
				if (temp != -1) {
					minStep = min(minStep, temp);
				}
			}
			dp[i] = minStep == INT_MAX ? -1 : minStep + 1;
		}
		return amount == 0 ? 0 : dp[amount];
	}
};

// �ҵĽⷨһ��ʽ����̬�滮��ʱ�� 68 ms���ռ� 14 MB
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> dp(amount + 1, 0);
		for (int i = 1; i <= amount; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < coins.size(); ++j) {
				if (i - coins[j] < 0) continue;
				int temp = dp[i - coins[j]];
				if (temp != -1) {
					minStep = min(minStep, temp);
				}
			}
			dp[i] = minStep == INT_MAX ? -1 : minStep + 1;
		}
		return amount == 0 ? 0 : dp[amount];
	}
};

// �ٷ��ⷨһ�����仯������ʱ��O(Sn) 80 ms���ռ�O(S) 15.6 MB
// ����F(S)Ϊ��ɽ��S���������Ӳ��������[c0 ... cn-1]Ϊ��ѡ��nöӲ�����ֵ
// �ٶ����һöӲ����ֵ��C����ת�Ʒ���ΪF(S) = F(S-C) + 1
// �����ǲ�֪�����һöӲ��C�Ƕ��٣���Ҫö��ÿ��Ӳ�����ֵc0,c1,...,cn-1��ѡ������F(S-C)��С�����ֵ��
class Solution {
private:
	vector<int> count;

	int dp(const vector<int>& coins, int rem) {
		if (rem < 0) return -1;
		else if (rem == 0) return 0;
		// ����ֵ�ѱ��������ֻ��ֱ�ӵ���count�������ŵĶ�Ӧ��ֵ��Ӳ����
		if (count[rem - 1] != 0) return count[rem - 1];
		int minNum = INT_MAX;
		for (int coin : coins) {
			int ret = dp(coins, rem - coin);
			if (ret >= 0 && ret < minNum) {
				minNum = ret + 1;
			}
		}
		count[rem - 1] = minNum == INT_MAX ? -1 : minNum;
		return count[rem - 1];
	}
public:
	int coinChange(vector<int>& coins, int amount) {
		if (amount < 1) return 0;
		count.resize(amount);
		return dp(coins, amount);
	}
};

// �ٷ��ⷨ������̬�滮��ʱ��O(Sn) 80 ms���ռ�O(S) 14 MB
// �������¶��ϵķ�ʽ˼����F(i)����������ͬ��F(i)��ת�Ʒ���Ϊ
// F(i) = min_(j = 0,...,n-1) (F(i-c_j)) + 1
class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		int overVal = amount + 1;
		vector<int> dp(overVal, overVal);
		dp[0] = 0;
		for (int i = 1; i <= amount; ++i) {
			for (int j = 0; j < coins.size(); ++j) {
				if (coins[j] <= i) {
					dp[i] = min(dp[i], dp[i - coins[j]] + 1);
				}
			}
		}
		return dp[amount] > amount ? -1 : dp[amount];
	}
};