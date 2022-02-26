#include<iostream>
#include<string>
using namespace std;

// �ҵĽⷨ��KMP�㷨(�ο������ݽṹ)��ʱ�� 0 ms 100%���ռ� 7.4 MB 16.98%
class Solution {
public:
    int strStr(string haystack, string needle) {
        int i = 0, j = 0, n1 = haystack.size(), n2 = needle.size();
        if (!n2) return 0;
        // next[i]��ʾ����ƥ�䴮needle��needle[0]~needle[i]��һ���Ӵ���ǰk+1���ַ����k+1���ַ���ȵ�����k��k!=i
        // ����abcabd������next[4], �Ӵ�Ϊabcab��ǰ2���ַ���������ַ���ȣ����k=1
        vector<int> next(n2);
        get_nextval(needle, next);
        while (i < n1 && j < n2) {
            if (j == -1 || haystack[i] == needle[j]) {
                ++i;
                ++j;
            }
            // �в���ƥ�䣬��ǰ����
            else {
                j = next[j];
            }
        }
        return j > n2 - 1 ? (i - n2) : -1;
    }

    // ������������next����
    void get_nextval(const string& needle, vector<int>& next) {
        int i = 0, k = -1;
        next[0] = -1;
        while (i < needle.size() - 1) {
            if (k == -1 || needle[i] == needle[k]) {
                ++i;
                ++k;
                if (needle[i] != needle[k]) next[i] = k;
                // ����λ��ͬ��������ͬ�����ǰ׺
                else next[i] = next[k];
            }
            // ����λ��ͬ����ǰ����
            else {
                k = next[k];
            }
        }
    }
};