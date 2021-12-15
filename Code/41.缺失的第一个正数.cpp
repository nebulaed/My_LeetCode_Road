#include<iostream>
#include<vector>
#include<unordered_set>
using namespace std;

// �ҵ���ͨ�ⷨ, ʱ��O(n) 252 ms���ռ�O(n) 129.5 MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		unordered_set<int> hashset;
		for (int i = 0; i < nums.size(); ++i) {
			hashset.insert(nums[i]);
		}
		int i = 1;
		while (hashset.count(i)) {
			++i;
		}
		return i;
	}
};

// �ٷ��ⷨһ�������������鹹���ϣ��ʱ��O(n) 112ms, �ռ�O(n) 80.9MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			if (nums[i] <= 0) {
				nums[i] = n + 1;
			}
		}
		for (int i = 0; i < n; ++i) {
			if (abs(nums[i]) <= n && nums[abs(nums[i]) - 1] > 0) {
				nums[abs(nums[i]) - 1] = -nums[abs(nums[i]) - 1];
			}
		}
		for (int i = 0; i < n; ++i) {
			if (nums[i] > 0) {
				return i + 1;
			}
		}
		return n + 1;
	}
};

// �ٷ��ⷨ�����û���ʱ��O(n) 136 ms���ռ�O(1) 80.9 MB
class Solution {
public:
	int firstMissingPositive(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
				swap(nums[nums[i] - 1], nums[i]);
			}
		}
		for (int i = 0; i < n; ++i) {
			if (nums[i] != i + 1) {
				return i + 1;
			}
		}
		return n + 1;
	}
};

int main() {
	vector<int> nums = { 3,4,-1,1 };

	Solution s;
	int ret = s.firstMissingPositive(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}