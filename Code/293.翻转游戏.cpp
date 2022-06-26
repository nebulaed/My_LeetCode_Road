#include<vector>
#include<string>
using namespace std;

// 我的解法：一次遍历，时间 O(n) 4 ms 35.68%，空间 O(1) 7.1 MB 71.35%
class Solution {
public:
    vector<string> generatePossibleNextMoves(string currentState) {
        vector<string> ret;
        size_t len = currentState.size();
        for (size_t i = 1; i < len; ++i) {
            if (currentState[i] == currentState[i - 1] && currentState[i] == '+'){
                ret.emplace_back(currentState);
                ret.back()[i] = ret.back()[i - 1] = '-';
            }
        }
        return ret;
    }
};