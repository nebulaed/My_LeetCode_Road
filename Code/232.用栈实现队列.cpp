#include<iostream>
#include<stack>

using std::stack;

// 我的解法：时间 0 ms 100%，空间 6.8 MB 36.03%
class MyQueue {
private:
    stack<int> input, output;
public:
    MyQueue() {}

    void push(int x) {
        input.emplace(x);
    }

    int pop() {
        while (!input.empty()) {
            output.emplace(input.top());
            input.pop();
        }
        int temp = output.top();
        output.pop();
        while (!output.empty()) {
            input.emplace(output.top());
            output.pop();
        }
        return temp;
    }

    int peek() {
        while (!input.empty()) {
            output.emplace(input.top());
            input.pop();
        }
        int temp = output.top();
        while (!output.empty()) {
            input.emplace(output.top());
            output.pop();
        }
        return temp;
    }

    bool empty() {
        return input.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

// LeetCode 101解法：时间 0 ms 100%，空间 6.8 MB 39.03%
// 需要时将input的内容转移到output中，不需要转移回input，效率更高
class MyQueue {
private:
    stack<int> input, output;
public:
    MyQueue() {}

    void push(int x) {
        input.emplace(x);
    }

    int pop() {
        if (output.empty()) {
            while (!input.empty()) {
                output.emplace(input.top());
                input.pop();
            }
        }
        int temp = output.top();
        output.pop();
        return temp;
    }

    int peek() {
        if (output.empty()) {
            while (!input.empty()) {
                output.emplace(input.top());
                input.pop();
            }
        }
        return output.top();
    }

    bool empty() {
        return input.empty() && output.empty();
    }
};