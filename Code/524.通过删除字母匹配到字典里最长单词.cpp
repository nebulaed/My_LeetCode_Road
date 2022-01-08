#include<iostream>
#include<string>
#include<vector>
#include<array>
#include<algorithm>
using namespace std;

// �ҵĽⷨ����ָ�룬���α�����ʱ��O(d(m+n)) 64 ms���ռ�O(d) 14.6 MB
class Solution {
public:
	string findLongestWord(string s, vector<string>& dictionary) {
		size_t length = dictionary.size();
		vector<size_t> ptrDir(length, 0);
		for (char ch : s) {
			for (size_t i = 0; i < length; ++i) {
				size_t temp = ptrDir[i];
				const string& tempStr = dictionary[i];
				if (temp < tempStr.size() && tempStr[temp] == ch) {
					++ptrDir[i];
				}
			}
		}
		string ret;
		for (size_t i = 0; i < length; ++i) {
			const string& currWord = dictionary[i];
			size_t currPtr = ptrDir[i];
			size_t retLength = ret.size();
			if (currPtr == currWord.size()) {
				if (currPtr > retLength || (currPtr == retLength && currWord < ret)) {
					ret = currWord;
				}
			}
		}
		return ret;
	}
};

// �ٷ��ⷨһ��˫ָ�룬һ�α�����ʱ��O(d��(m+n)) 52 ms���ռ�O(1) 14.7 MB
class Solution {
public:
	string findLongestWord(string s, vector<string>& dictionary) {
		string ret;
		for (const auto& word : dictionary) {
			size_t ptrS = 0, ptrW = 0, wordSize = word.size();
			while (ptrS < s.size() && ptrW < wordSize) {
				if (word[ptrW] == s[ptrS]) {
					++ptrW;
				}
				++ptrS;
			}
			if (ptrW == wordSize) {
				if (wordSize > ret.size() || (wordSize == ret.size() && word < ret)) {
					ret = word;
				}
			}
		}
		return ret;
	}
};

// �ٷ��ⷨ��������ʱ��O(d*m*log d + d*(m+n)) 48 ms���ռ�O(d*m) 14.6 MB
// �ȶ�dictionary��Ԥ���������ַ������ȵĽ�����ֵ���������������Ȼ���ǰ����ҵ���һ�������������ַ���ֱ�ӷ��ؼ��ɡ�
class Solution {
public:
	string findLongestWord(string s, vector<string>& dictionary) {
		sort(dictionary.begin(), dictionary.end(), [](const string& lhs, const string& rhs) {
			return lhs.size() > rhs.size() || (lhs.size() == rhs.size() && lhs < rhs);
			});
		for (const string& word : dictionary) {
			size_t ptrW = 0, ptrS = 0, wordSize = word.size();
			while (ptrW < wordSize && ptrS < s.size()) {
				if (word[ptrW] == s[ptrS]) {
					++ptrW;
				}
				++ptrS;
			}
			if (ptrW == wordSize) {
				return word;
			}
		}
		return "";
	}
};

// �ٷ��ⷨ������̬�滮��ʱ��O(m*|��|+d*n) 44 ms���ռ�O(m*|��|) 15.4 MB
// ���ǿ���ͨ��Ԥ�����õ�����s��ÿһ��λ�ã��Ӹ�λ�ÿ�ʼ����ÿһ���ַ���һ�γ��ֵ�λ��
// ����ʹ�ö�̬�滮�ķ���ʵ��Ԥ������f[i][j]��ʾ�ַ���s�д�λ��i��ʼ�����ַ�j
class Solution {
public:
	string findLongestWord(string s, vector<string>& dictionary) {
		size_t m = s.size();
		vector<array<int, 26>> dp(m + 1, array<int, 26>{});
		// Ϊ���һ��ȫ�������m���Ա�ֱ��ǲ���s���ǲ���û��ĳһ�ַ�
		fill(dp[m].begin(), dp[m].end(), m);

		// ��s�����һ���ַ���ʼ����ͳ��
		for (int i = m - 1; i >= 0; --i) {
			for (int j = 0; j < 26; ++j) {
				// ��s[i]�ǵ�jλ������ַ������¼�µ�jλ�ַ����ֵĵ�ǰλ��i
				if (s[i] == 'a' + j) {
					dp[i][j] = i;
				}
				// �����jλ���ֵ�λ�ú�s�ĺ�һλ����ͬ
				else {
					dp[i][j] = dp[i + 1][j];
				}
			}
		}
		string ret;
		for (const string& word : dictionary) {
			bool match = true;
			int j = 0;
			for (int i = 0; i < word.size(); ++i) {
				// ����word[i]������s�е�λ��
				int pos = dp[j][word[i] - 'a'];
				// ������m˵��s��û��word[i]
				if (pos == m) {
					match = false;
					break;
				}
				// �����s[j]��ʼ����word����һλ�ַ�
				j = pos + 1;
			}
			if (match) {
				if (word.size() > ret.size() || (word.size() == ret.size() && word < ret)) {
					ret = word;
				}
			}
		}
		return ret;
	}
};