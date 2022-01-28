#include<iostream>
#include<string>
#include<algorithm>

using std::string;
using std::reverse;

// 我的解法：除法+取模，时间 0 ms 100%，空间 5.6 MB 97.50%
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