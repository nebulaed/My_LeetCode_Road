#include<iostream>
#include<string>

using std::string;
using std::to_string;

// LeetCode 101�ⷨ�����ó�����ȡ��(ģ)�����㡣ʱ�� 0 ms 100%���ռ� 5.8 MB 82%
// ע�⸺�������ϸ�ڡ������������ֲ����ַ�����Ҫע�⿼���Ƿ񳬳�int���½�
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

