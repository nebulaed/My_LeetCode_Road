#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// 自写解法
class Solution {
public:
	bool isPalindrome(int x) {
		string s = to_string(x);
		int start = 0;
		int median = (s.size() - 1) / 2;
		int len1 = expandAroundCenter(s, median, median);
		int len2 = expandAroundCenter(s, median, median + 1);
		int len = max(len1, len2);
		if (len == s.size()) {
			return true;
		}
		else {
			return false;
		}
	}

	int expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		return right - left - 1;
	}
};

// 官方做法
class Solution {
public:
	bool isPalindrome(int x) {
		// 当x为负数或个位为0(因为首位不可能是0)时，x不可能为回文数
		if (x < 0 || (x % 10 == 0 && x != 0)) {
			return false;
		}

		int revertedNumber = 0;
		while (x > revertedNumber) {
			revertedNumber = revertedNumber * 10 + x % 10;
			x /= 10;
		}
		return x == revertedNumber || x == revertedNumber / 10;
	}
};

int main() {
	int input = 12121;
	
	Solution s;
	bool ret = s.isPalindrome(input);
	if (ret) cout << "true" << endl;
	else cout << "false" << endl;

	system("pause");
	return 0;
}