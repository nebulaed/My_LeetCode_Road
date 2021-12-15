#include<iostream>
#include<string>
using namespace std;

// 我的解法：16 ms，6.7 MB
class Solution {
public:
	string addStrings(string num1, string num2) {
		string ret = "";
		int digit = 1;
		int n1 = num1.size(), n2 = num2.size(), carry = 0;
		int this1, this2, this_num;
		while (n1 - digit >= 0 || n2 - digit >= 0 || carry) {
			this1 = n1 - digit >= 0 ? num1[n1 - digit] - '0' : 0;
			this2 = n2 - digit >= 0 ? num2[n2 - digit] - '0' : 0;
			this_num = this1 + this2 + carry;
			ret.insert(0, 1, this_num > 9 ? this_num - 10 + '0' : this_num + '0');
			carry = this_num > 9 ? 1 : 0;
			++digit;
		}
		return ret;
	}
};

// 我的解法参考官方解法优化：4 ms，6.5 MB
class Solution {
public:
	string addStrings(string num1, string num2) {
		string ret = "";
		int digit = 1;
		int n1 = num1.size(), n2 = num2.size(), carry = 0;
		while (n1 - digit >= 0 || n2 - digit >= 0 || carry) {
			int this1 = n1 - digit >= 0 ? num1[n1 - digit] - '0' : 0;
			int this2 = n2 - digit >= 0 ? num2[n2 - digit] - '0' : 0;
			int this_num = this1 + this2 + carry;
			ret += this_num > 9 ? this_num - 10 + '0' : this_num + '0';
			carry = this_num > 9 ? 1 : 0;
			++digit;
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

int main() {
	string num1 = "456";
	string num2 = "777";

	Solution s;
	string ret = s.addStrings(num1, num2);

	cout << ret << endl;
	system("pause");
	return 0;
}