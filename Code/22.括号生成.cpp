#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct BiTNode
{
	BiTNode *lchild, *rchild;
};

// �ҵĽⷨ(������)
//class Solution {
//public:
//	vector<string> generateParenthesis(int n) {
//		vector<string> ret;
//		BiTNode* T = nullptr;
//		CreateBiTree(T, n, n, true, "", ret);
//		return ret;
//	}
//
//	void CreateBiTree(BiTNode* T, int n1, int n2, bool flag, string s, vector<string>& ret) {
//		if (!n1 && !n2) {
//			T = nullptr;
//		}
//		else {
//			if (flag && n1 > 0) {
//				T = new BiTNode;
//				s += '(';
//				--n1;
//			}
//			else if (flag && !n1) {
//				T = nullptr;
//				return;
//			}
//			else if (!flag && n2 > 0 && n2 > n1) {
//				T = new BiTNode;
//				s += ')';
//				--n2;
//			}
//			else if (!flag && (!n2 || n2 <= n1)) {
//				T = nullptr;
//				return;
//			}
//			if (!n1 && !n2) ret.push_back(s);
//			CreateBiTree(T->lchild, n1, n2, true, s, ret);
//			CreateBiTree(T->rchild, n1, n2, false, s, ret);
//		}
//	}
//};

// �ٷ��ⷨ1��������
// ˼·������2^(2n)�������ź��������ַ����ɵ����У�Ȼ����ÿһ���Ƿ���Ч��
//class Solution {
//private:
//	bool valid(const string& str) {
//		int balance = 0;
//		for (char c : str) {
//			if (c == '(') {
//				++balance;
//			}
//			else {
//				--balance;
//			}
//			if (balance < 0) {
//				return false;
//			}
//		}
//		return balance == 0;
//	}
//
//	void generate_all(string& current, int n, vector<string>& ret) {
//		if (n == current.size()) {
//			if (valid(current)) {
//				ret.push_back(current);
//			}
//			return;
//		}
//		current += '(';
//		generate_all(current, n, ret);
//		current.pop_back();
//		current += ')';
//		generate_all(current, n, ret);
//		current.pop_back();
//	}
//public:
//	vector<string> generateParenthesis(int n) {
//		vector<string> ret;
//		string current;
//		generate_all(current, n * 2, ret);
//		return ret;
//	}
//};

// �ٷ��ⷨ2�����ݷ�
// �ڷ���1�Ļ����ϣ�ֻ��������Чʱ�������'('��')'��ͨ������ĿǰΪֹ���õ������ź������ŵ���Ŀ��ʵ��
class Solution {
	void backtrack(vector<string>& ret, string& cur, int open, int close, int n) {
		if (cur.size() == n * 2) {
			ret.push_back(cur);
			return;
		}
		if (open < n) {
			cur.push_back('(');
			backtrack(ret, cur, open + 1, close, n);
			cur.pop_back();
		}
		if (close < open) {
			cur.push_back(')');
			backtrack(ret, cur, open, close + 1, n);
			cur.pop_back();
		}
	}

public:
	vector<string> generateParenthesis(int n) {
		vector<string> result;
		string current;
		backtrack(result, current, 0, 0, n);
		return result;
	}
};

int main() {
	int n = 3;

	Solution s;
	vector<string> ret = s.generateParenthesis(n);

	cout << "[";
	for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}

