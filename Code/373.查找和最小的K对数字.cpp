#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// 我的解法：超时
//class Solution {
//public:
//    vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2, int k) {
//        int n1 = nums1.size(), n2 = nums2.size();
//        vector<vector<int>> ret;
//        for (int ptr1 = 0; ptr1 < n1; ++ptr1){
//            for (int ptr2 = 0; ptr2 < n2; ++ptr2){
//                ret.emplace_back(vector<int>{nums1[ptr1], nums2[ptr2]});
//            }
//        }
//        if (n1 * n2 <= k){
//            sort(ret.begin(), ret.end(), [](const vector<int>& lhs, const vector<int>& rhs){
//                return (lhs[0] + lhs[1]) < (rhs[0] + rhs[1]);
//            });
//            return ret;
//        }
//        else{
//            partial_sort(ret.begin(), ret.begin() + k, ret.end(), [](const vector<int>& lhs, const vector<int>& rhs){
//                return (lhs[0] + lhs[1]) < (rhs[0] + rhs[1]);
//            });
//            return vector<vector<int>>(ret.begin(), ret.begin() + k);
//        }
//    }
//};

// 官方题解一：优先队列+Lambda，时间 O(k log k) 184 ms 21.91%，空间 O(k) 105.1 MB 14.25%
class Solution {
public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        auto myComp = [&nums1, &nums2](const pair<int, int> &lhs, const pair<int, int> &rhs) {
            return (nums1[lhs.first] + nums2[lhs.second]) > (nums1[rhs.first] + nums2[rhs.second]);
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(myComp)> doubleIndQ{myComp};
        int minLen = min(k, n1);
        for (int i = 0; i < minLen; ++i) {
            doubleIndQ.emplace(i, 0);
        }
        vector<vector<int>> ret;
        while (k-- > 0 && !doubleIndQ.empty()) {
            auto [ind1, ind2] = doubleIndQ.top();
            doubleIndQ.pop();
            ret.emplace_back(vector<int>{nums1[ind1], nums2[ind2]});
            if (++ind2 < n2) {
                doubleIndQ.emplace(ind1, ind2);
            }
        }
        return ret;
    }
};

// 官方解法二：时间 192 ms 19.96%，空间 103.8 MB 16.53%
class Solution {
private:
    long long countLessTarget(const vector<int> &nums1, const vector<int> &nums2, int target, int n1, int n2) {
        long long cnt = 0;
        int ind1 = 0, ind2 = n2 - 1;
        while (ind1 < n1 && ind2 >= 0) {
            if (nums1[ind1] + nums2[ind2] > target) {
                --ind2;
            } else {
                cnt += ind2 + 1;
                ++ind1;
            }
        }
        return cnt;
    }

    long long myMin(long long num1, long long num2) {
        return num1 <= num2 ? num1 : num2;
    }

public:
    vector<vector<int>> kSmallestPairs(vector<int> &nums1, vector<int> &nums2, int k) {
        int n1 = nums1.size(), n2 = nums2.size();
        int left = nums1.front() + nums2.front(), right = nums1.back() + nums2.back(), pairSum = right;
        while (left <= right) {
            int mid = left + ((right - left) >> 1);
            if (countLessTarget(nums1, nums2, mid, n1, n2) < k) {
                left = mid + 1;
            } else {
                pairSum = mid;
                right = mid - 1;
            }
        }
        vector<vector<int>> ret;
        int pos = n2 - 1;
        // 找到小于pairSum的所有数对
        for (int i = 0; i < n1; ++i) {
            while (pos >= 0 && nums1[i] + nums2[pos] >= pairSum) {
                --pos;
            }
            for (int j = 0; j <= pos && k > 0; ++j, --k) {
                ret.emplace_back(vector<int>{nums1[i], nums2[j]});
            }
        }
        // 找到所有等于pairSum的数对
        pos = n2 - 1;
        for (int i = 0; i < n1 && k > 0; ++i) {
            int start1 = i;
            while (i < n1 - 1 && nums1[i] == nums1[i + 1]) {
                ++i;
            }
            while (pos >= 0 && nums1[i] + nums2[pos] > pairSum) {
                --pos;
            }
            int start2 = pos;
            while (pos > 0 && nums2[pos] == nums2[pos - 1]) {
                --pos;
            }
            if (nums1[i] + nums2[pos] != pairSum) {
                continue;
            }

            int count = myMin(k, static_cast<long long>((i - start1 + 1) * (start2 - pos + 1)));
            for (int j = 0; j < count && k > 0; ++j, --k) {
                ret.emplace_back(vector<int>{nums1[i], nums2[pos]});
            }
        }
        return ret;
    }
};

int main(){

//    vector<int> nums1{1,7,11}, nums2{2,4,6};
    vector<int> nums1{1,1,2}, nums2{1,2,3};
//    vector<int> nums1{1,7,11}, nums2{2,4,6};
    int k = 10;

    Solution sol;
    vector<vector<int>> ret = sol.kSmallestPairs(nums1, nums2, k);

    for (const auto& line: ret){
        for (int num: line){
            cout << num << ',';
        }
        cout << '\n';
    }
    return 0;
}