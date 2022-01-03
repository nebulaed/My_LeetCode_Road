#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

// �ҵĽⷨһ��ջ��ʱ��O(S+|s|) 0 ms���ռ�O(S) 6.1 MB
class Solution {
public:
	string decodeString(string s) {
		// ret����������ս����cur������ŵ�ǰ[]���ַ�����curNum������ŵ�ǰ����
		string ret, cur, curNum;
		// stkFreq�������[]ǰ���֣���ʾ[]���ַ����ظ�����
		stack<int> stkFreq;
		// stkStr�������[]���ַ���
		stack<string> stkStr;
		for (size_t i = 0; i < s.size();) {
			curNum.clear();
			while (isdigit(s[i])) {
				curNum += s[i];
				// ����һ���ַ��������֣���ɽ�curNum�ڴ�ŵ��ַ���תΪ���֣��Ž�stkFreq��
				if (!isdigit(s[i + 1])) {
					stkFreq.emplace(stoi(curNum));
					curNum.clear();
				}
				++i;
			}
			// ����ǰ�ַ�Ϊ[����stkStr�з�����ַ���
			if (s[i] == '[') {
				stkStr.emplace("");
				++i;
			}
			cur.clear();
			// ��s[i]��Сд��ĸ�����뵱ǰ[]���ַ���cur��
			while (s[i] >= 'a' && s[i] <= 'z') {
				cur += s[i];
				++i;
			}
			// ��s[i]����]��iС��s���ȣ�����Сд��ĸ��Ҳ����ζ��������
			if (s[i] != ']' && i < s.size()) {
				// ��stkStrΪ�գ���cur����stkStr��
				if (stkStr.empty()) stkStr.emplace(cur);
				// ����stkStr��ջ������cur
				else stkStr.top() += cur;
				continue;
			}
			// ��stkFreq��Ϊ����s[i]��]
			while (!stkFreq.empty() && s[i] == ']') {
				// stkStr��ջ������cur
				stkStr.top() += cur;
				cur.clear();
				// cur = stkFreq.top()��stkStr.top()�ظ�
				string temp = stkStr.top();
				for (int i = 0; i < stkFreq.top(); ++i) {
					cur += temp;
				}
				stkFreq.pop();
				stkStr.pop();
				++i;
				// ��stkStr��Ϊ��
				if (!stkStr.empty()) {
					cur = stkStr.top() + cur;
					stkStr.pop();
					// ����ǰ�ַ�Ϊ]����ΪstkStr����һ�����ַ���������stkStr��stkFreq���Ȳ���
					if (s[i] == ']') stkStr.emplace("");
				}
			}
			if (stkFreq.empty()) ret += cur;
			// ��stkFreq��Ϊ�գ�˵������[ûƥ����]����˽�cur����stkStr��
			else stkStr.emplace(cur);
		}
		return ret;
	}
};


// �ٷ��ⷨһ��ջ������ʱ��O(S+|s|) 0 ms, �ռ�O(S) 6.5 MB
// ���������ַ�����
// 1.����ǰ�ַ�Ϊ��λ��������һ������(�����Ķ����λ)����ջ
// 2.����ǰ���ַ�Ϊ��ĸ�������ţ���ջ
// 3.����ǰ�ַ�Ϊ�����ţ���ʼ��ջ��һֱ�������ų�ջ����ջ���з�ת��ƴ�ӳ�һ���ַ�������ʱȡջ�������֣���������ַ���Ӧ�ó��ֵĴ�����
class Solution {
private:
	string getDigits(const string& s, size_t& ptr) {
		string ret = "";
		while (isdigit(s[ptr])) {
			ret += s[ptr++];
		}
		return ret;
	}

	string getString(const vector<string>& vec) {
		string ret;
		for (const auto& s : vec) {
			ret += s;
		}
		return ret;
	}
public:
	string decodeString(string s) {
		vector<string> stk;
		size_t ptr = 0;
		while (ptr < s.size()) {
			char cur = s[ptr];
			if (isdigit(cur)) {
				// ��ȡһ�����ֲ���ջ
				string digits = getDigits(s, ptr);
				stk.emplace_back(digits);
			}
			else if (isalpha(cur) || cur == '[') {
				// ��ȡһ����ĸ����ջ
				stk.emplace_back(string(1, s[ptr++]));
			}
			else {
				++ptr;
				vector<string> sub;
				while (stk.back() != "[") {
					sub.emplace_back(stk.back());
					stk.pop_back();
				}
				reverse(sub.begin(), sub.end());
				// �����ų�ջ
				stk.pop_back();
				// ��ʱջ��Ϊ��ǰsub��Ӧ���ַ���Ӧ�ó��ֵĴ���
				int repTime = stoi(stk.back());
				stk.pop_back();
				// tΪ�գ�oΪ[]���ַ���
				string t, o = getString(sub);
				// t=repTime*o
				while (repTime--) t += o;
				stk.emplace_back(t);
			}
		}
		return getString(stk);
	}
};

// �ٷ��ⷨ�����ݹ飬ʱ��O(S+|s|) 0 ms���ռ�O(|s|) 6.3 MB
// �������ҽ����ַ�����
// 1. ����ǰλ��Ϊ��λ����ô����һ������һ���÷����ű�ʾ���ַ��������������������k[...]:
// 1.1 �����Ƚ�����һ�����֣�Ȼ������������ţ��ݹ����½�����������ݣ�������Ӧ�������žͷ��أ���ʱ���Ը��ݽ�����������x����������������ַ���s'������µ��ַ���x��s'
// 1.2 ��k[...]�����������ٴε��õݹ麯���������������ұߵ�����
// 2 �����ǰλ������ĸλ����ô����ֱ�ӽ�����ǰ�����ĸ��Ȼ��ݹ����½��������ĸ��������ݡ�
class Solution {
private:
	string src;
	size_t ptr;
	int getDigits() {
		int ret = 0;
		while (ptr < src.size() && isdigit(src[ptr])) {
			ret = ret * 10 + src[ptr++] - '0';
		}
		return ret;
	}

	string getString() {
		if (ptr == src.size() || src[ptr] == ']') {
			// String  -> EPS
			return "";
		}

		char cur = src[ptr];
		int repTime = 1;
		string ret;

		if (isdigit(cur)) {
			// String -> Digits[String] String;
			// ����Digits
			repTime = getDigits();
			// ����������
			++ptr;
			// ����String
			string str = getString();
			// ����������
			++ptr;
			// �����ַ���
			while (repTime--) ret += str;
		}
		else if (isalpha(cur)) {
			// String -> Char String
			// ����Char
			ret = string(1, src[ptr++]);
		}
		return ret + getString();
	}
public:
	string decodeString(string s) {
		src = s;
		ptr = 0;
		return getString();
	}
};

int main() {

	string str = "3[z]2[2[y]pq4[2[jk]e1[f]]]ef";

	Solution s;
	string ret = s.decodeString(str);

	cout << ret << endl;

	system("pause");
	return 0;
}