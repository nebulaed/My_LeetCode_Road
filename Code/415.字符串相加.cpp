#include<iostream>
#include<string>
using namespace std;

// �ҵĽⷨ��16 ms��6.7 MB
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

// �ҵĽⷨ�ο��ٷ��ⷨ�Ż���4 ms��6.5 MB
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

// �ҵĽⷨ�ο�LeetCode 101��ʱ�� 4 ms 70.82%���ռ� 6.5 MB 91.05%
class Solution {
public:
	string addStrings(string num1, string num2) {
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		string ret;
		int digit = 0, carry = 0, length1 = num1.size(), length2 = num2.size();
		while (digit < length1 || digit < length2 || carry) {
			int cur1 = digit < length1 ? num1[digit] - '0' : 0;
			int cur2 = digit < length2 ? num2[digit] - '0' : 0;
			int curNum = cur1 + cur2 + carry;
			ret += (curNum > 9 ? curNum - 10 : curNum) + '0';
			carry = curNum > 9 ? 1 : 0;
			++digit;
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

// LeetCode 101�ⷨ���ȷ�ת�ַ���������λ���㣬���ת�����ʱ�� 4 ms 70.82%���ռ� 6.6 MB 44.45%
class Solution {
public:
	string addStrings(string num1, string num2) {
		reverse(num1.begin(), num1.end());
		reverse(num2.begin(), num2.end());
		string ret;
		int firstLen = num1.size(), secondLen = num2.size();
		if (firstLen < secondLen) {
			num1.swap(num2);
			swap(firstLen, secondLen);
		}
		int carry = 0;
		for (int i = 0; i < secondLen; ++i) {
			int curSum = (num1[i] - '0') + (num2[i] - '0') + carry;
			ret += (curSum % 10) + '0';
			carry = curSum < 10 ? 0 : 1;
		}
		for (int i = secondLen; i < firstLen; ++i) {
			int curSum = (num1[i] - '0') + carry;
			ret += (curSum % 10) + '0';
			carry = curSum < 10 ? 0 : 1;
		}
		if (carry) {
			ret += '1';
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