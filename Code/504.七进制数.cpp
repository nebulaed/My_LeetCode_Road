#include<iostream>
#include<string>

using std::string;
using std::to_string;

// LeetCode 101解法：利用除法和取余(模)来计算。时间 0 ms 100%，空间 5.8 MB 82%
// 注意负数和零的细节。如果输出是数字不是字符串，要注意考虑是否超出int上下界
class Solution {
public:
	string convertToBase7(int num) {
		if (num == 0) return "0";
		bool negative = num < 0;
		if (negative) num = -num;
		string ret;
		while (num) {
			int a = num / 7, b = num % 7;
			ret.insert(0, to_string(b));
			num = a;
		}
		return (negative ? "-" : "") + ret;
	}
};

