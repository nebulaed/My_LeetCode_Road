#include<iostream>
#include<vector>
#include<string>
using namespace std;

// 我的解法：KMP算法(参考大话数据结构)，时间 0 ms 100%，空间 7.4 MB 16.98%
class Solution {
public:
    int strStr(string haystack, string needle) {
        int i = 0, j = 0, n1 = haystack.size(), n2 = needle.size();
        if (!n2) return 0;
        // next[i]表示对于匹配串needle，needle[0]~needle[i]这一个子串，前k+1个字符与后k+1个字符相等的最大的k，k!=i
        // 例如abcabd，对于next[4], 子串为abcab，前2个字符与后两个字符相等，因此k=1
        vector<int> next(n2);
        get_nextval(needle, next);
        while (i < n1 && j < n2) {
            if (j == -1 || haystack[i] == needle[j]) {
                ++i;
                ++j;
            }
                // 有部分匹配，往前回溯
            else {
                j = next[j];
            }
        }
        return j > n2 - 1 ? (i - n2) : -1;
    }

    // 辅函数，计算next数组
    void get_nextval(const string& needle, vector<int>& next) {
        int i = 0, k = -1;
        next[0] = -1;
        while (i < needle.size() - 1) {
            if (k == -1 || needle[i] == needle[k]) {
                ++i;
                ++k;
                if (needle[i] != needle[k]) next[i] = k;
                    // 若该位相同，更新相同的最大前缀
                else next[i] = next[k];
            }
                // 若该位不同，往前回溯
            else {
                k = next[k];
            }
        }
    }
};