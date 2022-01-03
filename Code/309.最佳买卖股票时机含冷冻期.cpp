#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// �ٷ��ⷨһ����̬�滮��ʱ��O(n) 4 ms���ռ�O(n) 11.3 MB
// ˼·����f[i]��ʾ��i���������ۼ�������档�������⣬���ǻ������ֲ�ͬ״̬��
// 1.����Ŀǰ����һ֧��Ʊ����Ӧ���ۼ���������Ϊf[i][0];
// 2.����Ŀǰ�������κι�Ʊ�Ҵ����䶳�ڣ���Ӧ���ۼ���������Ϊf[i][1];
// 3.����Ŀǰ�������κι�Ʊ���Ҳ������䶳�ڣ���Ӧ���ۼ���������Ϊf[i][2]��
// A. ����f[i][0]��Ŀǰ���ǳ��е���֧��Ʊ���ڵ�i-1����Ѿ����еģ���Ӧ��״̬Ϊf[i-1][0]�������ǵ�i������ģ���ô��i-1�첻�ܳ��й�Ʊ��������Ʊ����Ӧ��״̬Ϊf[i-1][2]���������Ʊ�ĸ�����prices[i]�����״̬ת�Ʒ���Ϊ��
// f[i][0] = max(f[i-1][0], f[i-1][2]-prices[i])
// B. ����f[i][1]���ڵ�i����������䶳��˵�����������˹�Ʊ����ôi-1��س��й�Ʊ����ǰ״̬Ϊf[i-1][0]����������Ʊ��������prices[i]��״̬ת�Ʒ���Ϊ��
// f[i][1] = f[i-1][0] + prices[i]
// ����f[i][2]���ڵ�i�����֮�󲻳����κι�Ʊ���Ҳ������䶳�ڣ�˵������û�н����κβ���������i-1��ʱ�������κι�Ʊ����i-1��Ϊ�䶳�ڣ���״̬Ϊf[i-1][1]���������䶳�ڣ����Ӧ״̬Ϊf[i-1][2]�����״̬ת�Ʒ���Ϊ��
// f[i][2] = max(f[i-1][1], f[i-1][2])
// �������е�״̬ת�Ʒ��̣���ôһ����n�죬���մ�Ϊ
// max(f[n-1][0],f[n-1][1],f[n-1][2])
// �������һ��������Գ��й�Ʊ�޷��������ʽ��Ϊmax(f[n-1][1],f[n-1][2])
// �߽�����Ϊf[0][0]=-prices[0]��f[0][1] = 0, f[0][2] = 0
//
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.empty()) return 0;
		size_t n = prices.size();
		vector<array<int, 3>> f(n, array<int, 3>());
		f[0][0] = -prices[0];
		for (size_t i = 1; i < n; ++i) {
			f[i][0] = max(f[i - 1][0], f[i - 1][2] - prices[i]);
			f[i][1] = f[i - 1][0] + prices[i];
			f[i][2] = max(f[i - 1][1], f[i - 1][2]);
		}
		return max(f[n - 1][1], f[n - 1][2]);
	}
};

// �������飬ʱ��O(n) 0 ms���ռ�O(1) 10.9 MB
class Solution {
public:
	int maxProfit(vector<int>& prices) {
		if (prices.empty()) return 0;
		array<int, 3> f = { 0 };
		f[0] = -prices[0];
		for (int price : prices) {
			int newf2 = max(f[1], f[2]);
			f[1] = f[0] + price;
			f[0] = max(f[0], f[2] - price);
			f[2] = newf2;
		}
		return max(f[1], f[2]);
	}
};