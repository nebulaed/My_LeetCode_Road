#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

// 我的解法：
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