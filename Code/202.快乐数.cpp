#include<iostream>
#include<unordered_set>

using std::unordered_set;

// 我的解法1：哈希集合记录，出现循环即为假，否则为真，时间 4 ms 49.39%，空间 6.1 MB 59.51%
class Solution {
public:
	bool isHappy(int n) {
		unordered_set<int> record;
		while (!record.count(n)) {
			record.emplace(n);
			int sum = 0;
			while (n != 0) {
				int cur = n % 10;
				sum += cur * cur;
				n /= 10;
			}
			if (sum == 1) return true;
			n = sum;
		}
		return false;
	}
};


// 我的解法2：Floyd判圈算法，时间 0 ms 100%，空间 5.9 MB 77.63%
class Solution {
private:
	int sumOfSquare(int n) {
		int sum = 0;
		while (n != 0) {
			int cur = n % 10;
			sum += cur * cur;
			n /= 10;
		}
		return sum;
	}
public:
	bool isHappy(int n) {
		int slow = n, fast = n;
		do {
			slow = sumOfSquare(slow);
			fast = sumOfSquare(sumOfSquare(fast));
			if (fast == 1) return true;
		} while (slow != fast);
		return false;
	}
};


// 官方解法三：9的数位平方和为81，99的数位平方和为162，999的数位平方和为243，可以发现从三位数开始，数位平方和比243小，比999大的数经过多次求数位平方和后必定降回243内，说明数位平方和只有两种可能：
// 1.最终得到1
// 2.在243以下的数里循环
// 经过研究可以发现，只有一个循环：4->16->37->58->89->145->42->20->4
// 其他数字最终都会到达1
class Solution {
private:
	unordered_set<int> cycle{ 4, 16, 37, 58, 89, 145, 42, 20 };
	int sumOfSquare(int n) {
		int sum = 0;
		while (n != 0) {
			int cur = n % 10;
			sum += cur * cur;
			n /= 10;
		}
		return sum;
	}
public:
	bool isHappy(int n) {
		while (!cycle.count(n)) {
			n = sumOfSquare(n);
			if (n == 1) return true;
		}
		return false;
	}
};