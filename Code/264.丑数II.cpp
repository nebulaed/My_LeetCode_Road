#include<climits>
#include<iostream>
#include<queue>
#include<vector>
#include<unordered_set>
#include<functional>
#include<chrono>

using namespace std;

// 我的解法：优先队列，时间 O(n log n) 108 ms 23.06%，空间 O(n) 28 MB 24.82%
class Solution {
public:
    int nthUglyNumber(int n) {
        priority_queue<int, vector<int>, greater<int>> q;
        unordered_set<int> hashSet{1};
        q.emplace(1);
        int curr = 0;
        while(n--){
            curr = q.top();
            q.pop();
            if (curr > INT_MAX / 2) continue;
            int newNum = curr * 2;
            if (!hashSet.count(newNum)){
                hashSet.emplace(newNum);
                q.emplace(newNum);
            }
            if (curr > INT_MAX / 3) continue;
            newNum = curr * 3;
            if (!hashSet.count(newNum)){
                hashSet.emplace(newNum);
                q.emplace(newNum);
            }
            if (curr > INT_MAX / 5) continue;
            newNum = curr * 5;
            if (!hashSet.count(newNum)){
                hashSet.emplace(newNum);
                q.emplace(newNum);
            }
        }
        return curr;
    }
};

// 评论解法：多路归并，时间 O(n) 4 ms 91.88%，空间 O(n) 7.3 MB 87.54%
class Solution {
public:
    int nthUglyNumber(int n) {
        vector<int> ugly(n);
        ugly[0] = 1;
        for (int i2 = 0, i3 = 0, i5 = 0, ind = 1; ind < n; ++ind){
            int newNum2 = ugly[i2] * 2, newNum3 = ugly[i3] * 3, newNum5 = ugly[i5] * 5;
            int minNewNum = min(newNum2, min(newNum3, newNum5));
            if (minNewNum == newNum2) ++i2;
            if (minNewNum == newNum3) ++i3;
            if (minNewNum == newNum5) ++i5;
            ugly[ind] = minNewNum;
        }
        return ugly.back();
    }
};

int main() {

    using namespace chrono;
    auto start = steady_clock::now();

    Solution sol;
    int ret = sol.nthUglyNumber(1600);

    auto end = steady_clock::now();

    duration<double> durations = end-start;
    cout << ret << "\n";
    cout << "time = " << durations.count() * 1000 << "ms" << "\n";

    return 0;
}