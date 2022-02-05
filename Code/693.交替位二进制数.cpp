#include<iostream>
#include<cmath>

using std::log2;

// �ҵĽⷨһ��λ���㣬ʱ�� 0 ms 100%���ռ� 5.9 MB 12.67%
// ����λ����������101�����ƺ�Ϊ010������������Ϊ111������2^(log2(101)+1) - 1��1000 - 1 = 111��ȣ�˵����ǰ��Ϊ����λ��������
// ����ǰ�����ǽ���λ����������100�����ƺ�Ϊ010������������Ϊ110����2^(log2(100)+1) - 1�� 111 �����
class Solution {
public:
	bool hasAlternatingBits(int n) {
		int ret = n ^ (n >> 1);
		int digit = static_cast<int>(log2(n)) + 1;
		int j = digit >= 31 ? INT_MAX : (1 << digit) - 1;
		return ret == j;
	}
};

// �ҵĽⷨ����λ���㣬ʱ�� 0 ms 100%���ռ� 5.8 MB 39.41%
// 101��010�����Ϊ111��111 + 1��Ϊ1000��1000 & (1000 - 1) = (111 + 1) & 111���ǽ�1000���һλ1��Ϊ�㣬���Ϊ0
// ��˵����(n ^ (n >> 1) + 1) & (n ^ (n >> 1))Ϊ0����nΪ����λ��������
// ע�����n ^ (n >> 1) == INT_MAX�ı߽����
class Solution {
public:
	bool hasAlternatingBits(int n) {
		int ret = n ^ (n >> 1);
		return ret == INT_MAX || !((ret + 1) & ret);
	}
};