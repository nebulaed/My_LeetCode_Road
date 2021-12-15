#include<iostream>
using namespace std;

// �ҵĽⷨ���ο��ٷ������ݵݹ鷽��
//class Solution {
//public:
//	double powResolution(double x, int n) {
//		if (n == 0) return 1.00000;
//		double y = powResolution(x, n / 2);
//		return n % 2 == 0 ? y * y : y * y * x;
//	}
//	double myPow(double x, int n) {
//		return n >= 0 ? powResolution(x, n) : 1 / powResolution(x, -n);
//	}
//};

// �ٷ��ⷨ2�������ݵ�������
class Solution {
public:
	double quickMul(double x, long long n) {
		double ret = 1.0;
		// ���׵ĳ�ʼֵΪx
		double x_contribute = x;
		// �ڶ�n���ж����Ʋ�ֵ�ͬʱ�����
		while (n > 0) {
			// ��n�����Ʊ�ʾ�����λΪ1����ô��Ҫ���빱��
			if (n % 2 == 1) {
				ret *= x_contribute;
			}
			// �����ײ���ƽ��
			x_contribute *= x_contribute;
			// ����N�����Ʊ�ʾ�����λ����������ÿ��ֻҪ�ж����λ����
			n /= 2;
		}
		return ret;
	}
	double myPow(double x, int n) {
		long long N = n;
		return N >= 0 ? quickMul(x, N) : 1 / quickMul(x, -N);
	}
};

int main() {
	double x = 1;
	int n = INT_MIN;
	Solution s;
	double ret = s.myPow(x, n);

	cout << ret << endl;

	system("pause");
	return 0;
}