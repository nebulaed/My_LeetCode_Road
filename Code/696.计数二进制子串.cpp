#include<iostream>
#include<string>

using namespace std;

// �ҵĽⷨ��������չ����ʱ�� 12 ms 99.31%���ռ� 10.2 MB 89.36%
class Solution {
public:
    int countBinarySubstrings(string s) {
        int count = 0;
        size_t length = s.size();
        // ����Ҫ�����0������1������ȣ���0��1�������������ַ���
        // ��01��10Ϊ���Ľ���������չ���ж��Ըô�01��10Ϊ���ĵķ���Ҫ����ַ���������
        for (size_t lCenter = 0; lCenter < length - 1; ++lCenter) {
            size_t rCenter = lCenter + 1;
            if (s[lCenter] == '0') {
                if (s[rCenter] == '1') {
                    ++count;
                    size_t left = lCenter, right = rCenter;
                    while (--left != -1 && ++right < length && s[left] == '0' && s[right] == '1') {
                        ++count;
                    }
                }
            }
            else {
                if (s[rCenter] == '0') {
                    ++count;
                    size_t left = lCenter, right = rCenter;
                    while (--left != -1 && ++right < length && s[left] == '1' && s[right] == '0') {
                        ++count;
                    }
                }
            }
        }
        return count;
    }
};

// LeetCode 101�ⷨ��ʱ�� 16 ms 91.08%���ռ� 10.3 MB 46.34%
// �������ұ������飬��¼�͵�ǰλ��������ͬ�������ĳ��ȣ��Լ���֮ǰ�����Ĳ�ͬ���ֵĳ��ȡ�������˵������00110 �����һλ�����Ǽ�¼����ͬ���ֳ�����1����Ϊֻ��һ������0�����Ǽ�¼�Ĳ�ͬ���ֳ�����2����Ϊ��0 ֮ǰ������������1������ͬ���ֵ��������ȴ��ڵ��ڵ�ǰ���ֵ��������ȣ���˵������һ����ֻ����һ���Ե�ǰ���ֽ�β���������������ַ�����
class Solution {
public:
    int countBinarySubstrings(string s) {
        int pre = 0, cur = 1, count = 0;
        for (size_t i = 1; i < s.size(); ++i) {
            // ����ǰ�ַ���ǰһ�ַ���Ϊ0��1����ô��ǰ�����ַ�����+1
            if (s[i] == s[i - 1]) {
                ++cur;
            }
            // ���򽫵�ǰ�����ַ����������෴�����ַ���������ǰ�����ַ�������1
            else {
                pre = cur;
                cur = 1;
            }
            // ����ͬ�����ַ��������ڵ��ڵ�ǰ�����ַ��������������������ַ�������+1
            if (pre >= cur) {
                ++count;
            }
        }
        return count;
    }
};