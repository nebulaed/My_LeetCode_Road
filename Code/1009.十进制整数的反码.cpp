#include<iostream>

// �ҵĽⷨһ��ʱ�� 0 ms 100%���ռ� 5.8 MB 41.34%
class Solution {
public:
	int bitwiseComplement(int n) {
		if (n == 0) return 1;
		int mask = n;
		mask |= mask >> 1;
		mask |= mask >> 2;
		mask |= mask >> 4;
		mask |= mask >> 8;
		mask |= mask >> 16;
		return ~n & mask;
		// return n ^ mask; // Ч����������ͬ
	}
};

// �ҵĽⷨ����ʱ�� 0 ms 100%���ռ� 5.8 MB 67.01%
class Solution {
public:
	int bitwiseComplement(int n) {
		int digit = (n == 0 ? 0 : static_cast<int>(log2(n))) + 1;
		int mask = digit >= 31 ? INT_MAX : (1 << digit) - 1;
		return n ^ mask;
	}
};