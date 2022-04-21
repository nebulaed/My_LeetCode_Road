#include<iostream>
#include<array>
#include<array>

using namespace std;

// 我的解法：哈希表记录，时间 4 ms 92.73%，空间 6.8 MB 80.97%
class Solution {
public:
    bool isIsomorphic(string s, string t) {
        array<int, 256> s_first_index{}, t_first_index{};
        size_t length = s.size();
        for (size_t i = 0; i < length; ++i) {
            if (s_first_index[s[i]] != t_first_index[t[i]]) {
                return false;
            }
            s_first_index[s[i]] = t_first_index[t[i]] = i + 1;
        }
        return true;
    }
};