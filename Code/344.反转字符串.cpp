#include<vector>
using namespace std;

// 我的解法：双指针，时间 O(n) 16 ms 77.89%，空间 O(1) 22.5 MB 69.98%
class Solution {
public:
    void reverseString(vector<char>& s) {
        size_t len = s.size();
        for (size_t i = 0; i < len / 2; ++i) {
            swap(s[i], s[len - i - 1]);
        }
    }
};