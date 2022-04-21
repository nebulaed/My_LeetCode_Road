#include<iostream>
#include<array>
#include<vector>
#include<queue>
#include<unordered_set>
#include<functional>

using namespace std;

// 我的解法：优先队列，时间 超时
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) return 1;
        // 构建小顶堆
        priority_queue<long, vector<long>, greater<long>> queMin;
        // 将最小超级丑数1放入队列
        queMin.emplace(1);
        // 用于记录已入过队的数字
        unordered_set<long> hashSet{ 1 };
        // 经过n-1次出队后，堆顶就是第n个超级丑数
        for (int i = 0; i < n - 1; ++i) {
            long x = queMin.top();
            queMin.pop();
            // 将出队的最小超级丑数与primes中所有指数相乘，得到新的超级丑数
            for (int prime : primes) {
                long superUglyNumber = x * static_cast<long>(prime);
                // 新超级丑数必须没在队列中出现过
                if (!hashSet.count(superUglyNumber)) {
                    hashSet.emplace(superUglyNumber);
                    queMin.emplace(superUglyNumber);
                }
            }
        }
        return static_cast<int>(queMin.top());
    }
};


// 我的解法：多路归并，时间 1212 ms 40.73%，空间 13.1 MB 63.38%
struct myGreater {
    bool operator() (const array<long, 3>& lhs, const array<long, 3>& rhs) const{
        return lhs[0] > rhs[0];
    }
};
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) return 1;
        priority_queue<array<long, 3>, vector<array<long, 3>>, myGreater> queMin;
        for (int i = 0; i < primes.size(); ++i) {
            queMin.emplace(array<long, 3>{primes[i], i, 0});
        }
        vector<int> ret(n, 1);
        for (int i = 1; i < n;) {
            const auto [val, primeInd, idx] = queMin.top();
            queMin.pop();
            if (val != ret[i - 1]) {
                ret[i++] = val;
            }
            queMin.emplace(array<long, 3>{static_cast<long>(ret[idx + 1])* static_cast<long>(primes[primeInd]), primeInd, idx + 1});
        }
        return ret.back();
    }
};