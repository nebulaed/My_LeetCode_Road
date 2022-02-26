#include<iostream>
#include<vector>
#include<stack>
#include<string>
using namespace std;

// �ҵĽⷨ����׺���ʽ(�沨�����ʽ)��ʱ�� 4 ms 77.16%���ռ� 6.5 MB 81.47%
class Solution {
public:
    int calculate(string s) {
        string t;
        stack<int, vector<int>> stk;
        size_t length = s.size();
        for (size_t i = 0; i < length; ++i) {
            if (isdigit(s[i])) {
                t += s[i];
                if (i + 1 == length || !isdigit(s[i + 1])) t += ',';
            }
            else {
                if (s[i] == ' ') continue;
                if (s[i] == '(') {
                    stk.emplace(s[i]);
                }
                else if (s[i] == ')') {
                    while (stk.top() != '(') {
                        t += static_cast<char>(stk.top());
                        stk.pop();
                    }
                    stk.pop();
                }
                else {
                    while (!stk.empty() && ((stk.top() == '*' || stk.top() == '/') || ((stk.top() == '+' || stk.top() == '-') && (s[i] == '+' || s[i] == '-')))) {
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
                switch (t[i]) {
                case '+':
                    stk.emplace(lhs + rhs);
                    break;
                case '-':
                    stk.emplace(lhs - rhs);
                    break;
                case '*':
                    stk.emplace(lhs * rhs);
                    break;
                case '/':
                    stk.emplace(lhs / rhs);
                    break;
                }
                ++i;
            }
        }
        return stk.top();
    }
};