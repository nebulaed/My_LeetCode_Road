#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

// �ҵĽⷨ��
class Solution {
public:
	string minWindow(string s, string t) {
		int freq[52] = { 0 };
		for (int i = 0; i < t.size(); ++i) {
			modifyfreq(freq, t[i], true);
		}
		int freq2[52] = { 0 };
		string minWindow;
		int l = 0, r = 0, minLength = INT_MAX;
		for (int r = 0; r < s.size(); ++r) {
			modifyfreq(freq2, s[r], true);
			if (matchfreq(freq, freq2)) {
				while (l <= r) {
					modifyfreq(freq2, s[l], false);
					++l;
					if (!matchfreq(freq, freq2)) {
						if (r - l + 2 < minLength) {
							minWindow = s.substr(l - 1, r - l + 2);
							minLength = r - l + 2;
						}
						break;
					}
				}
			}
		}
		return minWindow;
	}

	bool matchfreq(int freq[], int freq2[]) {
		for (int i = 0; i < 52; ++i) {
			if (freq2[i] < freq[i]) {
				return false;
			}
		}
		return true;
	}

	void modifyfreq(int freq[], char c, bool sgn) {
		if (sgn) {
			if (c - 'A' >= 0 && c - 'A' < 26) {
				++freq[c - 'A'];
			}
			else {
				++freq[c - 'a' + 26];
			}
		}
		else {
			if (c - 'A' >= 0 && c - 'A' < 26) {
				--freq[c - 'A'];
			}
			else {
				--freq[c - 'a' + 26];
			}
		}
	}
};


// LeetCode 101�ⷨ��ʱ�� 4 ms���ռ� 7.5 MB
class Solution {
private:
	int ch2ind(char ch) {
		return ch >= 'a' ? ch - 'a' + 26 : ch - 'A';
	}
public:
	string minWindow(string s, string t) {
		int chars[52]{};
		bool flag[52]{ false };
		// ��ͳ��T�е��ַ����
		for (char ch : t) {
			int ind = ch2ind(ch);
			flag[ind] = true;
			++chars[ind];
		}
		// �ƶ��������ڣ����ϵظ���ͳ������
		int cnt = 0, left = 0, minLeft = 0, minSize = s.size() + 1;
		for (int right = 0; right < s.size(); ++right) {
			int indRight = ch2ind(s[right]);
			if (flag[indRight]) {
				if (--chars[indRight] >= 0) {
					++cnt;
				}
				// ��Ŀǰ���������Ѿ�����T��ȫ���ַ���
				// ���Խ�left���ƣ��ڲ�Ӱ����������»��������ַ���
				while (cnt == t.size()) {
					if (right - left + 1 < minSize) {
						minLeft = left;
						minSize = right - left + 1;
					}
					int indLeft = ch2ind(s[left]);
					if (flag[indLeft] && ++chars[indLeft] > 0) {
						--cnt;
					}
					++left;
				}
			}
		}
		return minSize > s.size() ? "" : s.substr(minLeft, minSize);
	}
};