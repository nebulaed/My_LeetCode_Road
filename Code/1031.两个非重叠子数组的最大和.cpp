#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// ���ѽⷨ��ʱ�� 4 ms 79.94%���ռ� 8.6 MB 21.04%
class Solution {
public:
	int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
		int n = nums.size();
		vector<array<int, 4>> dp(n, array<int, 4>{});
		int preSum = 0;
		for (int i = 0; i < firstLen; ++i) {
			preSum += nums[i];
		}
		int maxSum = preSum;
		dp[firstLen - 1][0] = maxSum;
		for (int i = firstLen; i < n; ++i) {
			preSum -= nums[i - firstLen];
			preSum += nums[i];
			maxSum = max(maxSum, preSum);
			dp[i][0] = maxSum;
		}
		preSum = 0;
		for (int i = 0; i < secondLen; ++i) {
			preSum += nums[i];
		}
		maxSum = preSum;
		dp[secondLen - 1][1] = maxSum;

		for (int i = secondLen; i < n; ++i) {
			preSum -= nums[i - secondLen];
			preSum += nums[i];
			maxSum = max(maxSum, preSum);
			dp[i][1] = maxSum;
		}
		preSum = 0;
		for (int i = n - 1; i >= n - firstLen; --i)
		{
			preSum += nums[i];
		}
		maxSum = preSum;
		dp[n - firstLen][2] = maxSum;
		for (int i = n - firstLen - 1; i >= 0; --i)
		{
			preSum -= nums[i + firstLen];
			preSum += nums[i];
			maxSum = max(maxSum, preSum);
			dp[i][2] = maxSum;
		}

		preSum = 0;
		for (int i = n - 1; i >= n - secondLen; --i)
		{
			preSum += nums[i];
		}
		maxSum = preSum;
		dp[n - secondLen][3] = maxSum;
		for (int i = n - secondLen - 1; i >= 0; --i)
		{
			preSum -= nums[i + secondLen];
			preSum += nums[i];
			maxSum = max(maxSum, preSum);
			dp[i][3] = maxSum;
		}

		//�����
		int res = 0;
		//L��secondLen���
		for (int i = firstLen; i <= n - secondLen; ++i)
			res = max(res, dp[i - 1][0] + dp[i][3]);
		//secondLen��L���
		for (int i = secondLen; i <= n - firstLen; ++i)
			res = max(res, dp[i - 1][1] + dp[i][2]);

		return res;
	}
};

// lee215�ⷨ��ʱ�� 4 ms 79.94%���ռ� 8.3 MB 80.26%
class Solution {
public:
	int maxSumTwoNoOverlap(vector<int>& nums, int firstLen, int secondLen) {
		int n = nums.size();
		// ��ǰ׺��
		for (int i = 1; i < n; ++i)
			nums[i] += nums[i - 1];
		//��ʼ���������ֵ�ĳ�ʼֵ����ʼ��firstLen����������ֵ����ʼֵ��secondLen����������ֵ
		//��ʼ������ǰ׺�����������㵱ǰ�����鳤�������ߵļ���Ԫ��ֵ
		int res = nums[firstLen + secondLen - 1], firstMax = nums[firstLen - 1], secondMax = nums[secondLen - 1];
		for (int i = firstLen + secondLen; i < n; ++i) {
			//��ǰ����������飬�ҳ���ΪfirstLen�����������ͣ���ʱ��ģ��firstLen������secondLen������ߣ�nums[i - secondLen]�ǵ�ǰλ�ã�secondLen����������֮ǰ�ĵ�һ��Ԫ��
			firstMax = max(firstMax, nums[i - secondLen] - nums[i - firstLen - secondLen]);
			//��ǰ����������飬�ҳ���ΪM�����������ͣ���ʱ��ģ��M������L������ߣ�A[i - L]�ǵ�ǰλ�ã�L����������֮ǰ�ĵ�һ��Ԫ��
			secondMax = max(secondMax, nums[i - firstLen] - nums[i - firstLen - secondLen]);
			//�Ƚ�firstLen����ߵ����ֵ+�����һ��secondLen������ͣ�secondLen����߲�ȡ���ֵ+�����һ��L�������
			res = max(res, max(firstMax + nums[i] - nums[i - secondLen], secondMax + nums[i] - nums[i - firstLen]));
		}
		return res;
	}
};