#include<iostream>
#include<vector>
using namespace std;


// �ҵĽⷨ��C���Խⷨ��˫ָ�룬ʱ�� 84 ms 10.06%���ռ� 12.6 MB 94.67%
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int* sortArrayByParityII(int* nums, int numsSize, int* returnSize) {
    int odd = 1, even = 0;
    while (odd < numsSize) {
        if (!((*(nums + odd)) & 1)) {
            // ע�����������ȥ��even�Ƿ񳬳��߽�ļ�飬��Ϊ��odd�ض��ж�Ӧ��even
            while (!((*(nums + even)) & 1)) {
                even += 2;
            }
            swap(nums + odd, nums + even);
        }
        odd += 2;
    }
    *returnSize = numsSize;
    return nums;
}

// �ҵĽⷨ��˫ָ�룬ʱ�� 20 ms 53.76%���ռ� 21 MB 35.02%
class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int n = nums.size(), even = 0;
        for (int odd = 1; odd < n; odd += 2) {
            if (!(nums[odd] & 1)) {
                while (!(nums[even] & 1)) {
                    even += 2;
                }
                swap(nums[odd], nums[even]);
            }
        }
        return nums;
    }
};