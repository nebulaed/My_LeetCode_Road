#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>
using namespace std;

// ������NP��ȫ���⣬�Ҳ�������ʽʱ�临�ӶȵĽⷨ����˱��볢�ԷǶ���ʽʱ�临�ӶȵĽⷨ������ʱ�临�Ӷ���Ԫ�ش�С��صĶ�̬�滮

// �����ת��������һ��ֻ�����������ķǿ�����nums[0]���ж��Ƿ���Դ�������ѡ��һЩ���֣�ʹ����Щ���ֵĺ͵�����������Ԫ�غ͵�һ�롣
// ���������ת����0-1�������⡣

// ��ʹ�ö�̬�滮���֮ǰ���Ƚ��������жϣ�
// 1. ��������ĳ���n�ж������Ƿ���Ա����֡���n < 2����ֱ�ӷ���false
// 2. �������������Ԫ�غ�sum�Լ����Ԫ��maxNum�����sum������������false����sum��ż������target = sum/2����maxNum > target������false

// ������ά����dp������n��target + 1�У�����dp[i][j]��ʾ�������[0, i]�±귶Χ��ѡȡ��������(����0)�����������Ƿ����һ��ѡȡ����ʹ�ñ�ѡȡ���������ĺ͵���j��
// ��ʼʱ��dp�е�ȫ��Ԫ�ض���false��

// �ڶ���״̬����Ҫ���Ǳ߽����������������������ڱ߽������
// 1.ֻҪ��ѡȡ�κ�����������ѡȡ�������;�Ϊ0����˶�������0<=i<n������dp[i][0] = true
// 2.��i==0ʱ��ֻ��һ��������nums[0]�ɱ�ѡȡ�����dp[0][nums[0]] = true

// ����i > 0 �� j > 0����Ҫ�����������������
// 1. ��j >= nums[i]�����ڵ�ǰ����nums[i]����ѡҲ���Բ�ѡ��������ֻҪ��һ��ǰ�����Ϊtrue������dp[i][j] = true
// 1.1 ����ѡȡnums[i]����dp[i][j] = dp[i-1][j]
// 1.2 ��ѡȡnums[i]����dp[i][j] = dp[i-1][j-nums[i]]
// ���ԣ�nums[i] = dp[i-1][j] | dp[i-1][j-nums[i]]
// 2. ��j < nums[i]������ѡȡ�����ֺ͵���j��������޷�ѡȡ��ǰ����nums[i]����ôdp[i][j] = dp[i-1][j]

// �ٷ��ⷨ����̬�滮��ʱ��O(n��target) 256 ms, �ռ�O(n��target) 73.4 MB
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		size_t length = nums.size();
		if (length < 2) return false;
		int sum = accumulate(nums.begin(), nums.end(), 0);
		if (sum & 1) return false;
		int target = sum / 2, maxNum = *max_element(nums.begin(), nums.end());
		if (maxNum > target) return false;
		vector<vector<int>> dp(length, vector<int>(target + 1, 0));
		for (size_t i = 0; i < length; ++i) {
			dp[i][0] = true;
		}
		dp[0][nums[0]] = true;
		for (size_t i = 1; i < length; ++i) {
			for (size_t j = 1; j < target + 1; ++j) {
				if (j >= nums[i]) {
					dp[i][j] = dp[i - 1][j] | dp[i - 1][j - nums[i]];
				}
				else {
					dp[i][j] = dp[i - 1][j];
				}
			}
		}
		return dp[length - 1][target];
	}
};

// �ٷ��ⷨ�Ż�����̬�滮+�������飬ʱ��O(n��target) 88 ms, �ռ�O(target) 9.1 MB
// ��vector<int> ȡ�� bool ���飬ʱ�� 128 ms���ռ� 9.6 MB
class Solution {
public:
	bool canPartition(vector<int>& nums) {
		size_t length = nums.size();
		if (length < 2) return false;
		int sum = 0, maxNum = 0;
		for (int num : nums) {
			sum += num;
			maxNum = max(num, maxNum);
		}
		if (sum & 1) return false;
		int target = sum / 2;
		if (maxNum > target) return false;
		bool* dp = new bool[target + 1]();
		dp[0] = dp[nums[0]] = true;
		for (size_t i = 1; i < length; ++i) {
			// ע�⣺�ò�ѭ����Ҫ�Ӵ�Сѭ��������dp[j-nums[i]]�ѱ�����Ϊ��ǰ���ֵ
			// �ҵ�д����
			//for (size_t j = target; j != -1; --j) {
			//	if (j >= nums[i]) {
			//		dp[j] |= dp[j - nums[i]];
			//	}
			//}
			// �ٷ�д�����ѣ�
			for (size_t j = target; j >= nums[i]; --j) {
				dp[j] |= dp[j - nums[i]];
			}
		}
		return dp[target];
	}
};