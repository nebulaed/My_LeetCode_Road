#include<climits>
#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>

using namespace std;

// 我的解法参考官方解法一思路：模拟，时间 O(|tasks|·|Σ|) 84 ms 24.32%，空间 O(|Σ|) 33.6 MB 69.98%
// |Σ|是任务种类
// 思路：选择不在冷却中的，剩余需执行次数最多的任务
//class Solution {
//public:
//    int leastInterval(vector<char>& tasks, int n) {
//        if (n == 0) return tasks.size();
//        unordered_map<char, pair<int, int>> hashMap;
//        for (char ch: tasks){
//            if (!hashMap.count(ch)){
//                hashMap.emplace(ch, pair<int,int>(1, 1));
//            } else{
//                ++hashMap[ch].first;
//            }
//        }
//        int time = 1, lastTime = 1;
//        while (!hashMap.empty()){
//            int minTime = INT_MAX, secondMinTime = INT_MAX, currAmount = 0;
//            char curr = '0';
//            for (auto& [task, p]: hashMap){
//                p.second = max(p.second, time);
//                if (p.second < minTime){
//                    currAmount = p.first;
//                    secondMinTime = minTime;
//                    minTime = p.second;
//                    curr = task;
//                }
//                else if (p.second == minTime){
//                    if (p.first > currAmount){
//                        currAmount = p.first;
//                        curr = task;
//                    }
//                    secondMinTime = minTime;
//                }
//                else if (p.second < secondMinTime){
//                    secondMinTime = p.second;
//                }
//            }
//            if (--hashMap[curr].first == 0){
//                hashMap.erase(curr);
//            } else {
//                hashMap[curr].second = time + n + 1;
//            }
//            lastTime = time;
//            if (secondMinTime != INT_MAX) {
//                time = max(time + 1, secondMinTime);
//            }
//            else time = minTime + n + 1;
//        }
//        return lastTime;
//    }
//};

// 官方解法一：模拟，时间 O(|tasks|·|Σ|) 92 ms 19.93%，空间 O(|Σ|) 33.5 MB 93.60%
//class Solution {
//public:
//    int leastInterval(vector<char> &tasks, int n) {
//        unordered_map<char, int> taskFreq;
//        for (char ch: tasks) {
//            ++taskFreq[ch];
//        }
//
//        int m = taskFreq.size(), ind = 0;
//        vector<int> nextValid(m), rest(m);
//        for (auto [_, freq]: taskFreq) {
//            nextValid[ind] = 1;
//            rest[ind++] = freq;
//        }
//
//        int time = 0, k = tasks.size();
//        for (int i = 0; i < k; ++i) {
//            ++time;
//            int minNextValid = INT_MAX;
//            for (int j = 0; j < m; ++j) {
//                if (rest[j]) {
//                    minNextValid = min(minNextValid, nextValid[j]);
//                }
//            }
//            time = max(time, minNextValid);
//            int curr = -1;
//            for (int j = 0; j < m; ++j) {
//                if (rest[j] && nextValid[j] <= time) {
//                    if (curr == -1 || rest[j] > rest[curr]) {
//                        curr = j;
//                    }
//                }
//            }
//            nextValid[curr] = time + n + 1;
//            --rest[curr];
//        }
//        return time;
//    }
//};

// 官方解法二：构造，时间 O(|tasks|+|Σ|) 48 ms 89.63%，空间 O(|Σ|) 33.4 MB 96.12%
// 我们首先考虑所有任务种类中执行次数最多的那一种，记它为 A，的执行次数为maxExec。
// 我们使用一个宽为n+1的矩阵可视化地展现执行A的时间点。其中任务以行优先的顺序执行，没有任务的格子对应 CPU 的待命状态。由于冷却时间为n，因此我们将所有的A排布在矩阵的第一列，可以保证满足题目要求，并且容易看出这是可以使得总时间最小的排布方法，对应的总时间为：(maxExec - 1)(n + 1) + 1
// 如果需要执行maxExec次的任务的数量为maxCount，那么类似地可以得到对应的总时间为：(maxExec - 1)(n + 1) + maxCount
// 当maxCount > n + 1时，填「超出」了n+1列，那么所有的 CPU 待命状态都是可以省去的。这是因为 CPU 待命状态本身只是为了规定任意两个相邻任务的执行间隔至少为n，但如果列数超过了n+1，那么就算没有这些待命状态，任意两个相邻任务的执行间隔肯定也会至少为n。此时，总执行时间就是任务的总数∣task∣。
// 因此，所需的最少时间为max{(maxExec - 1)(n + 1) + maxCount, |task|}
class Solution {
public:
    int leastInterval(vector<char> &tasks, int n) {
        unordered_map<char, int> taskFreq;
        for (char ch: tasks){
            ++taskFreq[ch];
        }

        // 最多的执行次数
        // lambda的参数列表采用auto是C++14才支持的特性
        int maxExec = max_element(taskFreq.begin(), taskFreq.end(), [] (const pair<const char, int>& lhs, const pair<const char, int>& rhs){
            return lhs.second < rhs.second;
        })->second;
        // 具有最多执行次数的任务数量
        int maxCount = 0;
        // lambda通过引用捕获外部变量maxCount，通过值捕获外部变量maxExec
        for_each(taskFreq.begin(), taskFreq.end(), [&maxCount, maxExec](const pair<const char, int>& lhs){
            maxCount += (lhs.second == maxExec);
        });

        return max((maxExec - 1) * (n + 1) + maxCount, static_cast<int>(tasks.size()));
    }
};


int main(){

    vector<char> tasks{'A','A','A','A','A','A','B','C','D','E','F','G'};

    Solution sol;
    cout << sol.leastInterval(tasks, 2) << endl;

    return 0;
}