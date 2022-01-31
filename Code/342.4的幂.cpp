#include<iostream>

// �ҵĽⷨ��ʱ�� O(1) 0 ms 100%���ռ� O(1) 5.9 MB 40.07%
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

// LeetCode 101�ⷨ��˼·ͬ�ϣ�����࣬ʱ�� O(1) 4 ms 38.04%���ռ� O(1) 5.9 MB 42.55%
class Solution {
public:
	bool isPowerOfFour(int n) {
		return n > 0 && !(n & (n - 1)) && (n & 1431655765);
	}
};

// �ٷ��ⷨ����ȡģ���ʣ�ʱ�� O(1) 0 ms 100%���ռ� O(1) 5.9 MB 26.83%
// 4^x = (3 + 1)^x = 1^x = 1 (mod 3)
// ��n��4���ݣ��ᷢ��������3������һ����1����n��2����ȴ����4���ݣ������Ա�ʾΪ4^x��2����ʱ������3������һ��Ϊ2
class Solution {
public:
	bool isPowerOfFour(int n) {
		return n > 0 && !(n & (n - 1)) && n % 3 == 1;
	}
};