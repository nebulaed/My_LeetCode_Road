#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ��dfs+���ݣ�ʱ�� 0 ms�� �ռ� 7.5 MB
class Solution {
private:
	vector<int> select;
	vector<vector<int>> ret;
	vector<int> cur;
public:
	void dfs(const vector<int>& nums) {
		if (select.empty()) {
			ret.emplace_back(cur);
			return;
		}

		for (int i = 0; i < select.size(); ++i) {
			int temp = select[i];
			cur.emplace_back(nums[temp]);
			select.erase(select.begin() + i);
			dfs(nums);
			select.insert(select.begin() + i, temp);
			cur.pop_back();
		}
	}
	vector<vector<int>> permute(vector<int>& nums) {
		for (int i = 0; i < nums.size(); ++i) {
			select.emplace_back(i);
		}
		dfs(nums);
		return ret;
	}
};

// �ٷ��ⷨ������
class Solution {
public:
	void backtrack(vector<vector<int>>& res, vector<int>& output, int first, int len) {
		// ��������������
		if (first == len) {
			res.emplace_back(output);
			return;
		}
		for (int i = first; i < len; ++i) {
			// ��̬ά������
			swap(output[i], output[first]);
			// �����ݹ�����һ����
			backtrack(res, output, first + 1, len);
			// ��������
			swap(output[i], output[first]);
		}
	}
	vector<vector<int>> permute(vector<int>& nums) {
		vector<vector<int> > res;
		backtrack(res, nums, 0, (int)nums.size());
		return res;
	}
};

int main() {

	vector<int> nums = { 1,2,3 };

	Solution s;
	vector<vector<int>> ret = s.permute(nums);

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