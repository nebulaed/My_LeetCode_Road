#include<iostream>
#include<string>
#include<algorithm>

using std::string;
using std::reverse;

// �ҵĽⷨ����415��ⷨ���ƣ�ʱ�� 4 ms 52.84%���ռ� 6.1 MB 86.68%
class Solution {
public:
	string addBinary(string a, string b) {
		string ret;
		int digit1 = a.size() - 1, digit2 = b.size() - 1, carry = 0;
		while (digit1 >= 0 || digit2 >= 0 || carry) {
			int cur1 = digit1 >= 0 ? a[digit1] - '0' : 0;
			int cur2 = digit2 >= 0 ? b[digit2] - '0' : 0;
			int curNum = cur1 + cur2 + carry;
			ret += (curNum & 1) + '0';
			carry = curNum >> 1;
			--digit1;
			--digit2;
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};