#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class Solution {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> ret;
		// �ж�wordsΪ�գ���Ϊ�����õ���words[0]
		if (words.empty()) {
			return ret;
		}

		int word_size = words[0].size();
		int word_num = words.size();

		unordered_map<string, int> m1; // ����hashmap
		for (int i = 0; i < word_num; ++i) {
			++m1[words[i]];
		}

		unordered_map<string, int> m2;
		// ��ȡ��s��������
		for (int i = 0, j = i; (i + word_size * word_num) <= s.size();) {
			// �ֶ��ж�
			while (j < (i + word_size * word_num)) {
				string temp_str = s.substr(j, word_size);
				j += word_size;
				// ��m1��û�н�ȡ�Ĵ���˵����ƥ��
				if (m1[temp_str] == 0) {
					i = j;
					m2.clear();
					break;
				}
				else {
					++m2[temp_str];
					// �ظ���������m1�г��ִ���������
					if (m1[temp_str] < m2[temp_str]) {
						while (m1[temp_str] < m2[temp_str]) {
							--m2[s.substr(i, word_size)];
							i += word_size;
						}
						break;
					}
				}
			}

			// ÿһ�ζ����ϣ�������
			if (j == (i + word_size * word_num)) {
				ret.push_back(i);
				--m2[s.substr(i, word_size)];
				i += word_size;
			}
		}
		return ret;
	}
};

int main() {
	string s = "barfoothefoobarman";
	vector<string> words = { "foo","bar" };

	Solution sol;
	vector<int> ret = sol.findSubstring(s,words);

	cout << "[";
	for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << ",";
	}
	cout << "]";

	system("pause");
	return 0;
}