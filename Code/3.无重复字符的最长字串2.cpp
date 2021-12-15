#include<iostream>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
using namespace std;

// 必错方法，unordered_set 元素无序
// class Solution {
// public:
// 	int lengthOfLongestSubstring(string s) {
// 		if (s.size() == 0) {
// 			return 0;
// 		}
// 		else {
// 			unordered_set<char> set;
// 			unordered_set<char>::iterator pos;
// 			int maxSubStrSize = 1;
// 			for (int i = 0; i < s.size(); i++) {
// 				pos = set.find(s[i]);
// 				if (pos != set.end()) {
// 					set.erase(set.begin(), ++pos);
// 				}
// 				set.insert(s[i]);
// 				maxSubStrSize = set.size() > maxSubStrSize ? set.size() : maxSubStrSize;
// 			}
// 			return maxSubStrSize;
// 		}
// 	}
// };


class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0) {
			return 0;
		}
		else {
			unordered_map<char, int> set1;
			unordered_map<char, int>::iterator pos;
			int maxSubStrSize = 1;
			int left = 0;
			for (int i = 0; i < s.size(); i++) {
				pos = set1.find(s[i]);
				if (pos != set1.end()) {
					cout << "left: " << left << endl;
					cout << "pos->second: " << pos->second << endl;
					for (int j = left; j <= pos->second; j++) {
						unordered_map<char, int>::iterator pos2;
						pos2 = set1.find(s[j]);
						if (pos2 != set1.end()) {
							set1.erase(s[j]);
							left = j + 1;
						}
					}
				}
				set1.insert(make_pair(s[i],i));
				for (unordered_map<char, int>::iterator it = set1.begin(); it != set1.end(); it++) {
					cout << "(" << it->first << ", " << it->second << ")" << "  ";
				}
				cout << endl;
				maxSubStrSize = set1.size() > maxSubStrSize ? set1.size() : maxSubStrSize;
			}
			return maxSubStrSize;
		}
	}
};

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		unordered_set<char> set1;
		int n = s.size();
		int right = -1, ret = 0;
		for (int i = 0; i < n; ++i) {
			if (i != 0) {
				set1.erase(s[i - 1]);
			}
			while (right + 1 < n && !set1.count(s[right+1])){
				set1.insert(s[right+1]);
				++right;
			}
			ret = max(ret, right-i+1);
		}
		return ret;
	}
};

int main() {
	string input = "abcabcab";
	cout << input << endl;
	Solution s;
	int ret = s.lengthOfLongestSubstring(input);
	cout << "无重复字符的最长字串长度为：" << ret << endl;
	system("pause");
	return 0;
}