#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

// �ٷ��ⷨ1����̬�滮
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int pre = 0, maxSum = nums[0];
		for (const auto& num : nums) {
			pre = max(pre + num, num);
			maxSum = max(maxSum, pre);
		}
		return maxSum;
	}
};

// �ٷ��ⷨ2��̰���㷨
class Solution {
public:
	int maxSubArray(vector<int>& nums) {
		int ret = INT_MIN, sum = 0;
		for (int i = 0; i < nums.size(); ++i) {
			sum += nums[i];
			ret = max(ret, sum);
			if (sum < 0) {
				sum = 0;
			}
		}
		return ret;
	}
};

// �ٷ��ⷨ3�����Σ��ŵ��ǿ��Խ������������[l,r]�����⡣��O(log n)��ʱ����������������ڵĴ𰸡�
class Solution {
public:
	struct Status {
		int lSum, rSum, mSum, iSum;
	};

	Status pushUp(Status l, Status r) {
		int iSum = l.iSum + r.iSum;
		int lSum = max(l.lSum, l.iSum + r.lSum);
		int rSum = max(r.rSum, r.iSum + l.rSum);
		int mSum = max(max(l.mSum, r.mSum), l.rSum + r.lSum);
		return (Status) { lSum, rSum, mSum, iSum };
	}
	
	Status get(vector<int>& a, int l, int r) {
		if (l == r) {
			return (Status) { a[l], a[l], a[l], a[l] };
		}
		int m = (l + r) >> 1;
		Status lSub = get(a, l, m);
		Status rSub = get(a, m + 1, r);
		return pushUp(lSub, rSub);
	}

	int maxSubArray(vector<int>& nums) {
		return get(nums, 0, nums.size() - 1).mSum;
	}
};


int main() {

	vector<int> nums = { 1 };

	Solution s;
	int ret = s.maxSubArray(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}