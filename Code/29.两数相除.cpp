#include<iostream>
using namespace std;

class Solution {
public:
	// ���ٳ��㷨
	bool quickAdd(int y, int z, int x) {
		int ret = 0, add = y;
		while (z) {
			// ��λ���������z������Ƶ�00000001��λȡ�룬�൱��z%2
			if (z & 1) {
				// �豣֤ret + add >= x
				if (ret < x - add) {
					return false;
				}
				ret += add;
			}
			if (z != 1) {
				// ͬ���豣֤add + add >= x;
				// ����Ͳ�������ַ���
				if (add < x - add) {
					return false;
				}
				add += add;
			}
			// �����ó����������ʾz�Ķ�������������һλ�����һλ��ȥ���൱��z/=2
			z >>= 1;
		}
		return true;
	}

	int divide(int dividend, int divisor) {
		// ���Ǳ�����ΪINT��Сֵ�����
		if (dividend == INT_MIN) {
			if (divisor == 1) {
				return INT_MIN;
			}
			if (divisor == -1) {
				return INT_MAX;
			}
		}
		// ���ǳ���ΪINT��Сֵ�����
		if (divisor == INT_MIN) {
			return dividend == INT_MIN ? 1 : 0;
		}
		// ���Ǳ�����Ϊ0�����
		if (dividend == 0) {
			return 0;
		}

		// һ�������ʹ�ö��ֲ���
		// �����е�����ȡ�෴��������ֻ��Ҫ����һ�����
		bool rev = false;
		if (dividend > 0) {
			dividend = -dividend;
			rev = !rev;
		}
		if (divisor > 0) {
			divisor = -divisor;
			rev = !rev;
		}

		int left = 1, right = INT_MAX, ans = 0;
		while (left <= right) {
			// ע����������Ҳ���ʹ�ó���
			// (right-left)>>1�൱��(right-left)/2
			int mid = left + ((right - left) >> 1);
			bool check = quickAdd(divisor, mid, dividend);
			if (check) {
				ans = mid;
				// ע�����
				if (mid == INT_MAX)
					break;
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return rev ? -ans : ans;		
	}
};