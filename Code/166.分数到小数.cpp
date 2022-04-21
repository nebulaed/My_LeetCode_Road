#include<string>
#include<unordered_map>
using namespace std;

// 官方解法一：长除法，时间 0 ms 100%，空间 6.2 MB 74.89%
class Solution {
public:
    string fractionToDecimal(int numerator, int denominator) {
        long long numeratorLong = numerator, denominatorLong = denominator;
        if (numeratorLong % denominatorLong == 0) {
            return to_string(numeratorLong / denominatorLong);
        }
        string ret;
        // 若分子和分母中一个小于0一个不小于0
        if (numeratorLong < 0 ^ denominatorLong < 0) {
            ret += '-';
        }
        // 计算整数部分
        numeratorLong = abs(numeratorLong), denominatorLong = abs(denominatorLong);
        int intPart = numeratorLong / denominatorLong;
        ret += to_string(intPart) + '.';

        // 计算小数部分
        string fractionPart;
        unordered_map<int, int> remainderMap;
        long long remainder = numeratorLong % denominatorLong, index = 0;
        while (remainder != 0 && !remainderMap.count(remainder)) {
            remainderMap.emplace(remainder, index++);
            remainder *= 10;
            fractionPart += to_string(remainder / denominatorLong);
            remainder %= denominatorLong;
        }
        if (remainder != 0) {
            int start = remainderMap[remainder];
            fractionPart.insert(start, "(");
            fractionPart += ')';
        }
        ret += fractionPart;
        return ret;
    }
};