#include<iostream>

// �ҵĽⷨ������׳�����ĸ�����ʱ�� 0 ms 100%���ռ� 5.8 MB 66.10%
// ˼·����ĸ����������ĸ���
class Solution {
public:
	int trailingZeroes(int n) {
		int ret = 0;
		for (int factor = 5; factor <= n; factor *= 5) {
			ret += n / factor;
		}
		return ret;
	}
};

// LeetCode 101�ⷨ��ͳ�ƽ׳˽����������5�ĸ�����ʱ�� 0 ms 100%���ռ� 5.8 MB 64.23%
class Solution {
public:
	int trailingZeroes(int n) {
		return n == 0 ? 0 : (n / 5 + trailingZeroes(n / 5));
	}
};
