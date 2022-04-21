#include<iostream>
#include<string>
#include<vector>
using namespace std;

// 我的解法=官方解法1：做加法 12 ms，9.4 MB
//class Solution {
//public:
//	string multiply(string num1, string num2) {
//		string ret = "0";
//		if (num1 == "0" || num2 == "0") return ret;
//		int carry = 0;
//		for (int j = num2.size() - 1; j >= 0; --j) {
//			string temp = "";
//			int this2 = num2[j] - '0';
//			if (this2) {
//				for (int i = num1.size() - 1; i >= 0 || carry; --i) {
//					int this1 = i >= 0 ? num1[i] - '0' : 0;
//					int this_num = (this1 * this2 + carry) % 10;
//					temp += this_num + '0';
//					carry = (this1 * this2 + carry) / 10;
//				}
//				reverse(temp.begin(), temp.end());
//				for (int k = 0; k < num2.size() - 1 - j; ++k) {
//					temp += '0';
//				}
//				ret = addStrings(ret, temp);
//			}
//		}
//		return ret;
//	}
//
//	string addStrings(const string& num1, const string& num2) {
//		string ret = "";
//		int digit = 1;
//		int n1 = num1.size(), n2 = num2.size(), carry = 0;
//		while (n1 - digit >= 0 || n2 - digit >= 0 || carry) {
//			int this1 = n1 - digit >= 0 ? num1[n1 - digit] - '0' : 0;
//			int this2 = n2 - digit >= 0 ? num2[n2 - digit] - '0' : 0;
//			int this_num = this1 + this2 + carry;
//			ret += this_num > 9 ? this_num - 10 + '0' : this_num + '0';
//			carry = this_num > 9 ? 1 : 0;
//			++digit;
//		}
//		reverse(ret.begin(), ret.end());
//		return ret;
//	}
//};

// 官方解法2：做乘法 4 ms，6.6 MB
class Solution {
public:
    string multiply(string num1, string num2) {
        if (num1 == "0" || num2 == "0") return "0";
        int n1 = num1.size(), n2 = num2.size();
        vector<int> ansArr(n1 + n2);
        for (int i = n1 - 1; i >= 0; --i) {
            int x = num1[i] - '0';
            for (int j = n2 - 1; j >= 0; --j) {
                int y = num2[j] - '0';
                ansArr[i + j + 1] += x * y;
            }
        }
        for (int i = n1 + n2 - 1; i > 0; --i) {
            ansArr[i - 1] += ansArr[i] / 10;
            ansArr[i] %= 10;
        }
        int index = ansArr[0] == 0 ? 1 : 0;
        string ans;
        while (index < n1 + n2) {
            ans += ansArr[index] + '0';
            ++index;
        }
        return ans;
    }
};


int main() {

    string num1 = "256";
    string num2 = "999";

    Solution s;
    string ret = s.multiply(num1, num2);

    cout << ret << endl;

    return 0;
}