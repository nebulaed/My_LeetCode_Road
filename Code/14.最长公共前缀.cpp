#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ
//class Solution {
//public:
//	string longestCommonPrefix(vector<string>& strs) {
//		string ret = "";
//		bool flag = true;
//
//		for (int i = 0; i < strs[0].size(); ++i) {
//			for (int j = 0; j < strs.size(); ++j) {
//				if (i >= strs[j].size() || strs[j][i] != strs[0][i]) {
//					flag = false;
//					break;
//				}
//			}
//			if (flag) ret += strs[0][i];
//			else break;
//		}
//		return ret;
//	}
//};


// ��������LCP(S1...Sn)��ʾ�ַ���S1...Sn�������ǰ׺

// �ٷ��ⷨ1������ɨ��
// LCP(S1...Sn)=LCP(LCP(LCP(S1,S2),S3),...Sn)

//class Solution {
//public:
//	string longestCommonPrefix(vector<string>& strs) {
//		if (!strs.size()) {
//			return "";
//		}
//		string prefix = strs[0];
//		int count = strs.size();
//		for (int i = 1; i < count; ++i) {
//			prefix = longestCommonPrefix(prefix, strs[i]);
//			if (!prefix.size()) {
//				break;
//			}
//		}
//		return prefix;
//	}
//
//	string longestCommonPrefix(const string& str1, const string& str2) {
//		int length = min(str1.size(), str2.size());
//		int index = 0;
//		while (index < length && str1[index] == str2[index]) {
//			++index;
//		}
//		return str1.substr(0, index);
//	}
//};

// �ٷ��ⷨ2������ɨ��
//class Solution {
//public:
//	string longestCommonPrefix(vector<string>& strs) {
//		if (!strs.size()) {
//			return "";
//		}
//		int length = strs[0].size();
//		int count = strs.size();
//		for (int i = 0; i < length; ++i) {
//			char c = strs[0][i];
//			for (int j = 1; j < count; ++j) {
//				if (i == strs[j].size() || strs[j][i] != c) {
//					return strs[0].substr(0, i);
//				}
//			}
//		}
//		return strs[0];
//	}
//};

// �ٷ��ⷨ3������
// LCP(S1...Sn)=LCP(LCP(S1...Sk),LCP(Sk+1...Sn))
// ����LCP(S1...Sn)���ַ���S1...Sn�������ǰ׺��1<k<n
// ���η��õ��ַ��������е������ǰ׺��������LCP(S1...Sj)�ɷֽ�ΪLCP(Si...Smid)��LCP(Smid+1...Sj)������mid=(i+j)/2��������������ֱ���⣬Ȼ�������������Ľ���������ǰ׺����Ϊԭ�����

//class Solution {
//public:
//	string longestCommonPrefix(vector<string>& strs) {
//		if (!strs.size()) {
//			return "";
//		}
//		else {
//			return longestCommonPrefix(strs, 0, strs.size() - 1);
//		}
//	}
//
//	string longestCommonPrefix(const vector<string>& strs, int start, int end) {
//		if (start == end) {
//			cout << start << endl;
//			return strs[start];
//		}
//		else {
//			int mid = (start + end) / 2;
//			string lcpLeft = longestCommonPrefix(strs, start, mid);
//			string lcpRight = longestCommonPrefix(strs, mid + 1, end);
//			return commonPrefix(lcpLeft, lcpRight);
//		}
//	}
//
//	string commonPrefix(const string& lcpLeft, const string& lcpRight) {
//		int minLength = min(lcpLeft.size(), lcpRight.size());
//		for (int i = 0; i < minLength; ++i) {
//			if (lcpLeft[i] != lcpRight[i]) {
//				return lcpLeft.substr(0, i);
//			}
//		}
//		return lcpLeft.substr(0, minLength);
//	}
//};

// �ٷ��ⷨ4�����ֲ���
class MyCompare {
public:
	bool operator()(const string& s, const string& t) {
		return s.size() < t.size();
	}
};

class Solution {
public:
	string longestCommonPrefix(vector<string>& strs) {
		if (!strs.size()) {
			return "";
		}
		int minLength = min_element(strs.begin(), strs.end(), MyCompare())->size();
		int low = 0, high = minLength;
		while (low < high) {
			int mid = (high - low + 1) / 2 + low;
			if (isCommonPrefix(strs, mid)) {
				low = mid;
			}
			else {
				high = mid - 1;
			}
		}
		return strs[0].substr(0, low);
	}

	bool isCommonPrefix(const vector<string>& strs, int length) {
		string str0 = strs[0].substr(0, length);
		int count = strs.size();
		for (int i = 1; i < count; ++i) {
			for (int j = 0; j < length; ++j) {
				if (str0[j] != strs[i][j]) {
					return false;
				}
			}
		}
		return true;
	}
};



int main() {
	vector<string> strs = { "flower","flow","flight" };

	Solution s;
	
	string ret = s.longestCommonPrefix(strs);

	cout << ret << endl;

	system("pause");
	return 0;
}