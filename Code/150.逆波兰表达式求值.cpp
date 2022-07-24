#include<vector>
#include<string>
#include<stack>
using namespace std;

// 我的解法：栈模拟，时间 O(n) 8 ms 82.32%，空间 O(n) 11.3 MB 99.85% (普通stack 11.6 MB 76.63%)
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int, vector<int>> stk;
        // stack<int> stk;
        for (const auto& token: tokens){
            if (isdigit(token[0]) || token.size() != 1) {
                stk.emplace(stoi(token));
            } else {
                int b = stk.top();
                stk.pop();
                int a = stk.top();
                stk.pop();
                switch (token[0]) {
                    case '+':
                        stk.emplace(a+b);
                        break;
                    case '-':
                        stk.emplace(a-b);
                        break;
                    case '*':
                        stk.emplace(a*b);
                        break;
                    case '/':
                        stk.emplace(a/b);
                        break;
                }
            }
        }
        return stk.top();
    }
};

// 官方解法二：数组模拟栈，时间 O(n) 4 ms 97.92%，空间 O(n) 11.4 MB 98.82%
class Solution {
public:
    int evalRPN(vector<string> &tokens) {
        const size_t n = tokens.size();
        vector<int> stk((n + 1) / 2);
        size_t pos = 0;
        for (const auto &token: tokens) {
            if (isdigit(token[0]) || token.size() != 1) {
                stk[pos++] = stoi(token);
            } else {
                int b = stk[--pos];
                switch (token[0]) {
                    case '+':
                        stk[pos - 1] += b;
                        break;
                    case '-':
                        stk[pos - 1] -= b;
                        break;
                    case '*':
                        stk[pos - 1] *= b;
                        break;
                    case '/':
                        stk[pos - 1] /= b;
                        break;
                }
            }
        }
        return stk[0];
    }
};