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
//				// ���ϸ��ַ���Ϊ��ʼλ��ʱ���������ظ��ַ�����ִ�����Ϊtemp����ô�ӵ�ǰ�ַ�����temp-1���ַ��ڱض�û���ظ��ַ�
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