#include<iostream>
#include<cmath>

using std::fmod;
using std::log10;

//  �ҵĽⷨ��ʱ��O(log_3 n) 20 ms 34.95%���ռ� 5.9 MB 33.51%
class Solution {
public:
	bool isPowerOfThree(int n) {
		while (n >= 3) {
			if (n % 3 != 0) break;
			n /= 3;
		}
		return n == 1;
	}
};

// LeetCode 101�ⷨһ�����ö�����ʱ�� 8 ms 91.91%���ռ� 6 MB 7.24%
// ��log_3^n = m����n��3�������η�����ômһ����������
class Solution {
public:
	bool isPowerOfThree(int n) {
		return fmod(log10(n) / log10(3), 1) == 0;
	}
};

// LeetCode 101�ⷨ����ȡģ��ʱ�� 12 ms 76.27%���ռ� 5.8 MB 63.43%
// int��Χ��3�����η���3^19=1162261467�����n��3�������η���1162261467 % n һ��Ϊ�㡣
class Solution {
public:
	bool isPowerOfThree(int n) {
		return n > 0 && 1162261467 % n == 0;
	}
};