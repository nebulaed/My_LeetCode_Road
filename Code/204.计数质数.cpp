#include<iostream>
#include<vector>

using std::vector;
using std::sqrt;

// LeetCode 101�ⷨһ������ɸ����ʱ�� 220 ms 69.70%���ռ� 10.1 MB 80.79%
// ˼·�������Ӵ�2��n���������赱ǰ������m��������С��n�ģ�����m������������Ϊ�����������ز�Ϊ������
// ����������û�б���Ϊ���������־���������
class Solution {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> prime(n, true);
		// ȥ������������0��1
		int count = n - 2;
		for (int i = 2; i < n; ++i) {
			if (prime[i]) {
				for (int j = 2 * i; j < n; j += i) {
					if (prime[j]) {
						prime[j] = false;
						--count;
					}
				}
			}
		}
		return count;
	}
};

// LeetCode 101�ⷨ��������ɸ���Ż���ʱ�� 84 ms 96.25%���ռ� 10 MB 86.30%
class Solution {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> prime(n, true);
		// ��С������һ��С�ڵ��ڿ�����
		int i = 3, sqrtN = sqrt(n), count = n / 2;
		while (i <= sqrtN){
			// ����ż�����ظ�����
			for (int j = i* i; j < n; j += 2 * i) {
				if (prime[j]) {
					prime[j] = false;
					--count;
				}
			}
			do {
				// ����ż�����ظ�����
				i += 2;
			} while (i <= sqrtN && !prime[i]);
		}
		return count;
	}
};