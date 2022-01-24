#include<iostream>
#include<vector>

using std::vector;
using std::sqrt;

// LeetCode 101解法一：埃氏筛法，时间 220 ms 69.70%，空间 10.1 MB 80.79%
// 思路：将因子从2到n遍历，假设当前遍历到m，把所有小于n的，且是m倍数的整数标为和数，和数必不为质数。
// 遍历结束后，没有被标为和数的数字就是质数。
class Solution {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> prime(n, true);
		// 去掉不是质数的0和1
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

// LeetCode 101解法二：埃氏筛法优化，时间 84 ms 96.25%，空间 10 MB 86.30%
class Solution {
public:
	int countPrimes(int n) {
		if (n <= 2) return 0;
		vector<bool> prime(n, true);
		// 最小质因子一定小于等于开方数
		int i = 3, sqrtN = sqrt(n), count = n / 2;
		while (i <= sqrtN){
			// 避免偶数和重复遍历
			for (int j = i* i; j < n; j += 2 * i) {
				if (prime[j]) {
					prime[j] = false;
					--count;
				}
			}
			do {
				// 避免偶数和重复遍历
				i += 2;
			} while (i <= sqrtN && !prime[i]);
		}
		return count;
	}
};