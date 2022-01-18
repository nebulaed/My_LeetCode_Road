#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size();
		int n = p.size();

		auto matches = [&](int i, int j) {
			if (i == 0) {
				return false;
			}
			if (p[j - 1] == '.') {
				return true;
			}
			return s[i - 1] == p[j - 1];
		};
	
		vector<vector<int>> f(m + 1, vector<int>(n + 1));
		f[0][0] = true;
		for (int i = 0; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					f[i][j] |= f[i][j - 2];
					if (matches(i, j - 1)) {
						f[i][j] |= f[i - 1][j];
					}
				}
				else {
					if (matches(i, j)) {
						f[i][j] |= f[i - 1][j - 1];
					}
				}
			}
		}
		return f[m][n];
	}
};

class Solution {
public:
	bool isMatch(string s, string p) {
		if (s == p) return true;
		int i = 0, j = 0;
		while (i < s.size() && j < s.size()) {
			if (p[j] >= 'a' && p[j] <= 'z') {
				if (s[i] != p[j]) {
					break;
				}
				++i;
				++j;
			}
			else if (p[j] == '.') {
				++i;
				++j;
			}
			else (p[j] == '*') {
				if (p[j - 1] == '.') {
					if (j == p.size()) {
						i = s.size()
					}
					++j;
				}
			}
		}
	}
};

// LeetCode 101�ⷨ����̬�滮��ʱ�� 4 ms 87.12%���ռ� 6.6 MB 76.37%
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size(), n = p.size();
		// dp[i][j]��ʾ��i��ֹ���ַ����Ƿ���Ա���j��ֹ��������ʽƥ��
		vector<vector<bool>> dp(m + 1, vector<bool>(n + 1, false));
		dp[0][0] = true;
		for (int i = 1; i <= n; ++i) {
			// ��p�ĵ�i���ַ�Ϊ*��ֻҪ��0��ֹ���ַ���s�ܱ���i-2��ֹ��������ʽpƥ�䣬��ôsҲ�ܱ���i��ֹ��pƥ��
			if (p[i - 1] == '*') {
				dp[0][i] = dp[0][i - 2];
			}
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				// ��p�ĵ�j���ַ�Ϊ.��ֻҪ��i-1��ֹ���ַ���s�ܱ���j-1��ֹ��������ʽpƥ�䣬��ôsҲ�ܱ���i��ֹ��pƥ��
				if (p[j - 1] == '.') {
					dp[i][j] = dp[i - 1][j - 1];
				}
				// ��p�ĵ�j���ַ���Ϊ*Ҳ��Ϊ.����ôֻ�е���i-1��ֹ���ַ���s�ܱ���j-1��ֹ��������ʽpƥ�䣬��s�ĵ�i���ַ���p�ĵ�j���ַ�һ�£�����ƥ��
				else if (p[j - 1] != '*') {
					dp[i][j] = dp[i - 1][j - 1] & (p[j - 1] == s[i - 1]);
				}
				// ��p�ĵ�j���ַ�Ϊ*����p�ĵ�j-1���ַ���s�ĵ�i���ַ���һ�£���p�ĵ�j-1���ַ�����.����ôs��p�Ƿ�ƥ��ȡ������i��ֹ��s����j-2��ֹ��p�Ƿ�ƥ�䣬Ҳ����p�ĵ�j-1��j�ַ���?*ƥ�������Ԫ��
				else if ((p[j - 2] != s[i - 1]) & (p[j - 2] != '.')) {
					dp[i][j] = dp[i][j - 2];
				}
				// ��p�ĵ�j���ַ�Ϊ*����p�ĵ�j-1���ַ���s�ĵ�i���ַ�ƥ��(��������ƥ�����.ƥ��)����ôֻҪ��i��β��s����j-1��β��pƥ�����i-1��β��s������j��β��pƥ�����i��β��s������j-2��β��pƥ�䣬��ôs��pƥ�䡣
				// ��һ�ֺ���⣬�������ba��ba*�Ƚϣ����s[i]=ba��p[j-1]=ba��ƥ���ϣ���ôs��p��ƥ����
				// �ڶ��ֱ�ʾ�����aab��c*a*b*�Ƚϣ�s[i]=aa��p[j-1]=c*aƥ�䲻�ˣ����s[i-1]=a��p[j]=c*a*ƥ�䣬��ôs=aa��p=c*a*��ƥ��
				// �����ֱ�ʾ�����ab��abd*�Ƚϣ�s[i]=ab��p[j-2]=ab��ƥ�䣬��s=ab��p=abd*Ҳ��ƥ��
				else {
					dp[i][j] = dp[i][j - 1] | dp[i - 1][j] | dp[i][j - 2];
				}
			}
		}
		return dp[m][n];
	}
};

int main() {

	string s = "mississippi";
	string p = "mis*is*p*.";

	Solution sol;
	bool ret = sol.isMatch(s, p);
	if (ret) cout << "true" << endl;
	else cout << "false" << endl;

	system("pause");
	return 0;
}