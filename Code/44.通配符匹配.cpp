#include<iostream>
#include<string>
#include<vector>
using namespace std;

// �Լ��ⷨ�� 64 ms��27.3 MB
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size();
		int n = p.size();

		auto matches = [&](int i, int j) {
			if (i == 0) {
				return false;
			}
			if (p[j - 1] == '?') {
				return true;
			}
			return s[i - 1] == p[j - 1];
		};

		vector<vector<int>> f(m + 1, vector<int>(n + 1));
		f[0][0] = true;
		// �ο���ָ�㲿��
		for (int i = 1; i <= n; ++i) {
			if (p[i - 1] == '*') {
				f[0][i] = true;
			}
			else {
				break;
			}
		}
		//
		for (int i = 0; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					if (i > 0) {
						f[i][j] |= f[i - 1][j];
						if (j > 1) {
							// �ο���ָ�㲿��
							// if(matches(i, j-1)){
							f[i][j] |= f[i][j - 1];
							// }
						}
						else f[i][j] = true;
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

// �ٷ��ⷨ1����̬�滮 O(mn) 64 ms��O(mn) 27.1 MB
class Solution {
public:
	bool isMatch(string s, string p) {
		int m = s.size();
		int n = p.size();
		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		dp[0][0] = true;
		for (int i = 1; i <= n; ++i) {
			if (p[i - 1] == '*') {
				dp[0][i] = true;
			}
			else {
				break;
			}
		}
		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (p[j - 1] == '*') {
					dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
				}
				else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
					dp[i][j] = dp[i - 1][j - 1];
				}
			}
		}
		return dp[m][n];
	}
};

// �ٷ��ⷨ2��̰���㷨 ����ʱ�临�Ӷ�O(mn)��ƽ��ʱ�临�Ӷ�O(mlog n) 8 ms��6.4 MB
class Solution {
public:
	bool isMatch(string s, string p) {
		// ���str��[left,right)���Ƿ�Ϊ*
		auto allStars = [](const string& str, int left, int right) {
			for (int i = left; i < right; ++i) {
				if (str[i] != '*') {
					return false;
				}
			}
			return true;
		};
		// ���u��v�Ƿ�ƥ��
		auto charMatch = [](char u, char v) {
			return u == v || v == '?';
		};

		// ��s��p�ĳ��Ȳ�Ϊ0����p�����һ���ַ���Ϊ*���ж�s��p�Ľ�β�ַ��Ƿ�ƥ�䣬����s��p�Ľ�βһͬ���ַ�ɾȥ������ƥ��ʧ��
		while (s.size() && p.size() && p.back() != '*') {
			if (charMatch(s.back(), p.back())) {
				s.pop_back();
				p.pop_back();
			}
			else {
				return false;
			}
		}
		// ��pΪ�գ���sΪ��ʱƥ��ɹ�������ƥ��ʧ��
		if (p.empty()) {
			return s.empty();
		}

		// index��0��ʼ��sRecord��-1��ʼ����p��һ���ַ���*��sRecord��pRecord�Ŵ�pIndex��ʼ������Ҫ��һƥ���ַ�ֱ��p�ĵ�һ��*
		int sIndex = 0, pIndex = 0;
		int sRecord = -1, pRecord = -1;
		while (sIndex < s.size() && pIndex < p.size()) {
			if (p[pIndex] == '*') {
				++pIndex;
				sRecord = sIndex;
				pRecord = pIndex;
			}
			else if (charMatch(s[sIndex], p[pIndex])) {
				++sIndex;
				++pIndex;
			}
			else if (sRecord != -1 && sRecord + 1 < s.size()) {
				++sRecord;
				sIndex = sRecord;
				pIndex = pRecord;
			}
			else {
				return false;
			}
		}
		return allStars(p, pIndex, p.size());
	}
};

int main() {
	string s = "aa";
	string p = "*";

	Solution sol;
	bool ret = sol.isMatch(s, p);

	cout << ret << endl;
	system("pause");
	return 0;
}