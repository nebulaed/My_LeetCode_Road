#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ��������չ�㷨��ʱ�� O(n^2) 4 ms 82.96%���ռ� O(1) 6.1 MB 78.53%
class Solution {
private:
    int expandAroundCenter(const string& s, size_t left, size_t right) {
        int count = 0;
        while (left != -1 && right < s.size() && s[left] == s[right]) {
            ++count;
            --left;
            ++right;
        }
        return count;
    }
public:
    int countSubstrings(string s) {
        int count = 0;
        for (size_t i = 0; i < s.size(); ++i) {
            count += expandAroundCenter(s, i, i);
            count += expandAroundCenter(s, i, i + 1);
        }
        return count;
    }
};

// �ٷ���⣺Manacher�㷨��ʱ��O(n) 0 ms 100%���ռ� 6.6 MB 60.12%
class Solution {
public:
    int countSubstrings(string s) {
        // ����'$'��'!'��Ϊ��ѭ��ʱ����Խ��
        string t = "$#";
        for (char ch : s) {
            t += ch;
            t += '#';
        }
        t += '!';
        int n = t.size(), iMax = 0, rMax = 0, ans = 0;
        vector<int> armLen(n);
        for (int i = 1; i < n; ++i) {
            int& curArmLen = armLen[i];
            // ��i�������ڵ�ǰ�������Ӵ��ڣ�����iΪ���ĵ����۳�Ϊ[rMax - i + 1(�������Ӵ��ұ߽絽i)��i������������Ӵ���ĶԳƵ�����۳�]����ȡ��Сֵ
            // ����۳�Ϊ1
            curArmLen = (i <= rMax) ? min(rMax - i + 1, armLen[2 * iMax - i]) : 1;
            // ������չ
            while (t[i + curArmLen] == t[i - curArmLen]) {
                ++curArmLen;
            }
            // ��̬ά��iMax��rMax
            if (i + curArmLen - 1 > rMax) {
                iMax = i;
                rMax = i + curArmLen - 1;
            }
            // ans += (armLen[i] - 1) / 2����ȡ��
            // �������ַ���Ϊ$#a#b#c#!������ǰ�ַ�Ϊaʱ�����۳�ΪcurArmLen = 2����ôʵ���������ַ�������ΪmaxLen = curArmLen - 1 = 1�������ַ�������Ϊ(maxLen + 1) / 2
            // ��ˣ������ַ�������ΪcurArmLen / 2
            ans += curArmLen / 2;
        }
        return ans;
    }
};