#include<iostream>
#include<string>
#include<algorithm>

using std::string;
using std::reverse;


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