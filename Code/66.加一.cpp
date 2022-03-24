#include<vector>
using namespace std;

// �ҵĽⷨ�������������ʱ�� O(n) 0 ms 100%���ռ� O(1) 8.5 MB 66.52%
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