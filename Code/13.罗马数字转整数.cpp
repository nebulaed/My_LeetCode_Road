#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;

// 我的解法
class Solution {
public:
    int romanToInt(string s) {
        int ret = 0;
        const string roman[] = {"CM","M","CD","D","XC","C","XL","L","IX","X","IV","V","I"};
        const int num[] = { 900,1000,400,500,90,100,40,50,9,10,4,5,1 };

        for (int i = 0; i < sizeof(roman) / sizeof(roman[0]); ++i) {
            for (int pos = s.find(roman[i]); pos != -1; pos = s.find(roman[i])) {
                ret += num[i];
                s.erase(pos, roman[i].size());
            }
        }

        return ret;
    }
};

// 官方解法
class Solution {
private:
    unordered_map<char, int> symbolValues = {
            {'I', 1},
            {'V', 5},
            {'X', 10},
            {'L', 50},
            {'C', 100},
            {'D', 500},
            {'M', 1000},
    };
public:
    int romanToInt(string s) {
        int ret = 0;
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            int value = symbolValues[s[i]];
            if (i < n - 1 && value < symbolValues[s[i + 1]]) {
                ret -= value;
            }
            else {
                ret += value;
            }
        }
        return ret;
    }
};

int main() {

    string roman_num = "MCMXCIV";

    Solution s;
    int ret = s.romanToInt(roman_num);

    cout << ret << endl;

    return 0;
}