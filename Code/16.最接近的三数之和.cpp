#include<iostream>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;

// 做不出来
//class Solution {
//public:
//	int threeSumClosest(vector<int>& nums, int target) {
//		int n = nums.size();
//		sort(nums.begin(), nums.end());
//		int deviation = INT_MAX;
//		// 枚举(a,b,c)中的a
//		for (int first = 0; first < n; ++first) {
//			// 枚举的a必须与上个枚举的a数值不等
//			if (first > 0 && nums[first] == nums[first - 1]) {
//				continue;
//			}
//			// c对应的指针初始指向数组的最右端
//			int third = n - 1;
//			int cur_target = target - nums[first];
//			// 枚举b
//			for (int second = first + 1; second < n && second != third; ++second) {
//				// 同样要保证枚举的b必须与上个枚举的b数值不等
//				if (second > first + 1 && nums[second] == nums[second - 1]) {
//					continue;
//				}
//				// 需要保证b的指针在c的指针左侧
//				while (second<third-1 && abs(cur_target - nums[second] - nums[third-1])<= abs(cur_target - nums[second] - nums[third])) {
//					--third;
//				}
//				if (abs(cur_target - nums[second] - nums[third]) < abs(deviation)) {
//					deviation = cur_target - nums[second] - nums[third];
//				}
//			}
//		}
//		return target - deviation;
//	}
//};

// 官方解答1：排序 + 双指针
class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        int deviation = INT_MAX;
        // 枚举(a,b,c)中的a
        for (int first = 0; first < n; ++first) {
            // 枚举的a必须与上个枚举的a数值不等
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // b对应的指针初始指向a+1，c对应的指针初始指向数组的最右端
            int third = n - 1;
            int second = first + 1;
            // 使用双指针枚举b和c
            while (second < third) {
                if (abs(target - nums[first] - nums[second] - nums[third]) < abs(deviation)) {
                    // 更新绝对值最小的deviation
                    deviation = target - nums[first] - nums[second] - nums[third];
                    // 若当前和等于target直接返回答案
                    if (!deviation) return target;
                }
                // 若和大于target，向左移动c
                if (nums[first] + nums[second] + nums[third] >= target) {
                    --third;
                    // 若c和c+1相等，则c再次向左移动
                    while (second < third && nums[third] == nums[third + 1]) {
                        --third;
                    }
                }
                    // 若和小于target，向右移动b
                else {
                    ++second;
                    // 若b和b-1相等，则b再次向右移动
                    while (second < third && nums[second] == nums[second - 1]) {
                        ++second;
                    }
                }
            }
        }
        return target - deviation;
    }
};


int main() {
    vector<int> nums = { 1,1,-1,-1,3 };
    int target = -1;

    Solution s;
    int ret = s.threeSumClosest(nums,target);

    cout << ret << endl;

    return 0;
}