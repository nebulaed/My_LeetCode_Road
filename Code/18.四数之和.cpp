#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// 我的解法
//class Solution {
//public:
//	vector<vector<int>> fourSum(vector<int>& nums, int target) {
//		int n = nums.size();
//		sort(nums.begin(), nums.end());
//		vector<vector<int>> ans;
//		// 枚举(a,b,c,d)中的a
//		for (int first = 0; first < n; ++first) {
//			// 枚举的a必须与上个枚举的a数值不等
//			if (first > 0 && nums[first] == nums[first - 1]) {
//				continue;
//			}
//			for (int second = first + 1; second < n; ++second) {
//				// 枚举的b必须与上个枚举的b数值不等
//				if (second > first + 1 && nums[second] == nums[second - 1]) {
//					continue;
//				}
//				// c对应的指针初始指向数组的最右端
//				int fourth = n - 1;
//				int cur_target = target-nums[first]-nums[second];
//				// 枚举b
//				for (int third = second + 1; third < n; ++third) {
//					// 同样要保证枚举的c必须与上个枚举的c数值不等
//					if (third > second + 1 && nums[third] == nums[third - 1]) {
//						continue;
//					}
//					// 需要保证b的指针在c的指针左侧
//					while (third<fourth && nums[third] + nums[fourth]>cur_target) {
//						--fourth;
//					}
//					// 若指针重合，随着c后续的增加
//					// 就不会有满足a+b+c+d = 0并且c<d的d了，可以退出循环
//					if (third == fourth) {
//						break;
//					}
//					if (nums[third] + nums[fourth] == cur_target) {
//						ans.push_back({ nums[first],nums[second],nums[third],nums[fourth] });
//					}
//				}
//			}
//		}
//		return ans;
//	}
//};

// 我的解法+小优化
class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		int n = nums.size();
		if (n < 4) return {};
		sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		// 枚举(a,b,c,d)中的a
		for (int first = 0; first < n - 3; ++first) {
			// 枚举的a必须与上个枚举的a数值不等
			if (first > 0 && nums[first] == nums[first - 1]) continue;
			if (nums[first] + nums[first + 1]> target - nums[first + 2] - nums[first + 3]) break;
			if (nums[first] + nums[n - 3]< target - nums[n - 2] - nums[n - 1]) continue;
			for (int second = first + 1; second < n - 2; ++second) {
				// 枚举的b必须与上个枚举的b数值不等
				if (second > first + 1 && nums[second] == nums[second - 1]) continue;
				if (nums[first] + nums[second] > target - nums[second + 1] - nums[second + 2]) break;
				if (nums[first] + nums[second] < target - nums[n - 2] - nums[n - 1]) continue;
				// c对应的指针初始指向数组的最右端
				int fourth = n - 1;
				int cur_target = target - nums[first] - nums[second];
				// 枚举b
				for (int third = second + 1; third < n - 1; ++third) {
					// 同样要保证枚举的c必须与上个枚举的c数值不等
					if (third > second + 1 && nums[third] == nums[third - 1]) {
						continue;
					}
					// 需要保证b的指针在c的指针左侧
					while (third<fourth && nums[third] + nums[fourth]>cur_target) {
						--fourth;
					}
					// 若指针重合，随着c后续的增加
					// 就不会有满足a+b+c+d = 0并且c<d的d了，可以退出循环
					if (third == fourth) {
						break;
					}
					if (nums[third] + nums[fourth] == cur_target) {
						ans.push_back({ nums[first],nums[second],nums[third],nums[fourth] });
					}
				}
			}
		}
		return ans;
	}
};

// 官方解法：在我的基础上加小优化


int main() {
	vector<int> input = { 2,2,2,2,2 };
	int target = 8;

	Solution s;
	vector<vector<int>> ret = s.fourSum(input, target);

	cout << '[';
	for (int i = 0; i < ret.size(); ++i) {
		cout << "[ ";
		for (int j = 0; j < ret[i].size(); ++j) {
			cout << ret[i][j] << " ";
		}
		cout << ']';
	}
	cout << ']' << endl;

	system("pause");
	return 0;
}