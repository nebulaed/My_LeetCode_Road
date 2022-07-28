#include<iostream>
#include<cmath>
#include<vector>
#include<string>
using namespace std;

class Solution {
private:
    int getFirstDigit(int num) {
        if (num >= 100000000) num /= 100000000;
        if (num >= 10000) num /= 10000;
        if (num >= 100) num /= 100;
        if (num >= 10) num /= 10;
        return num;
    }

    int getNumOfDigit(int num) {
        int n = 0;
        while(num) {
            num /= 10;
            ++n;
        }
        return n;
    }
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [this](int lhs, int rhs){
            while(true) {
                int lhsFirst = getFirstDigit(lhs), rhsFirst = getFirstDigit(rhs);
                if (lhsFirst > rhsFirst) {
                    return true;
                } else if (lhsFirst < rhsFirst) {
                    return false;
                } else {
                    int lhsDigit = getNumOfDigit(lhs), rhsDigit = getNumOfDigit(rhs);
                    lhs -= lhsFirst * pow(10, lhsDigit);
                    rhs -= rhsFirst * pow(10, rhsDigit);
                    int newlhsDigit = getNumOfDigit(lhs), newrhsDigit = getNumOfDigit(rhs);
                    if (lhsDigit - newlhsDigit > rhsDigit - newrhsDigit) return false;
                    if (lhsDigit - newlhsDigit < rhsDigit - newrhsDigit) return true;
                    // if (lhs == 0) lhs = 9;
                    // if (rhs == 0) rhs = 9;
                    // if (lhs == 0 && rhs == 0) 
                }
            }
        });
        string ret;
        for_each(nums.begin(), nums.end(), [&ret](int num) {
            ret += to_string(num);
        });
        return ret;
    }
};

// 官方思路：时间 O(n log n log m) 8 ms 57.78%，空间 O(log n) 10.8 MB 60.34%，m是32位整数最大值
class Solution {
public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [](int lhs, int rhs){
            string strLhs = to_string(lhs), strRhs = to_string(rhs);
            if (strLhs + strRhs > strRhs + strLhs) {
                return true;
            }
            return false;
        });
        if (nums[0] == 0) return "0";
        string ret;
        for_each(nums.begin(), nums.end(), [&ret](int num) {
            ret += to_string(num);
        });
        return ret;
    }
};

// 我的解法：不转字符串比较，自己实现10的幂，时间 O(n log n) 4 ms 90.08%，空间 O(log n) 10.7 MB 77.77%
class Solution {
private:
    int getNumOfDigit(int num) {
        int n = 0;
        while(num) {
            num /= 10;
            ++n;
        }
        return n;
    }
    unsigned int pow10(int p)
    {
        if (p == 0) return 1;
        if (p == 1) return 10;

        int tmp = pow10(p / 2);
        if (p % 2 == 0) return tmp * tmp;
        else return 10 * tmp * tmp;
    }

public:
    string largestNumber(vector<int>& nums) {
        sort(nums.begin(), nums.end(), [this](int lhs, int rhs){
            if (lhs == 0) return false;
            if (rhs == 0) return true;
            int lhsDigit = getNumOfDigit(lhs), rhsDigit = getNumOfDigit(rhs);
            if (pow10(rhsDigit) * lhs + rhs > pow10(lhsDigit) * rhs + lhs) {
                return true;
            }
            return false;
        });
        if (nums[0] == 0) return "0";
        string ret;
        for_each(nums.begin(), nums.end(), [&ret](int num) {
            ret += to_string(num);
        });
        return ret;
    }
};


int main() {
    vector<int> nums{3,30,34,5,9};

    Solution sol;
    cout << sol.largestNumber(nums) << endl;

    return 0;
}