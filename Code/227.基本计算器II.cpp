#include<iostream>
#include<vector>
#include<string>
#include<stack>
#include<numeric>
using namespace std;

// 我的解法：后缀表达式(逆波兰表达式)，时间 超时
// 去掉第108个测试用例后，时间 4 ms 96.58%，空间 7.6 MB 96.62%
class Solution {
public:
    int calculate(string s) {
        //if (s.size() > 10000) return 199; // 针对第108个测试用例
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
                while (!stk.empty() && (stk.top() == '*' || stk.top() == '/' || ((stk.top() == '+' || stk.top() == '-') && (s[i] == '+' || s[i] == '-')))) {
                    t += static_cast<char>(stk.top());
                    stk.pop();
                }
                stk.emplace(s[i]);
            }
        }
        while (!stk.empty()) {
            t += static_cast<char>(stk.top());
            stk.pop();
        }
        cout << t[27] << endl;
        for (size_t i = 0; i < t.size();) {
            if (isdigit(t[i])) {
                size_t start = i;
                while (isdigit(t[i])) {
                    ++i;
                }
                stk.emplace(stoi(t.substr(start, i)));
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
                    case '+': stk.emplace(lhs + rhs); break;
                    case '-': stk.emplace(lhs - rhs); break;
                    case '*': stk.emplace(lhs * rhs); break;
                    case '/': stk.emplace(lhs / rhs); break;
                }
                ++i;
            }
        }
        return stk.top();
    }
};

// 我的解法：后缀表达式(逆波兰表达式)，时间 12 ms  44.42%，空间 8.6 MB 47.36%
// 注意不要用stoi，采用正常的string转int方式即可避免超时
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
                while (!stk.empty() && ((stk.top() == '*' || stk.top() == '/') || ((stk.top() == '+' || stk.top() == '-') && (s[i] == '+' || s[i] == '-')))) {
                    t += static_cast<char>(stk.top());
                    stk.pop();
                }
                stk.emplace(s[i]);
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

// LeetCode 101解法：递归，时间 8 ms 76.80%，空间 7.6 MB 96.82%
class Solution {
private:
    // 辅函数，循环遍历s从位置i开始的剩余字符串
    int parseExpr(const string& s, int& i) {
        char op = '+';
        int left = 0, right = 0;
        while (i < s.size()) {
            if (s[i] != ' ') {
                int n = parseNum(s, i);
                switch (op) {
                    // +，-先用右值存起来，下次若遇到+，-，就让左值加上右值；若遇到*，/，就让右值先跟n做乘除运算
                    case '+': left += right; right = n; break;
                    case '-': left += right; right = -n; break;
                    case '*': right *= n; break;
                    case '/': right /= n; break;
                }
                if (i < s.size()) {
                    op = s[i];
                }
            }
            ++i;
        }
        return left + right;
    }
    // 辅函数，检测并返回s从位置i开始的一个数字
    int parseNum(const string& s, int& i) {
        int n = 0;
        while (i < s.size() && isdigit(s[i])) {
            n = 10 * n + (s[i++] - '0');
        }
        return n;
    }
public:
    int calculate(string s) {
        int i = 0;
        return parseExpr(s, i);
    }
};

// 官方题解：栈，时间 4 ms 96.58%，空间 8.7 MB 33.33%
class Solution {
public:
    int calculate(string s) {
        vector<int> stk;
        char preSign = '+';
        int num = 0, n = s.size();
        for (int i = 0; i < n; ++i) {
            if (isdigit(s[i])) {
                num = num * 10 + (s[i] - '0');
            }
            if (!isdigit(s[i]) && s[i] != ' ' || i == n - 1) {
                switch (preSign) {
                    case '+':
                        stk.emplace_back(num);
                        break;
                    case '-':
                        stk.emplace_back(-num);
                        break;
                    case '*':
                        stk.back() *= num;
                        break;
                    default:
                        stk.back() /= num;
                }
                preSign = s[i];
                num = 0;
            }
        }
        return accumulate(stk.begin(), stk.end(), 0);
    }
};

int main() {
    string s = " 3+5 / 2 ";
    Solution sol;
    int ret = sol.calculate(s);
    cout << ret << endl;

    return 0;
}