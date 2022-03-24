#include<vector>
using namespace std;

// 我的解法：反向迭代器，时间 O(n) 0 ms 100%，空间 O(1) 8.5 MB 66.52%
class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        bool carry = true;
        for (auto rit = digits.rbegin(); rit != digits.rend(); ++rit) {
            ++(*rit);
            if (*rit < 10) {
                carry = false;
                break;
            }
            else {
                *rit = 0;
            }
        }
        if (carry) digits.insert(digits.begin(), 1);
        return digits;
    }
};