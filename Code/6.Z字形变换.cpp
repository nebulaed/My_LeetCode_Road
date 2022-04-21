#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows == 1) {
            return s;
        }
        vector<string> temp(numRows, "");
        int row;
        for (int i = 0; i < s.size(); ++i) {
            row = i % (numRows + numRows - 2);
            cout << "row0 = " << row << endl;
            if (row >= numRows) {
                row = 2 * numRows - row - 2;
            }
            cout << "row = " << row << endl << "i = " << i << endl;
            temp[row] += s[i];
        }
        string ret;
        for (int i = 0; i < numRows; ++i) {
            ret += temp[i];
        }
        return ret;
    }
};

int main() {
    string input = "PAYPALISHIRING";
    int numRows = 4;
    Solution s;
    string ret = s.convert(input, 4);
    cout << ret << endl;

    return 0;
}