#include<iostream>
using namespace std;

// �ҵĽⷨ��˫ָ�룬ʱ�� O(sqrt(c)) 0 ms���ռ� O(1) 5.7 MB 
class Solution {
public:
	bool judgeSquareSum(int c) {
		int left = 0, right = sqrt(c);
		while (left <= right) {
			int aSquare = left * left;
			int bSquare = right * right;
			// ע�⣺����ҪС��aSquare + bSquare > INT_MAX������Ҫ��bSquare����ұ�
			if (aSquare > c - bSquare) {
				--right;
			}
			else if (aSquare < c - bSquare) {
				++left;
			}
			else return true;
		}
		return false;
	}
};

// �ٷ��ⷨ1��ֱ������sqrt������ʱ�� O(sqrt(c)) 4 ms���ռ� O(1) 5.8 MB
class Solution {
public:
	bool judgeSquareSum(int c) {
		for (long a = 0; a * a <= c; ++a) {
			double b = sqrt(c - a * a);
			if (b == static_cast<int>(b)) {
				return true;
			}
		}
		return false;
	}
};

// �ٷ��ⷨ2����ѧ��ʱ�� O(sqrt(c)) 0 ms���ռ� O(1) 5.8 MB
// ������������ǣ�һ���Ǹ�����c����ܹ���ʾΪ����������ƽ���ͣ����ҽ���c����������4k+3�������ӵ��ݾ�Ϊż����
class Solution {
public:
	bool judgeSquareSum(int c) {
		for (int base = 2; base * base <= c; base++) {
			// ����������ӣ�ö����һ��
			if (c % base != 0) {
				continue;
			}

			// ���� base ����
			int exp = 0;
			while (c % base == 0) {
				c /= base;
				exp++;
			}

			// ���� Sum of two squares theorem ��֤
			if (base % 4 == 3 && exp % 2 != 0) {
				return false;
			}
		}

		// ���� 11 ��������������������� for ѭ���� base * base <= c ��base == 11 ��ʱ�򲻻����ѭ����
		// ������˳�ѭ���Ժ���Ҫ����һ���ж�
		return c % 4 != 3;
	}
};