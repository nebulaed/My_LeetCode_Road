#include<iostream>
#include<vector>
#include<stack>

using namespace std;

// LeetCode 101解法：单调栈，时间 128 ms 83.79%，空间 86.9 MB 30.89%
// 维持一个单调递减的栈，在栈中存放位置而非数值。从左向右遍历数组，对于每个位置p，如果p的数值比栈顶存储位置q的数值大，则取出q，并记录p到q的距离为p-q；重复这一过程，直到p对应数值小于等于栈顶存储位置的数值(或空栈)时，将p插入栈顶，然后继续。
// 在这个过程中，栈内数组保持永远单调递减，避免使用排序进行比较。
// 最后栈内剩余一些日期，说明它们之后没有出现更大的数值。
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        int n = temperatures.size();
        vector<int> ret(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!stk.empty()) {
                int prev = stk.top();
                if (temperatures[i] <= temperatures[prev]) {
                    break;
                }
                stk.pop();
                ret[prev] = i - prev;
            }
            stk.emplace(i);
        }
        return ret;
    }
};

// 我的解法：单调栈，时间 O(n) 132 ms 75.87%，空间 O(n) 86.9 MB 14.69%
class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> stk;
        int n = temperatures.size();
        vector<int> ret(n, 0);
        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int prev = stk.top();
                ret[prev] = i - prev;
                stk.pop();
            }
            stk.emplace(i);
        }
        return ret;
    }
};