#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Solution {
public:
	string intToRoman(int num) {
		string ret = "";
		int digits[4] = { 0,0,0,0 };
		const string roman = "IVXLCDM";

		digits[3] = num / 1000;
		digits[2] = (num % 1000) / 100;
		digits[1] = (num % 100) / 10;
		digits[0] = num % 10;

		for (int i = sizeof(digits)/sizeof(digits[0]) - 1; i >= 0; --i) {
			if (digits[i]) {
				if (digits[i] < 4) {
					ret += string(digits[i],roman[2 * i]);
				}
				else if (digits[i] == 4) {
					ret += roman[2 * i];
					ret += roman[2 * i + 1];
				}
				else if (digits[i] > 4 && digits[i] < 9) {
					ret += roman[2 * i + 1];
					ret += string(digits[i] - 5, roman[2 * i]);
				}
				else if (digits[i] == 9) {
					ret += roman[2 * i];
					ret += roman[2 * i + 2];
				}
			}
		}
		return ret;
	}
};

int main() {

	int num = 1994;

	Solution s;
	string ret = s.intToRoman(num);

	/*for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << " ";
	}
	cout << endl;*/
	cout << ret << endl;

	system("pause");
	return 0;
}