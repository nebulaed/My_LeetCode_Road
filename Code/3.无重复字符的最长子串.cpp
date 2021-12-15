#include<iostream>
#include<string>
using namespace std;

//class Solution {
//public:
//	int lengthOfLongestSubstring(string s) {
//		if (s.size() == 0) {
//			return 0;
//		}
//		else {
//			int maxSubStrSize = 1;
//			int thisimax = 1;
//			for (int i = 0; i < s.size(); i++) {
//				int temp = thisimax;
//				thisimax = 1;
//				// 若上个字符作为起始位置时，不包含重复字符的最长字串长度为temp，那么从当前字符计起，temp-1个字符内必定没有重复字符
//				for (int j = i + temp - 1; j < s.size(); j++) {
//					for (int it = i; it < j; it++) {
//						if (s[it] == s[j]) {
//							maxSubStrSize = (j - i) > maxSubStrSize ? (j - i) : maxSubStrSize;
//							thisimax = (j - i) > thisimax ? (j - i) : thisimax;
//							goto label;
//						}
//					}
//					maxSubStrSize = (j + 1 - i) > maxSubStrSize ? (j + 1 - i) : maxSubStrSize;
//					thisimax = (j + 1 - i) > thisimax ? (j + 1 - i) : thisimax;
//				}
//			label:;
//			}
//			return maxSubStrSize;
//		}
//
//	}
//};

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0) {
			return 0;
		}
		else {
			int maxSubStrSize = 1;
			// 记录右界
			int right = 1;
			for (int i = 0; i < s.size(); i++) {
				// 若上个字符作为起始位置时，不包含重复字符的最长子串终点为right-1，那么从当前字符到right-1个字符必定没有重复字符
				for (int j = right; j < s.size(); j++) {
					for (int it = i; it < j; it++) {
						if (s[it] == s[j]) {
							maxSubStrSize = (j - i) > maxSubStrSize ? (j - i) : maxSubStrSize;
							right = j;
							goto label;
						}
					}
					maxSubStrSize = (j + 1 - i) > maxSubStrSize ? (j + 1 - i) : maxSubStrSize;
					right = j;
				}
			label:;
			}
			return maxSubStrSize;
		}
	}
};

int main()
{
	//string input = "abcabcbb";
	string input = "pwwkew";
	cout << input << endl;
	Solution s;
	int ret = s.lengthOfLongestSubstring(input);
	cout << "无重复字符的最长字串长度为：" << ret << endl;
	system("pause");
	return 0;
}