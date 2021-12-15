#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
using namespace std;

// �Լ��ⷨ��dfs+���ݣ���ʱ
//class Solution {
//private:
//	int minSteps = INT_MAX;
//public:
//	void dfs(const vector<int>& nums, int pos, int steps) {
//		if (pos >= nums.size() - 1) {
//			if (steps < minSteps)
//				minSteps = steps;
//			return;
//		}
//		if (steps >= minSteps - 1) return;
//
//		for (int i = nums[pos]; i > 0; --i) {
//			if ((pos + i) >= nums.size() - 1 || nums[pos + i] != 0)
//				dfs(nums, pos + i, steps + 1);
//		}
//	}
//
//	int jump(vector<int>& nums) {
//		dfs(nums, 0, 0);
//		return minSteps;
//	}
//};

// �Լ��ⷨ������ۣ���ʱ��������һ����
//class Solution {
//private:
//	int minSteps = INT_MAX;
//public:
//	void dfs(const vector<int>& nums, int pos, int steps) {
//		if (pos >= nums.size() - 1) {
//			if (steps < minSteps)
//				minSteps = steps;
//			return;
//		}
//		if (steps >= minSteps - 1) return;
//        
//		for (int i = nums[pos]; i > 0; --i) {
//			if ((pos + i) >= nums.size() - 1 || i + nums[pos + i] > nums[pos])
//				dfs(nums, pos + i, steps + 1);
//		}
//	}
//
//	int jump(vector<int>& nums) {
//		dfs(nums, 0, 0);
//		return minSteps;
//	}
//};

// �ٷ��ⷨ1��̰���㷨��ʱ�临�Ӷ�O(n) 4 ms���ռ临�Ӷ�O(1) 16 MB
class Solution {
public:
	int jump(vector<int>& nums) {
		int maxPos = 0, n = nums.size(), end = 0, step = 0;
		for (int i = 0; i < n - 1; ++i) {
			if (i <= maxPos) {
				maxPos = max(maxPos, i + nums[i]);
				if (i == end) {
					end = maxPos;
					++step;
				}
			}
		}
		return step;
	}
};

int main() {
	vector<int> nums = { 5,8,1,8,9,8,7,1,7,5,8,6,5,4,7,3,9,9,0,6,6,3,4,8,0,5,8,9,5,3,7,2,1,8,2,3,8,9,4,7,6,2,5,2,8,2,7,9,3,7,6,9,2,0,8,2,7,8,4,4,1,1,6,4,1,0,7,2,0,3,9,8,7,7,0,6,9,9,7,3,6,3,4,8,6,4,3,3,2,7,8,5,8,6,0 };

	Solution s;
	int ret = s.jump(nums);

	cout << ret << endl;
	system("pause");
	return 0;
}