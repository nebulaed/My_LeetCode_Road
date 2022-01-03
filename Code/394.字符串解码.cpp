#include<iostream>
#include<string>
#include<stack>
#include<vector>
using namespace std;

// 我的解法一：栈，时间O(S+|s|) 0 ms，空间O(S) 6.1 MB
class Solution {
public:
	string decodeString(string s) {
		// ret用来存放最终结果，cur用来存放当前[]内字符串，curNum用来存放当前数字
		string ret, cur, curNum;
		// stkFreq用来存放[]前数字，表示[]内字符串重复次数
		stack<int> stkFreq;
		// stkStr用来存放[]内字符串
		stack<string> stkStr;
		for (size_t i = 0; i < s.size();) {
			curNum.clear();
			while (isdigit(s[i])) {
				curNum += s[i];
				// 若下一个字符不是数字，则可将curNum内存放的字符串转为数字，放进stkFreq内
				if (!isdigit(s[i + 1])) {
					stkFreq.emplace(stoi(curNum));
					curNum.clear();
				}
				++i;
			}
			// 若当前字符为[，往stkStr中放入空字符串
			if (s[i] == '[') {
				stkStr.emplace("");
				++i;
			}
			cur.clear();
			// 若s[i]是小写字母，放入当前[]内字符串cur中
			while (s[i] >= 'a' && s[i] <= 'z') {
				cur += s[i];
				++i;
			}
			// 若s[i]不是]且i小于s长度，不是小写字母，也就意味着是数字
			if (s[i] != ']' && i < s.size()) {
				// 若stkStr为空，将cur放入stkStr内
				if (stkStr.empty()) stkStr.emplace(cur);
				// 否则stkStr的栈顶接上cur
				else stkStr.top() += cur;
				continue;
			}
			// 若stkFreq不为空且s[i]是]
			while (!stkFreq.empty() && s[i] == ']') {
				// stkStr的栈顶接上cur
				stkStr.top() += cur;
				cur.clear();
				// cur = stkFreq.top()个stkStr.top()重复
				string temp = stkStr.top();
				for (int i = 0; i < stkFreq.top(); ++i) {
					cur += temp;
				}
				stkFreq.pop();
				stkStr.pop();
				++i;
				// 若stkStr不为空
				if (!stkStr.empty()) {
					cur = stkStr.top() + cur;
					stkStr.pop();
					// 若当前字符为]，则为stkStr补充一个空字符串，避免stkStr和stkFreq长度不等
					if (s[i] == ']') stkStr.emplace("");
				}
			}
			if (stkFreq.empty()) ret += cur;
			// 若stkFreq不为空，说明还有[没匹配上]，因此将cur放入stkStr中
			else stkStr.emplace(cur);
		}
		return ret;
	}
};


// 官方解法一：栈操作，时间O(S+|s|) 0 ms, 空间O(S) 6.5 MB
// 遍历输入字符串：
// 1.若当前字符为数位，解析出一个数字(连续的多个数位)并进栈
// 2.若当前的字符为字母或左括号，进栈
// 3.若当前字符为右括号，开始出栈，一直到左括号出栈，出栈序列反转后拼接成一个字符串，此时取栈顶的数字，就是这个字符串应该出现的次数。
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
				// 获取一个数字并进栈
				string digits = getDigits(s, ptr);
				stk.emplace_back(digits);
			}
			else if (isalpha(cur) || cur == '[') {
				// 获取一个字母并进栈
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
				// 左括号出栈
				stk.pop_back();
				// 此时栈顶为当前sub对应的字符串应该出现的次数
				int repTime = stoi(stk.back());
				stk.pop_back();
				// t为空，o为[]内字符串
				string t, o = getString(sub);
				// t=repTime*o
				while (repTime--) t += o;
				stk.emplace_back(t);
			}
		}
		return getString(stk);
	}
};

// 官方解法二：递归，时间O(S+|s|) 0 ms，空间O(|s|) 6.3 MB
// 从左向右解析字符串：
// 1. 若当前位置为数位，那么后面一定包含一个用方括号表示的字符串，即属于这种情况：k[...]:
// 1.1 可以先解析出一个数字，然后解析到左括号，递归向下解析后面的内容，遇到对应的右括号就返回，此时可以根据解析出的数字x解析出的括号里的字符串s'构造出新的字符串x×s'
// 1.2 把k[...]解析结束后，再次调用递归函数，解析右括号右边的内容
// 2 如果当前位置是字母位，那么我们直接解析当前这个字母，然后递归向下解析这个字母后面的内容。
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
			// 解析Digits
			repTime = getDigits();
			// 过滤左括号
			++ptr;
			// 解析String
			string str = getString();
			// 过滤右括号
			++ptr;
			// 构造字符串
			while (repTime--) ret += str;
		}
		else if (isalpha(cur)) {
			// String -> Char String
			// 解析Char
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