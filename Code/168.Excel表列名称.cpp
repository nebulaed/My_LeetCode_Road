#include<iostream>
#include<string>
#include<algorithm>

using std::string;
using std::reverse;

// �ҵĽⷨ������+ȡģ��ʱ�� 0 ms 100%���ռ� 5.6 MB 97.50%
class Solution {
public:
	string convertToTitle(int columnNumber) {
		string ret;
		while (columnNumber != 0) {
			int curr = --columnNumber % 26;
			columnNumber /= 26;
			ret += curr + 'A';
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};