#include<iostream>
#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

// �ٷ��ⷨһ������+��֦��ʱ��O(n��2^n) 4 ms���ռ�O(n^2) 7.5 MB
class Solution {
private:
	vector<string> ret;

	void dfs(string str, int start, int leftRemove, int rightRemove) {
		if (leftRemove == 0 && rightRemove == 0) {
			if (isValid(str)) {
				ret.emplace_back(str);
			}
			return;
		}
		for (int i = start; i < str.size(); ++i) {
			// ����������ͬ�ַ���ֻ������һ�μ���
			if (i != start && str[i] == str[i - 1]) {
				continue;
			}
			// ��ʣ���ַ��޷�����ɾ��������Ҫ��ֱ�ӷ���
			if (leftRemove + rightRemove > str.size() - i) {
				return;
			}
			// ����ȥ��һ��������
			if (leftRemove > 0 && str[i] == '(') {
				dfs(str.substr(0, i) + str.substr(i + 1), i, leftRemove - 1, rightRemove);
			}
			// ����ȥ��һ��������
			if (rightRemove > 0 && str[i] == ')') {
				dfs(str.substr(0, i) + str.substr(i + 1), i, leftRemove, rightRemove - 1);
			}
		}
	}

	inline bool isValid(const string& str) {
		int cnt = 0;

		for (char c : str) {
			if (c == '(') {
				++cnt;
			}
			else if (c == ')') {
				--cnt;
				if (cnt < 0) {
					return false;
				}
			}
		}
		return cnt == 0;
	}
public:
	vector<string> removeInvalidParentheses(string s) {
		int leftRemove = 0;
		int rightRemove = 0;

		// �������֪Ӧ��ɾ���������š�����������
		for (char c : s) {
			if (c == '(') {
				++leftRemove;
			}
			else if (c == ')') {
				if (leftRemove == 0) {
					++rightRemove;
				}
				else {
					--leftRemove;
				}
			}
		}
		dfs(s, 0, leftRemove, rightRemove);
		return ret;
	}
};

// �ٷ��ⷨ����BFS��ʱ��O(n��2^n) 64 ms���ռ�O(n��C^(n/2)_n) 24.3 MB
// ˼·������BFSʱÿ��ɾ���ַ����е�1�����ţ�ֱ�����ֺϷ�ƥ����ַ���Ϊֹ����ʱ������ת�Ĵ�����Ϊ������Ҫɾ�����ŵĸ���
// ����BFSʱ��ÿ�α�����һ�������Ľ����Ȼ�����һ���Ѿ�����Ľ����ÿһ���ַ����������п��ܵ�ɾ��һ�����ŵķ���
// Ȼ�󽫱���Ľ��������һ��������������ʱ�������ù�ϣ��ȥ��
class Solution {
private:
	inline bool isValid(const string& str) {
		int cnt = 0;

		for (char c : str) {
			if (c == '(') {
				++cnt;
			}
			else if (c == ')') {
				--cnt;
				if (cnt < 0) {
					return false;
				}
			}
		}
		return cnt == 0;
	}
public:
	vector<string> removeInvalidParentheses(string s) {
		vector<string> ret;
		unordered_set<string> currSet;

		currSet.emplace(s);
		while (true) {
			// ������currSet�е�str�Ƿ�Ϸ����Ϸ��Ļ�����ret
			for (const auto& str : currSet) {
				if (isValid(str)) {
					ret.emplace_back(str);
				}
			}
			// ���currSet��һ���Ϸ��ַ�����ζ�����кϷ��ַ����ѽ���currSet
			if (ret.size() > 0) return ret;
			// ��һ�ֵ��ַ�������
			unordered_set<string> nextSet;
			// ������currSet�е�str
			for (const auto& str : currSet) {
				// ��str�ĵ�0λ��ʼ���������ÿһ���ַ�
				for (size_t i = 0; i < str.size(); ++i) {
					// ������������ͬ�ַ���ֻ����һ��(����һ��)
					if (i > 0 && str[i] == str[i - 1]) {
						continue;
					}
					// ����ɾ����ǰ��iλ��'('��')'
					if (str[i] == '(' || str[i] == ')') {
						nextSet.emplace(str.substr(0, i) + str.substr(i + 1, str.size()));
					}
				}
			}
			// nextSet��ֵ����ǰ����currSet
			currSet = nextSet;
		}
	}
};