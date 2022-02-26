#include<iostream>
#include<array>
#include<string>
using namespace std;

// �ҵĽⷨ����ϣ��ʱ�� 0 ms 100%���ռ� 6.3 MB 96.42%
class Solution {
public:
    int longestPalindrome(string s) {
        array<int, 52> charFreq{};
        for (char ch : s) {
            if (ch >= 'a' && ch <= 'z') {
                ++charFreq[ch - 'a' + 26];
            }
            else {
                ++charFreq[ch - 'A'];
            }
        }
        int length = 0;
        for (int freq : charFreq) {
            if (freq & 1) {
                length += freq - 1 + !(length & 1);
            }
            else {
                length += freq;
            }
        }
        return length;
    }
};