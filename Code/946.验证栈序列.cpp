#include<vector>
#include<stack>
using namespace std;

// 我的解法：模拟，时间 O(n) 8 ms 72.41%，空间 O(n) 14.7 MB 99.23%
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        stack<int, vector<int>> stk;
        int ind1 = 0, ind2 = 0, n = pushed.size();
        while (ind1 < n || ind2 < n){
            if (!stk.empty() && stk.top() == popped[ind2]){
                stk.pop();
                ++ind2;
            } else {
                if (ind1 >= n) break;
                stk.emplace(pushed[ind1++]);
            }
        }
        return ind1 == ind2;
    }
};

// 我的解法改进：模拟+固定长度vector，时间 O(n) 4 ms 96.86%，空间 O(n) 14.9 MB 71.14%
class Solution {
public:
    bool validateStackSequences(vector<int>& pushed, vector<int>& popped) {
        int ind1 = 0, ind2 = 0, indTop = -1, n = pushed.size();
        vector<int> stk(n);
        while (ind1 < n || ind2 < n){
            if (indTop != -1 && stk[indTop] == popped[ind2]){
                --indTop;
                ++ind2;
            } else {
                if (ind1 >= n) break;
                stk[++indTop] = pushed[ind1++];
            }
        }
        return ind1 == ind2;
    }
};