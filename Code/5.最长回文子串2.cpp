#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;


// ��̬�滮
class Solution {
public:
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2) {
			return s;
		}
		int maxLen = 1;
		int begin = 0;
		// dp(i,j)��ʾ�ַ���s�ĵ�i��j����ĸ��ɵĴ�(���ı�ʾ��s[i:j])�Ƿ�Ϊ���Ĵ�����Ϊ1����Ϊ0
		vector<vector<int>> dp(n, vector<int>(n));
		// ���г���
		for (int i = 0; i < n; i++) {
			dp[i][i] = true;
		}
		// ö���Ӵ�����
		for (int L = 2; L <= n; L++) {
			// ö����߽磬��߽�����Ȳ�����L���ȵ�����
			for (int i = 0; i < n; i++) {
				int j = L + i - 1;
				// ���ұ߽�Խ�磬���˳���ǰѭ��
				if (j >= n) {
					break;
				}

				if (s[i] != s[j]) {
					dp[i][j] = false;
				}
				else {
					// ��L < 4 �� j - i < 3������s[i] == s[j]��ǰ���£�s[i:j]��Ϊ���Ĵ�
					if (L < 4) {
						dp[i][j] = true;
					}
					// ��L >= 4������Ҫ�����ڲ��Ƿ�Ϊ���Ĵ�
					else {
						dp[i][j] = dp[i + 1][j - 1];
					}
				}

				// ����������Ӵ����Ⱥͽ��
				if (dp[i][j] && L > maxLen) {
					maxLen = L;
					begin = i;
				}
			}
		}

		return s.substr(begin, maxLen);
	}
};

// ������չ�㷨
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
		// ok�Ĳ���s[left,right]����s[left+1, right-1]
		return right - left - 1;
	}
};

// Manacher�㷨
class Solution {
public:
	string longestPalindrome(string s) {
		int start = 0, maxLen = 1;
		string t = "#";
		// �����ַ���s�е�ÿ���ַ�c
		for (char& c : s) {
			t += c;
			t += '#';
		}
		t += '#';
		s = t;

		// ���Ĵ��ı۳�
		vector<int> armLen; 
		int right = -1, j = -1;
		int cur_arm_len;
		for (int i = 0; i < s.size(); ++i) {
			if (right >= i) {
				// i_sym��i��jΪ���ĵľ���λ
				int i_sym = j * 2 - i;
				// rightΪ��jΪ���ĵ�����Ĵ��۳����ܸ��ǵ�����ԶԪ�أ�right-i������iΪ������j�ı۳����Ƿ�Χ�ڵ����۳���
				int min_arm_len = min(armLen[i_sym], right - i);
				// ����i_sym�ı۳���¼armLen���Ѽ�¼����i_symΪ���ĵĻ��Ĵ��۳����ʼ����iΪ���ĵĻ��Ĵ��۳�ʱ��ֻ���i-min_arm_len��i+min_arm_len��ʼ������չ���������ڱ�Ϊ���������ַ������ʱ۳�Ϊ(����-1)/2
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
		// ok�Ĳ���s[left,right]����s[left+1, right-1]
		return right - left - 1;
	}
};

int main()
{
	Solution s;
	string ret = s.longestPalindrome("ababba");
	cout << "������Ӵ�Ϊ��" << ret << endl;
	system("pause");
	return 0;
}