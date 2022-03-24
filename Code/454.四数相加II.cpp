#include<vector>
#include<unordered_map>
using namespace std;

// �ٷ��ⷨ������+��ϣ��ʱ�� 144 ms 98.32%���ռ� 23.6 MB 80.96%
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> sums;
        for (int num1 : nums1) {
            for (int num2 : nums2) {
                int sum = num1 + num2;
                auto it = sums.find(sum);
                if (it != sums.end()) {
                    ++it->second;
                }
                else sums.emplace(sum, 1);
            }
        }
        int count = 0;
        for (int num3 : nums3) {
            for (int num4 : nums4) {
                auto it = sums.find(-num3 - num4);
                if (it != sums.end()) {
                    count += it->second;
                }
            }
        }
        return count;
    }
};