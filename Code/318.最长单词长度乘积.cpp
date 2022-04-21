#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>

using namespace std;

// LeetCode 101解法：时间 28 ms 96.95%，空间 15.9 MB 52.19%
// 思路：用一个长度为26的二进制数字代表字符串中存在的字母，每个位置为1表示存在该字母，为0表示不存在，如果两字符串有相同字母，则它们的二进制数字按位与不为0.
class Solution {
public:
    int maxProduct(vector<string>& words) {
        // 哈希表表示从二进制表示数字到最长单词长度的映射
        unordered_map<int, int> hashMap;
        int ret = 0;
        for (const auto& word : words) {
            int mask = 0, length = word.size();
            // 若mask中有该字母，则将该字母对应位置置为1
            for (char ch : word) {
                mask |= 1 << (ch - 'a');
            }
            // 将二进制表示数字对应的单词长度取最大值
            hashMap[mask] = max(hashMap[mask], length);
            // 对于哈希表中所有的单词的代表二进制数字，检查当前单词与它们是否有重复字母，无则更新最大无相同字母字符串长度乘积
            for (const auto& [wordMask, wordLen] : hashMap) {
                if (!(mask & wordMask)) {
                    ret = max(ret, length * wordLen);
                }
            }
        }
        return ret;
    }
};

int main() {

    vector<string> input = { "abcw","baz","foo","bar","xtfn","abcdef" };

    Solution s;
    int ret = s.maxProduct(input);

    cout << ret << endl;

    return 0;
}