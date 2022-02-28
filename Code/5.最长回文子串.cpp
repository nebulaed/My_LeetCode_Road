#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
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

// 动态规划
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2) {
			return s;
		}
		int maxLen = 1;
		int begin = 0;
		// dp(i,j)表示字符串s的第i到j个字母组成的串(下文表示成s[i:j])是否为回文串，是为1，否为0
		vector<vector<int>> dp(n, vector<int>(n));
		// 所有长度
		for (int i = 0; i < n; i++) {
			dp[i][i] = true;
		}
		// 枚举子串长度
		for (int L = 2; L <= n; L++) {
			// 枚举左边界，左边界可以先不考虑L长度的限制
			for (int i = 0; i < n; i++) {
				int j = L + i - 1;
				// 若右边界越界，就退出当前循环
				if (j >= n) {
					break;
				}

				if (s[i] != s[j]) {
					dp[i][j] = false;
				}
				else {
					// 若L < 4 或 j - i < 3，则在s[i] == s[j]的前提下，s[i:j]必为回文串
					if (L < 4) {
						dp[i][j] = true;
					}
					// 若L >= 4，则还需要考虑内部是否为回文串
					else {
						dp[i][j] = dp[i + 1][j - 1];
					}
				}

				// 更新最长回文子串长度和结果
				if (dp[i][j] && L > maxLen) {
					maxLen = L;
					begin = i;
				}
			}
		}

		return s.substr(begin, maxLen);
	}
};

// 中心扩展算法
class Solution {
public:
	string longestPalindrome(string s) {
		if (s.size() == 0) {
			return "";
		}
		int start = 0;
		int maxLen = 1;
		for (int i = 0; i < s.size(); ++i) {
			int len1 = expandAroundCenter(s, i, i);
			int len2 = expandAroundCenter(s, i, i + 1);
			int len = max(len1, len2);
			if (len > maxLen) {
				start = i - (len - 1) / 2;
				maxLen = len;
			}
		}
		return s.substr(start, maxLen);
	}

	int expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		// ok的不是s[left,right]而是s[left+1, right-1]
		return right - left - 1;
	}
};

// Manacher算法
class Solution {
public:
	string longestPalindrome(string s) {
		int start = 0, maxLen = 1;
		string t = "#";
		// 遍历字符串s中的每个字符c
		for (char& c : s) {
			t += c;
			t += '#';
		}
		t += '#';
		s = t;

		// 回文串的臂长
		vector<int> armLen;
		int right = -1, j = -1;
		int cur_arm_len;
		for (int i = 0; i < s.size(); ++i) {
			if (right >= i) {
				// i_sym是i以j为中心的镜像位
				int i_sym = j * 2 - i;
				// right为以j为中心的最长回文串臂长所能覆盖到的最远元素，right-i就是以i为中心在j的臂长覆盖范围内的最大臂长。
				int min_arm_len = min(armLen[i_sym], right - i);
				// 由于i_sym的臂长记录armLen中已记录下以i_sym为中心的回文串臂长，故检查以i为中心的回文串臂长时，只需从i-min_arm_len到i+min_arm_len开始往外拓展，由于现在必为长度奇数字符串，故臂长为(长度-1)/2
				cur_arm_len = (expandAroundCenter(s, i - min_arm_len, i + min_arm_len) - 1) / 2;
			}
			else {
				cur_arm_len = (expandAroundCenter(s, i, i) - 1) / 2;
			}
			armLen.push_back(cur_arm_len);
			if (i + cur_arm_len > right) {
				j = i;
				right = i + cur_arm_len;
			}
			if (cur_arm_len * 2 + 1 > maxLen) {
				start = i - cur_arm_len;
				maxLen = 2 * cur_arm_len;
			}
		}

		string ret;
		for (int i = start; i <= start + maxLen; ++i) {
			if (s[i] != '#') {
				ret += s[i];
			}
		}
		return ret;
	}

	int expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		// ok的不是s[left,right]而是s[left+1, right-1]
		return right - left - 1;
	}
};

// 我的第二次解法：中心扩展，时间 12 ms 94.97%，空间 7.1 MB 78.71%
class Solution {
private:
	int expandAroundCenter(const string& s, int left, int right) {
		while (left >= 0 && right < s.size() && s[left] == s[right]) {
			--left;
			++right;
		}
		return right - left - 1;
	}
public:
	string longestPalindrome(string s) {
		int start = 0, maxLen = 1, n = s.size();
		for (int i = 0; i < n - 1; ++i) {
			int singularLen = expandAroundCenter(s, i, i);
			int evenLen = expandAroundCenter(s, i, i + 1);
			if (singularLen > evenLen) {
				if (singularLen > maxLen) {
					maxLen = singularLen;
					start = i - (maxLen >> 1);
				}
			}
			else {
				if (evenLen > maxLen) {
					maxLen = evenLen;
					start = i - (maxLen >> 1) + 1;
				}
			}
		}
		return s.substr(start, maxLen);
	}
};

int main()
{
	Solution s;
	string ret = s.longestPalindrome("cbbd");
	//string ret = s.longestPalindrome("ababba");
	cout << "最长回文子串为：" << ret << endl;
	system("pause");
	return 0;
}