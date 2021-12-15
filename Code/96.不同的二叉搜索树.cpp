#include<iostream>
#include<vector>
using namespace std;

// �ٷ��ⷨһ����̬�滮��ʱ��O(n^2) 0 ms���ռ�O(n) 6 MB(ʹ��int*ʱΪ5.8 MB)
class Solution {
public:
	int numTrees(int n) {
		// dp[i]��ʾ����Ϊi(i=0...n)�������ܹ��ɵĲ�ͬ�������ĸ���
		vector<int> dp(n + 1);
		// ��vector���ɶ�̬int�����ܼ��ٿռ����ģ���������ʱ��
		// int* dp = new int[n + 1]();
		// i = 0��ʾ���г���Ϊ0������ֻ��һ��
		dp[0] = 1;
		// i = 1��ʾֻ�и����Ķ�����������ֻ��һ��
		dp[1] = 1;
		// �ٶ�F(j,i)��ʾ�Ե�j���ڵ�Ϊ����㡢�ڵ�����Ϊi�Ķ�����������������ôF(j,i)=dp[j-1]*dp[i-j]����Ϊ�Ե�j���ڵ�Ϊ���������������ڵ�j���ڵ�������������и����������������и������������Ľڵ����Ϊj-1���������Ľڵ����Ϊi-j��������dp[i]=F(1,i)+F(2,i)+...+F(i,i)
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp[n];
	}
};

// �ٷ��ⷨ������ѧ��ʱ��O(n) 0 ms���ռ�O(1) 5.9 MB
// �ڽⷨһ���Ƶ�����dp[i]��ֵ��Ϊ�������������и����ڼ���Ķ������£�C_0 = 1, C_{n+1}=2(2n+1)/(n+2)*C_n
class Solution {
public:
	int numTrees(int n) {
		long long C = 1;
		for (int i = 0; i < n; ++i) {
			C *= 2 * (2 * i + 1) / (i + 2);
		}
		return int(C);
	}
};