#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ����̬�滮��ʱ�� 4 ms���ռ� 7.6 MB
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			int minOne = INT_MAX;
			for (int j = 1; j <= i; j *= 2) {
				minOne = min(minOne, dp[i - j]);
			}
			dp[i] = minOne + 1;
		}
		return dp;
	}
};

// �ҵĽⷨ������̬�滮+��ѧ��ʱ�� 8 ms���ռ� 7.7 MB
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i - pow(2, static_cast<int>(log2(i)))] + 1;
		}
		return dp;
	}
};

// �ٷ��ⷨһ��Brian Kernighan�㷨��ʱ��O(n log n) 4 ms���ռ�O(1) 7.8 MB
// ������������x����x = x & (x - 1)�����㷨��x�Ķ����Ʊ�ʾ�����һ��1���0����x�ظ��ò�����ֱ��x���0������������Ϊx��һ��������
class Solution {
private:
	int countOnes(int x) {
		int ones = 0;
		while (x > 0) {
			x &= (x - 1);
			++ones;
		}
		return ones;
	}
public:
	vector<int> countBits(int n) {
		vector<int> bits(n + 1, 0);
		for (int i = 0; i <= n; ++i) {
			bits[i] = countOnes(i);
		}
		return bits;
	}
};

// �ٷ��ⷨ������̬�滮���������Чλ��ʱ��O(n) 4 ms���ռ�O(1) 7.7 MB
// ˼·��������i��һ������ʱ��������0<=j<i��j��һ��������֪����i��j��ȣ�i�Ķ����Ʊ�ʾֻ����һ��1����ɿ��ٵõ�i��һ������
// ��bits[i]��ʾi��һ����������bits[i] = bits[j] + 1
// ��������x����֪������������y��ʹ��y<=x��y��2���������ݣ���y�Ķ����Ʊ�ʾ��ֻ�����λ��1�����඼Ϊ0��y��Ϊx�������Чλ��
// ��z = x - y����Ȼ0<=z<x����bits[x] = bits[z] + 1
// һ���������ǲ���2���������ݣ�����ͨ��y&(y-1) == 0�ж�
// ��highBit��ʾ��ǰ�������Чλ��������1��n��ÿ��������i���������²���
// 1.��i&(i-1)==0������highBit = i�����µ�ǰ�����Чλ
// 2.��bits[i]��bits[i-highBit]��1�������Ǵ�С�����������bits[i-highBit]��֪����bits[i] = bits[i-highBit] + 1
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		int highBit = 0;
		for (int i = 1; i <= n; ++i) {
			if (i & (i - 1) == 0) {
				highBit = i;
			}
			dp[i] = dp[i - highBit] + 1;
		}
		return dp;
	}
};

// �ٷ��ⷨ������̬�滮���������Чλ��ʱ��O(n) 4 ms���ռ�O(1) 7.7 MB
// ��������x���������������һλ���õ�int(x/2)����bits(int(x/2))�����֪��bits[x]:
// 1.��x��ż����bits[x] = bits[int(x/2)]
// 2.��x��������bits[x] = bits[int(x/2)] + 1
// ������������Ժϲ���bits[x] = bits[int(x/2)] + x % 2
// �ö������㷨��bits[x] = bits[x>>1] + (x & 1)
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i >> 1] + (i & 1);
		}
		return dp;
	}
};

// �ٷ��ⷨ�ģ���̬�滮�����������λ��ʱ��O(n) 4 ms���ռ�O(1) 7.6 MB
// ����������x���������λλx�Ķ����Ʊ�ʾ����͵�1����λ����10�Ķ����Ʊ�ʾ��1010���������λΪ2
// ��y = x & (x - 1)����yΪ��x���������λ��1��0���������Ȼ0<=y<x��bits[x] = bits[y] + 1��
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i & (i - 1)] + 1;
		}
		return dp;
	}
};

// ֱ��ʹ�����ú�����ʱ�� 0 ms 100%���ռ� 7.8 MB 36.09%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> ret(n + 1);
		for (int i = 0; i <= n; ++i) {
			ret[i] = __builtin_popcount(i);
		}
		return ret;
	}
};

// LeetCode 101�ⷨ��ʱ�� 8 ms 24.79%���ռ� 7.7 MB 50.06%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = i & 1 ? dp[i - 1] + 1 : dp[i >> 1];
		}
		return dp;
	}
};


// LeetCode 101�ⷨ��ʱ�� 4 ms 86.73%���ռ� 7.8 MB 40.80%
class Solution {
public:
	vector<int> countBits(int n) {
		vector<int> dp(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			dp[i] = dp[i & (i - 1)] + 1;
		}
		return dp;
	}
};