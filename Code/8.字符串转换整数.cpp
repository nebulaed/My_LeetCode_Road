#include<iostream>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

// �Լ�д�ķ���
//class Solution {
//public:
//	int myAtoi(string s) {
//		while (s[0] == ' ') {
//			s.erase(0, 1);
//		}
//		if (s.size() == 0) {
//			return 0;
//		}
//		bool sgn = true;
//		if (s[0] != '-' && s[0] < '0' && s[0]>'9') {
//			return 0;
//		}
//		if (s[0] == '-') {
//			if (s[1] >= '0' && s[1] <= '9') {
//				s.erase(0, 1);
//				sgn = false;
//			}
//			else {
//				return 0;
//			}
//		}
//		else if (s[0] == '+') {
//			if (s[1] >= '0' && s[1] <= '9') {
//				s.erase(0, 1);
//				sgn = true;
//			}
//			else {
//				return 0;
//			}
//		}
//		int ret = 0;
//		for (int i = 0; i < s.size() && s[i] >= '0' && s[i] <= '9'; ++i) {
//			if (!sgn && (-ret < INT_MIN / 10 || (-ret == INT_MIN / 10 && s[i] >= '8'))) {
//				return INT_MIN;
//			}
//			else if (sgn && (ret > INT_MAX / 10 || (ret == INT_MAX / 10 && s[i] >= '7'))) {
//				return INT_MAX;
//			}
//			ret = ret * 10 + int(s[i] - '0');
//		}
//		if (!sgn) {
//			return -ret;
//		}
//		return ret;
//	}
//};

// �ٷ��ⷨ
class Automation {
	string state = "start";
	unordered_map<string, vector<string>> table = {
		{"start", {"start","signed", "in_number", "end"}},
		{"signed", {"end", "end", "in_number", "end"}},
		{"in_number", {"end", "end", "in_number", "end"}},
		{"end", {"end", "end", "end", "end"}}
	};

	int get_col(char c) {
		// c�ǿո񷵻�0
		if (isspace(c)) return 0;
		// c��+��-����1
		if (c == '+' || c == '-') return 1;
		// c�����ַ���1
		if (isdigit(c)) return 2;
		// �����������3
		return 3;
	}
public:
	// ����λ
	int sign = 1;
	// ���
	long long ans = 0;

	void get(char c) {
		// ͨ������ȡ��ǰ״̬����һ״̬
		state = table[state][get_col(c)];
		if (state == "in_number") {
			ans = ans * 10 + c - '0';
			// �������жϸþ���ֵ���ֵ��INT_MAX����-INT_MIN
			ans = sign == 1 ? min(ans, (long long)INT_MAX) : min(ans, -(long long)INT_MIN);
		}
		else if (state == "signed") {
			sign = c == '+' ? 1 : -1;
		}
	}
};

class Solution {
public:
	int myAtoi(string str) {
		Automation automation;
		for (char c : str) {
			automation.get(c);
		}
		return automation.sign * automation.ans;
	}
};

int main() {
	string input = "4193 with words";

	Solution s;
	int ret = s.myAtoi(input);
	cout << ret << endl;

	system("pause");
	return 0;
}