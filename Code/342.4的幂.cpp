#include<iostream>

// �ҵĽⷨ��ʱ�� 0 ms 100%���ռ� 5.9 MB 40.07%
class Solution {
public:
	bool isPowerOfFour(int n) {
		// ��nС�ڵ���0���ز���4����
		if (n <= 0) return false;
		// ��n�Ķ����Ʋ�ֻ��һ��1���ز���4����
		if (n & (n - 1)) return false;
		// ����λ(1),10101010 10101010 10101010 1010101
		const int M4 = 1431655765;
		// ��n�Ķ�����ֻ��һ��1��ǰ���£�ֻҪ���1��M4�е�1��λ�ã�����4����
		if (n & M4) return true;
		else return false;
	}
};

// LeetCode 101�ⷨ��˼·ͬ�ϣ�����࣬ʱ�� 4 ms 38.04%���ռ� 5.9 MB 42.55%
class Solution {
public:
	bool isPowerOfFour(int n) {
		return n > 0 && !(n & (n - 1)) && (n & 1431655765);
	}
};