#include<vector>
#include<stack>
#include<string>
using namespace std;

// �ҵĽⷨ���沨�����ʽ��ʱ�� 12 ms 54%���ռ� 9 MB 38%
// �ؼ��㣺һԪ���ʽ��-���Ĵ���
class Solution {
public:
    int calculate(string s) {
        // ����׺���ʽת��Ϊ��׺���ʽ
        string t;
        stack<int, vector<int>> stk;
        size_t length = s.size();
        bool flag = true;
        for (size_t i = 0; i < length; ++i) {
            if (isdigit(s[i])) {
                t += s[i];
                if (i + 1 == length || !isdigit(s[i + 1])) t += ',';
                flag = true;
            }
            else {
                if (s[i] == ' ') continue;
                if (s[i] == '(') {
                    stk.emplace(s[i]);
                    flag = false;
                }
                else if (s[i] == ')') {
                    while (stk.top() != '(') {
                        t += static_cast<char>(stk.top());
                        stk.pop();
                    }
                    stk.pop();
                }
                else {
                    // �ؼ��㣺������Ϊ'-'��ǰ�����κ��������ֻ���ţ�����ǰ����'('ʱ���Ӹ�0
                    if (s[i] == '-' && (t.empty() || !flag)) {
                        t += "0,";
                    }
                    while (!stk.empty() && (stk.top() == '+' || stk.top() == '-')) {
                        t += static_cast<char>(stk.top());
                        stk.pop();
                    }
                    stk.emplace(s[i]);
                }
            }
        }
        while (!stk.empty()) {
            t += static_cast<char>(stk.top());
            stk.pop();
        }
        // �Ժ�׺���ʽͨ����ջ��ջ�������д����õ�������
        for (size_t i = 0; i < t.size();) {
            if (isdigit(t[i])) {
                int num = 0;
                while (isdigit(t[i])) {
                    num = 10 * num + (t[i++] - '0');
                }
                stk.emplace(num);
            }
            else {
                if (t[i] == ',') {
                    ++i;
                    continue;
                }
                int rhs = stk.top();
                stk.pop();
                int lhs = stk.top();
                stk.pop();
                if (t[i++] == '+') {
                    stk.emplace(lhs + rhs);
                }
                else {
                    stk.emplace(lhs - rhs);
                }
            }
        }
        return stk.top();
    }
};

// �ٷ��ⷨһ������չ�� + ջ��ʱ�� O(n) 4 ms 97.89%���ռ� O(n) 7.8 MB 88.34%
// ԭ����sign = {-1, +1}����ǰ�ķ��ţ��������ű��ʽ�����ʣ�����ȡֵ��
// 1. ���ַ����е�ǰλ�õ�������й�
// 2. ����ǰλ����һϵ�з����ڣ���Ҳ����Щ����ǰ����������أ�ÿ������һ����-�ſ�ͷ�����ţ�����ζ�Ŵ˺�ķ��Ŷ�Ҫ����ת
class Solution {
public:
    int calculate(string s) {
        stack<int, vector<int>> stk;
        stk.emplace(1);
        int sign = 1, ret = 0, n = s.size(), i = 0;
        while (i < n) {
            if (s[i] == ' ') ++i;
            else if (s[i] == '+') {
                sign = stk.top();
                ++i;
            }
            else if (s[i] == '-') {
                sign = -stk.top();
                ++i;
            }
            else if (s[i] == '(') {
                stk.emplace(sign);
                ++i;
            }
            else if (s[i] == ')') {
                stk.pop();
                ++i;
            }
            else {
                int num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};

// �ҵĵڶ��νⷨ������չ��+ջ��û��Ҫ��vector<bool>��ʱ�� 8 ms 80.30%���ռ� 7.8 MB 87.75%
class Solution {
public:
    int calculate(string s) {
        vector<bool> stk;
        stk.emplace_back(1);
        int sign = 1, ret = 0, n = s.size(), i = 0;
        while (i < n) {
            if (s[i] == ' ') ++i;
            else if (s[i] == '+') {
                sign = stk.back() ? 1 : -1;
                ++i;
            }
            else if (s[i] == '-') {
                sign = -(stk.back() ? 1 : -1);
                ++i;
            }
            else if (s[i] == '(') {
                stk.emplace_back(sign == -1 ? 0 : 1);
                ++i;
            }
            else if (s[i] == ')') {
                stk.pop_back();
                ++i;
            }
            else {
                int num = 0;
                while (i < n && isdigit(s[i])) {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
                ret += sign * num;
            }
        }
        return ret;
    }
};