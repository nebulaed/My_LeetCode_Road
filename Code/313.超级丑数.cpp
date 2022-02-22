#include<iostream>
#include<array>
#include<vector>
#include<queue>
#include<unordered_set>
#include<functional>

using std::array;
using std::vector;
using std::priority_queue;
using std::unordered_set;
using std::greater;

// �ҵĽⷨ�����ȶ��У�ʱ�� ��ʱ
class Solution {
public:
    int nthSuperUglyNumber(int n, vector<int>& primes) {
        if (n == 1) return 1;
        // ����С����
        priority_queue<long, vector<long>, greater<long>> queMin;
        // ����С��������1�������
        queMin.emplace(1);
        // ���ڼ�¼������ӵ�����
        unordered_set<long> hashSet{ 1 };
        // ����n-1�γ��Ӻ󣬶Ѷ����ǵ�n����������
        for (int i = 0; i < n - 1; ++i) {
            long x = queMin.top();
            queMin.pop();
            // �����ӵ���С����������primes������ָ����ˣ��õ��µĳ�������
            for (int prime : primes) {
                long superUglyNumber = x * static_cast<long>(prime);
                // �³�����������û�ڶ����г��ֹ�
                if (!hashSet.count(superUglyNumber)) {
                    hashSet.emplace(superUglyNumber);
                    queMin.emplace(superUglyNumber);
                }
            }
        }
        return static_cast<int>(queMin.top());
    }
};


// �ҵĽⷨ����·�鲢��ʱ�� 1212 ms 40.73%���ռ� 13.1 MB 63.38%
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