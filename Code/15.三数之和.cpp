#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
#include<set>
using namespace std;

// 我的解法：超出时间限制
//class Solution {
//public:
//	vector<vector<int>> threeSum(vector<int>& nums) {
//		unordered_multimap<int, int> hashtable;
//		set<multiset<int>> temp = {};
//		vector<vector<int>> ret = {};
//		for (int i = 0; i < nums.size(); ++i) {
//			hashtable.insert(pair<int, int>(nums[i], i));
//		}
//		for (int i = 0; i < nums.size(); ++i) {
//			for (int j = i + 1; j < nums.size(); ++j){
//				auto it = hashtable.find(-nums[i] - nums[j]);
//				if (it != hashtable.end() && i!=j && i!=it->second && j!=it->second) {
//					multiset<int> cur_temp{ nums[i],nums[j],it->first };
//					temp.insert(cur_temp);
//				}
//			}
//		}
//		for (auto it = temp.begin(); it != temp.end(); ++it) {
//			vector<int> cur_ret = {};
//			cur_ret.assign(it->begin(), it->end());
//			ret.push_back(cur_ret);
//		}
//		return ret;
//	}
//};

// 官方解法1：排序+双指针
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ans;
        // 枚举(a,b,c)中的a
        for (int first = 0; first < n; ++first) {
            // 枚举的a必须与上个枚举的a数值不等
            if (first > 0 && nums[first] == nums[first - 1]) {
                continue;
            }
            // c对应的指针初始指向数组的最右端
            int third = n - 1;
            int target = -nums[first];
            // 枚举b
            for (int second = first + 1; second < n; ++second) {
                // 同样要保证枚举的b必须与上个枚举的b数值不等
                if (second > first + 1 && nums[second] == nums[second - 1]) {
                    continue;
                }
                // 需要保证b的指针在c的指针左侧
                while (second<third && nums[second] + nums[third]>target) {
                    --third;
                }
                // 若指针重合，随着b后续的增加
                // 就不会有满足a+b+c = 0并且b<c的c了，可以退出循环
                if (second == third) {
                    break;
                }
                if (nums[second] + nums[third] == target) {
                    ans.push_back({ nums[first],nums[second],nums[third] });
                }
            }
        }
        return ans;
    }
};

// 我的第二次解法：时间 72 ms 73.60%，空间 19.4 MB 81.43%
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        vector<vector<int>> ret;
        for (int i = 0; i < n - 2; ++i) {
            while (i > 0 && i < n - 2 && nums[i] == nums[i - 1]) {
                ++i;
            }
            int first = nums[i], secondptr = i + 1, thirdptr = n - 1;
            while (secondptr < thirdptr) {
                if (nums[secondptr] + nums[thirdptr] < -first) {
                    ++secondptr;
                }
                else if (nums[secondptr] + nums[thirdptr] > -first) {
                    --thirdptr;
                }
                else {
                    ret.emplace_back(vector<int>{first, nums[secondptr++], nums[thirdptr]});
                    while (secondptr < thirdptr && nums[secondptr] == nums[secondptr - 1]) {
                        ++secondptr;
                    }
                }
            }
        }
        return ret;
    }
};

int main() {
    vector<int> input = { -1,0,1,2,-1,-4 };

    Solution s;
    vector<vector<int>> ret = s.threeSum(input);

    cout << '[';
    for (int i = 0; i < ret.size(); ++i) {
        cout << "[ ";
        for (int j = 0; j < ret[i].size(); ++j) {
            cout << ret[i][j] << " ";
        }
        cout << ']';
    }
    cout << ']' << endl;

    return 0;
}