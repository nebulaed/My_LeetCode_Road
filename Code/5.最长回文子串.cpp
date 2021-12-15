#include<iostream>
#include<string>
using namespace std;

class Solution {
public:
	string longestPalindrome(string s) {
		string maxSubStr = s.substr(0,1);
		int maxSubStrSize = 1;
		bool flag;
		for (int i = 0; i < s.size(); i++) {
			for (int j = i + 1; j < s.size(); j++) {
				flag = true;
				int it1 = i;
				int it2 = j;
				for (; it1 < it2; it1++, it2--) {
					if (s[it1] != s[it2]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					if ((j + 1 - i) > maxSubStrSize) {
						maxSubStrSize = j + 1 - i;
						maxSubStr = s.substr(i, maxSubStrSize);
					}
				}
			}
		}
		return maxSubStr;
	}
};

int main()
{
	Solution s;
	string ret = s.longestPalindrome("cbbd");
	cout << "最长回文子串为：" << ret << endl;
	system("pause");
	return 0;
}