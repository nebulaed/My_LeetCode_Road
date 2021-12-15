#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ��dfs+���ݣ�4 ms��10.2 MB
class Solution {
private:
	vector<vector<int>> ret;
	vector<int> cur;
public:
	void dfs(int length, int pos, const vector<int>& nums) {
		if (cur.size() == length) {
			ret.emplace_back(cur);
			return;
		}
		if (pos == 0 && length + 1 <= nums.size()) {
			dfs(length + 1, pos, nums);
		}
		if (pos + 1 + length - cur.size() <= nums.size()) {
			dfs(length, pos + 1, nums);
		}
		if (find(cur.begin(), cur.end(), nums[pos]) == cur.end()) {
			cur.emplace_back(nums[pos]);
			dfs(length, pos + 1, nums);
			cur.pop_back();
		}
	}
	vector<vector<int>> subsets(vector<int>& nums) {
		ret.emplace_back(cur);
		dfs(1, 0, nums);
		return ret;
	}
};

// �ٷ��ⷨ��������ʵ���Ӽ�ö�٣�4 ms��6.7 MB
class Solution {
public:
	vector<int> t;
	vector<vector<int>> ans;

	vector<vector<int>> subsets(vector<int>& nums) {
		int n = nums.size();
		for (int mask = 0; mask < (1 << n); ++mask) {
			t.clear();
			for (int i = 0; i < n; ++i) {
				// �������Ƶ�mask��(1<<i)��ͬһλ��Ϊ1
				if (mask & (1 << i)) {
					t.push_back(nums[i]);
				}
			}
			ans.push_back(t);
		}
		return ans;
	}
};

// �ٷ��ⷨ����dfs+���ݣ�0 ms��7 MB
class Solution {
public:
	vector<int> t;
	vector<vector<int>> ans;

	void dfs(int cur, vector<int>& nums) {
		if (cur == nums.size()) {
			ans.emplace_back(t);
			return;
		}
		t.emplace_back(nums[cur]);
		dfs(cur + 1, nums);
		t.pop_back();
		dfs(cur + 1, nums);
	}

	vector<vector<int>> subsets(vector<int>& nums) {
		dfs(0, nums);
		return ans;
	}
};

int main() {

	vector<int> nums = { 1,2,3 };
	Solution s;
	vector<vector<int>> ret = s.subsets(nums);

	cout << "[";
	for (int i = 0; i < ret.size(); ++i) {
		cout << "[";
		for (int j = 0; j < ret[i].size(); ++j) {
			cout << ret[i][j];
			if (j != ret[i].size() - 1) cout << ",";
		}
		cout << "]";
		if (i != ret.size() - 1) cout << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}