#include<iostream>
#include<array>
#include<string>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0) {
			return 0;
		}
		else {
			int maxSubStrSize = 1;
			int thisimax = 1;
			for (int i = 0; i < s.size(); i++) {
				int temp = thisimax;
				thisimax = 1;
				// ���ϸ��ַ���Ϊ��ʼλ��ʱ���������ظ��ַ�����ִ�����Ϊtemp����ô�ӵ�ǰ�ַ�����temp-1���ַ��ڱض�û���ظ��ַ�
				for (int j = i + temp - 1; j < s.size(); j++) {
					for (int it = i; it < j; it++) {
						if (s[it] == s[j]) {
							maxSubStrSize = (j - i) > maxSubStrSize ? (j - i) : maxSubStrSize;
							thisimax = (j - i) > thisimax ? (j - i) : thisimax;
							goto label;
						}
					}
					maxSubStrSize = (j + 1 - i) > maxSubStrSize ? (j + 1 - i) : maxSubStrSize;
					thisimax = (j + 1 - i) > thisimax ? (j + 1 - i) : thisimax;
				}
			label:;
			}
			return maxSubStrSize;
		}

	}
};

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		if (s.size() == 0) {
			return 0;
		}
		else {
			int maxSubStrSize = 1;
			// ��¼�ҽ�
			int right = 1;
			for (int i = 0; i < s.size(); i++) {
				// ���ϸ��ַ���Ϊ��ʼλ��ʱ���������ظ��ַ�����Ӵ��յ�Ϊright-1����ô�ӵ�ǰ�ַ���right-1���ַ��ض�û���ظ��ַ�
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


// �ش�����unordered_set Ԫ������
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
				set1.insert(make_pair(s[i], i));
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

// �ҵĵڶ��νⷨ���������ڷ���ʱ�� 4 ms 97.26%���ռ� 6.7 MB 92.45%
class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		array<int, 128> charFreq{};
		int left = 0, right = 0, maxLen = 0, length = s.size();
		while (right < length) {
			while (right < length && charFreq[s[right]] == 0) {
				++charFreq[s[right++]];
			}
			maxLen = max(maxLen, right - left);
			if (right < length) {
				++charFreq[s[right]];
			}
			else break;
			++right;
			while (charFreq[s[left]] != 2) {
				--charFreq[s[left++]];
			}
			--charFreq[s[left++]];
		}
		return maxLen;
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
			while (right + 1 < n && !set1.count(s[right + 1])) {
				set1.insert(s[right + 1]);
				++right;
			}
			ret = max(ret, right - i + 1);
		}
		return ret;
	}
};

int main()
{
	//string input = "abcabcbb";
	string input = "pwwkew";
	cout << input << endl;
	Solution s;
	int ret = s.lengthOfLongestSubstring(input);
	cout << "���ظ��ַ�����ִ�����Ϊ��" << ret << endl;
	system("pause");
	return 0;
}