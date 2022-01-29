#include<iostream>
using namespace std;

// �ҵĽⷨ��ʱ��O(log C)��C���Ϊ31����Ϊint���Ϊ2^31���ռ�O(1)
class Solution {
public:
	int hammingDistance(int x, int y) {
		int ret = 0;
		while (x != 0 || y != 0) {
			if ((x & 1) != (y & 1)) {
				++ret;
			}
			x >>= 1;
			y >>= 1;
		}
		return ret;
	}
};

// ��ͬ˼·����������֮��ĺ��������Ƕ�Ӧλ�������ֲ�ͬ��λ�������ݶ��壬Ӧʹ��������㣬���ҽ�������λ��ͬʱ���Ϊ1

// �ٷ��ⷨһ������λ�������ܣ�ʱ��O(1) 0 ms���ռ�O(1) 5.9 MB
// ������Ӧ��ֱ��ʹ�����ú���
class Solution {
public:
	int hammingDistance(int x, int y) {
		return __builtin_popcount(x ^ y);
	}
};

// �ٷ��ⷨ������λʵ��λ������ʱ��O(log C) 0 ms���ռ�O(1) 5.9 MB
class Solution {
public:
	int hammingDistance(int x, int y) {
		int s = x ^ y, ret = 0;
		while (s) {
			ret += s & 1;
			s >>= 1;
		}
		return ret;
	}
};

// �ٷ��ⷨ����Brian Kernighan�㷨��ʱ��O(log C) 0 ms���ռ�O(1) 5.9 MB
// �ڷ������У�����s=(10001100)_2���������Ҫѭ������8�β��ܵõ��𰸣�ʵ���Ͽ�����������1֮���0��ֱ�Ӷ�1���м���
// ����x & (x-1)ɾȥ���ұߵ�1��֪��x == 0Ϊֹ���Ϳ��Լ�������ֵ�Ķ����Ʊ�ʾ�е�1����
// Ч�ʱȽⷨ����
class Solution {
public:
	int hammingDistance(int x, int y) {
		int s = x ^ y, ret = 0;
		while (s) {
			s &= s - 1;
			++ret;
		}
		return ret;
	}
};

// LeetCode 101�ⷨ��ʱ�� 0 ms 100%���ռ� 5.8 MB 84.22%
class Solution {
public:
	int hammingDistance(int x, int y) {
		int num = x ^ y, count = 0;
		while (num) {
			++count;
			num &= num - 1;
		}
		return count;
	}
};