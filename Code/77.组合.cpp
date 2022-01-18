#include<iostream>
#include<vector>

using std::vector;

// 我的解法：DFS+回溯，时间 12 ms 73.33%，空间 8.4 MB 99.86%
class Solution {
private:
	int retNum = 0;
	int count = 0;
	void dfs(vector<vector<int>>& ret, vector<int>& nums, int pos, int n, int k) {
		if (pos == k) {
			ret[count] = nums;
			++count;
			return;
		}
		if (count == retNum) return;
		for (int i = pos == 0 ? 1 : nums[pos - 1] + 1; i <= n; ++i) {
			// 修改当前节点状态
			nums[pos] = i;
			dfs(ret, nums, pos + 1, n, k);
			// 隐藏的回改当前节点状态
		}
	}

	int combination(int n, int k) {
		int retNum = 1;
		for (int i = 1; i <= n - k; ++i) {
			retNum = retNum * (i + k) / i;
		}
		return retNum;
	}
public:
	vector<vector<int>> combine(int n, int k) {
		retNum = combination(n, k);
		vector<vector<int>> ret(retNum);
		vector<int> nums(k, 0);
		dfs(ret, nums, 0, n, k);
		return ret;
	}
};