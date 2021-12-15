#include<iostream>
#include<string>
using namespace std;

// 我的解法
class Solution {
public:
	string countAndSay(int n) {
		int i = 1;
		string ret = "1";
		string temp = "";
		while (i < n) {
			int j = 0, left = 0;
			for (; j < ret.size() - 1; ++j) {
				if (ret[j] != ret[j + 1]) {
					temp += '0' + (j - left + 1);
					temp += ret[j];
					left = j + 1;
				}
			}
			temp += '0' + (j - left + 1);
			temp += ret[j];
			ret = temp;
			temp.clear();
			++i;
		}
		return ret;
	}
};

// 官方解法
class Solution {
public:
	string countAndSay(int n) {
		string prev = "1";
		for (int i = 2; i <= n; ++i) {
			string curr = "";
			int start = 0;
			int pos = 0;

			while (pos < prev.size()) {
				while (pos < prev.size() && prev[pos] == prev[start]) {
					++pos;
				}
				curr += pos - start + '0';
				curr += prev[start];
				start = pos;
			}
			prev = curr;
		}
		return prev;
	}
};

int main() {

	system("pause");
	return 0;
}