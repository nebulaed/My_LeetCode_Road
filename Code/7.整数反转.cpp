#include<iostream>
#include<string>
#include<algorithm>
using namespace std;

// 自己解法
//class Solution {
//public:
//	int reverse(int x) {
//		string temp = to_string(x);
//		// 必须加std避免错误调用当前函数
//		std::reverse(temp.begin(), temp.end());
//		int it = temp.find('-');
//		bool sgn = true;
//		if (it != -1) {
//			sgn = false;
//			temp.erase(it);
//		}
//		it = temp.find('0');
//		while (it == 0 && temp.size() > 1) {
//			temp.erase(it, 1);
//			it = temp.find('0');
//		}
//		try {
//			int ret = stoi(temp);
//			if (!sgn) ret = -ret;
//			return ret;
//		}
//		catch (out_of_range & exc) {
//			return 0;
//		}
//	}
//};

class Solution {
public:
	int reverse(int x) {
		int rev = 0;
		while (x != 0) {
			if (rev < INT_MIN / 10 || rev > INT_MAX / 10) {
				return 0;
			}
			int digit = x % 10;
			x /= 10;
			rev = rev * 10 + digit;
		}
		return rev;
	}
};



int main() {
	int input = 1234567899;
	Solution s;
	int ret = s.reverse(input);
	cout << ret << endl;

	system("pause");
	return 0;
}