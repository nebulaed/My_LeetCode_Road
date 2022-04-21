#include<iostream>
#include<climits>
#include<stack>
#include<algorithm>
using namespace std;

// 我的解法参考评论：时间 20 ms，空间15.9 MB
class MinStack {
private:
    int minVal;
    stack<pair<int, int>> stk;
public:
    MinStack() {
        this->minVal = INT_MAX;
    }

    void push(int val) {
        this->minVal = val < this->minVal ? val : this->minVal;
        stk.emplace(val, this->minVal);
    }

    void pop() {
        stk.pop();
        minVal = stk.empty() ? INT_MAX : stk.top().second;
    }

    int top() {
        return stk.top().first;
    }

    int getMin() {
        return stk.top().second;
    }
};

// 官方解法：辅助栈，时间O(1) 24 ms,空间O(n) 15.8 MB
class MinStack {
private:
    stack<int> x_stack;
    stack<int> min_stack;
public:
    MinStack() {
        min_stack.emplace(INT_MAX);
    }

    void push(int val) {
        x_stack.emplace(val);
        min_stack.emplace(min(min_stack.top(), val));
    }

    void pop() {
        x_stack.pop();
        min_stack.pop();
    }

    int top() {
        return x_stack.top();
    }

    int getMin() {
        return min_stack.top();
    }
};


// 官方解法：辅助栈的vector实现，时间 24 ms 40.77%，空间 15.9 MB 58.35%
class MinStack {
private:
    vector<int> x_stack;
    vector<int> min_stack;
public:
    MinStack() : min_stack{ INT_MAX } {}

    void push(int val) {
        x_stack.emplace_back(val);
        min_stack.emplace_back(min(min_stack.back(), val));
    }

    void pop() {
        x_stack.pop_back();
        min_stack.pop_back();
    }

    int top() {
        return x_stack.back();
    }

    int getMin() {
        return min_stack.back();
    }
};

// 评论解法：栈+差值，时间O(1)，空间O(1)
class MinStack {
private:
    stack<long long> stk;
    long long minVal;
public:
    MinStack() {
        minVal = -1;
    }

    void push(int val) {
        if (stk.empty()) {
            stk.emplace(0);
            minVal = val;
        }
        else { // 这次放入的值减去已有最小值
            long long diff = val - minVal;
            stk.emplace(diff);
            minVal = diff < 0 ? val : minVal;
        }
    }

    void pop() {
        long long diff = stk.top();
        stk.pop();
        minVal -= diff < 0 ? diff : 0;
    }

    int top() {
        long long diff = stk.top();
        return diff < 0 ? minVal : minVal + diff;
    }

    int getMin() {
        return minVal;
    }
};

// 我的解法：用vector实现最小栈，时间 24 ms 40.77%，空间 15.9 MB 65.62%
class MinStack {
private:
    vector<int> stk;
    vector<int> minVal;
public:
    MinStack() {}

    void push(int val) {
        stk.emplace_back(val);
        if (minVal.empty() || minVal.back() >= val) {
            minVal.emplace_back(val);
        }
    }

    void pop() {
        if (stk.back() == minVal.back()) {
            minVal.pop_back();
        }
        stk.pop_back();
    }

    int top() {
        return stk.back();
    }

    int getMin() {
        return minVal.back();
    }
};

// LeetCode 101解法：时间 20 ms 74.54%，空间 16 MB 41.69%
class MinStack {
private:
    stack<int> stk;
    stack<int> minVal;
public:
    MinStack() {}

    void push(int val) {
        stk.emplace(val);
        if (minVal.empty() || minVal.top() >= val) {
            minVal.emplace(val);
        }
    }

    void pop() {
        if (stk.top() == minVal.top()) {
            minVal.pop();
        }
        stk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return minVal.top();
    }
};