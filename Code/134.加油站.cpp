#include<vector>
using namespace std;

// 我的解法：DFS，超时
class Solution {
private:
    bool dfs(const vector<int>& gas, const vector<int>& cost, int curr, int pos, int start, bool first) {
        if (pos == start && !first){
            return true;
        }
        int newCurr = curr + gas[pos] - cost[pos];
        if (newCurr >= 0) {
            int newPos = pos + 1;
            if (newPos == gas.size()){
                newPos = 0;
            }
            return dfs(gas, cost, newCurr, newPos, start, false);
        }
        return false;
    }
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int curr = 0;
        for (int i = 0; i < gas.size(); ++i) {
            if (dfs(gas, cost, curr, i, i, true)) {
                return i;
            }
        }
        return -1;
    }
};

// 官方解法：一次遍历，时间 40 ms 99.91%，空间 67.7 MB 56.80%
// 假设我们此前发现，从加油站 x 出发，每经过一个加油站就加一次油（包括起始加油站），最后一个可以到达的加油站是 y.
// 通过推导能够得出结论：从 x,y 之间的任何一个加油站出发，都无法到达加油站 y 的下一个加油站。
// 因此我们只需首先检查第0个加油站，并判断是否能环绕一周，如果不能，就从第一个无法到达的加油站开始继续检查
class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        int curr = 0;
        while (curr < n) {
            int sumOfGas = 0, sumOfCost = 0;
            int cnt = -1;
            while (++cnt < n) {
                int next = (curr + cnt) % n;
                sumOfGas += gas[next];
                sumOfCost += cost[next];
                if (sumOfCost > sumOfGas) {
                    break;
                }
            }
            if (cnt == n) {
                return curr;
            } else {
                curr += cnt + 1;
            }
        }
        return -1;
    }
};