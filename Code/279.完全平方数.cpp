#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ����̬�滮��ʱ��O(n sqrt(n)) 176 ms���ռ�O(n) 9.3 MB
class Solution {
public:
	int numSquares(int n) {
		vector<int> nums;
		for (int i = 1; i * i <= n; ++i) {
			nums.emplace_back(i * i);
		}
		vector<int> f(n + 1, 0);
		for (int i = 1; i <= n; ++i) {
			int minStep = INT_MAX;
			for (int j = 0; j < nums.size(); ++j) {
				if (i - nums[j] >= 0) {
					minStep = min(minStep, f[i - nums[j]]);
				}
				else break;
			}
			f[i] = minStep + 1;
		}
		return f[n];
	}
};

// �ٷ��ⷨһ����̬�滮��ʱ��O(n sqrt(n)) 72 ms���ռ�O(n) 8.9 MB
class Solution {
public:
	int numSquares(int n) {
		vector<int> f(n + 1);
		for (int i = 1; i <= n; i++) {
			int minn = INT_MAX;
			for (int j = 1; j * j <= i; j++) {
				minn = min(minn, f[i - j * j]);
			}
			f[i] = minn + 1;
		}
		return f[n];
	}
};

// �ٷ��ⷨ������ƽ���Ͷ�������һ�����������Ա�ʾΪ�����ĸ���������ƽ����
// ʱ��O(sqrt(n)) 4 ms���ռ� O(1) 5.8 MB
// ���ҽ���n��4^k*(8m+7)ʱ��n���Ա���ʾΪ����������������ƽ���͡���n=4^k*(8m+7)ʱ��nֻ�ܱ���ʾΪ�ĸ���������ƽ���ͣ���ʱ����4
// ʣ��3�������Ϊ1ʱ��nΪ��ȫƽ����
// ������е�n-a^2(1<=a<=sqrt(n))�Ƿ�Ϊ��ȫƽ����������Ϊ2������Ϊ3
class Solution {
private:
	// �ж��Ƿ�Ϊ��ȫƽ����
	bool isPerfectSquare(int x) {
		int y = sqrt(x);
		return y * y == x;
	}

	bool checkAnswer4(int x) {
		while (x % 4 == 0) {
			x /= 4;
		}
		return x % 8 == 7;
	}

public:
	int numSquares(int n) {
		if (isPerfectSquare(n)) {
			return 1;
		}
		if (checkAnswer4(n)) {
			return 4;
		}
		for (int i = 1; i * i <= n; ++i) {
			int j = n - i * i;
			if (isPerfectSquare(j)) {
				return 2;
			}
		}
		return 3;
	}
};