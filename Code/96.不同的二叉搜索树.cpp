#include<iostream>
#include<vector>
using namespace std;

// 官方解法一：动态规划，时间O(n^2) 0 ms，空间O(n) 6 MB(使用int*时为5.8 MB)
class Solution {
public:
	int numTrees(int n) {
		// dp[i]表示长度为i(i=0...n)的序列能构成的不同搜索树的个数
		vector<int> dp(n + 1);
		// 把vector换成动态int数组能减少空间消耗，但会增加时间
		// int* dp = new int[n + 1]();
		// i = 0表示序列长度为0，空树只有一种
		dp[0] = 1;
		// i = 1表示只有根结点的二叉搜索树，只有一种
		dp[1] = 1;
		// 假定F(j,i)表示以第j个节点为根结点、节点总数为i的二叉搜索树个数，那么F(j,i)=dp[j-1]*dp[i-j]，因为以第j个节点为根结点的树个数等于第j个节点的左子树的所有个数×右子树的所有个数，左子树的节点个数为j-1，右子树的节点个数为i-j。且又有dp[i]=F(1,i)+F(2,i)+...+F(i,i)
		for (int i = 2; i <= n; ++i) {
			for (int j = 1; j <= i; ++j) {
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp[n];
	}
};

// 官方解法二：数学，时间O(n) 0 ms，空间O(1) 5.9 MB
// 在解法一中推导出的dp[i]的值即为卡塔兰数，其有更便于计算的定义如下：C_0 = 1, C_{n+1}=2(2n+1)/(n+2)*C_n
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