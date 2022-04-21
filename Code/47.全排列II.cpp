#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 我的解法：dfs+回溯，时间 8 ms，空间 8.9 MB
class Solution {
private:
    vector<pair<int, int>> freq;
    vector<vector<int>> ret;
    vector<int> cur;
public:
    void dfs(const vector<int>& nums, int selected) {
        if (freq.empty()) {
            ret.emplace_back(cur);
            return;
        }
        for (int i = 0; i < freq.size(); ++i) {
            int temp = freq[i].first;
            if (temp != selected) {
                int temp2 = freq[i].second;
                for (int j = 1; j <= temp2; ++j) {
                    cur.emplace_back(freq[i].first);
                    --freq[i].second;
                    if (freq[i].second == 0) {
                        freq.erase(freq.begin() + i);
                    }
                    dfs(nums, temp);
                }
                freq.insert(freq.begin() + i, make_pair(temp, 0));
                for (int j = 1; j <= temp2; ++j) {
                    ++freq[i].second;
                    cur.pop_back();
                }
            }
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); ++i) {
            if (freq.empty() || nums[i] != freq.back().first) {
                freq.emplace_back(nums[i], 1);
            }
            else {
                ++freq.back().second;
            }
        }

        dfs(nums, 11);
        return ret;
    }
};

// 官方解法：搜索回溯 时间 8 ms, 空间 8.2 MB
class Solution {
private:
    vector<int> vis;
public:
    void backtrack(vector<int>& nums, vector<vector<int>>& ans, int idx, vector<int>& perm) {
        if (idx == nums.size()) {
            ans.emplace_back(perm);
            return;
        }
        for (int i = 0; i < nums.size(); ++i) {
            if (vis[i] || (i > 0 && nums[i] == nums[i - 1] && !vis[i - 1])) {
                continue;
            }
            perm.emplace_back(nums[i]);
            vis[i] = 1;
            backtrack(nums, ans, idx + 1, perm);
            vis[i] = 0;
            perm.pop_back();
        }
    }

    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> ans;
        vector<int> perm;
        vis.resize(nums.size());
        sort(nums.begin(), nums.end());
        backtrack(nums, ans, 0, perm);
        return ans;
    }
};

int main() {

    vector<int> nums = { 1,1,2 };

    Solution s;
    vector<vector<int>> ret = s.permuteUnique(nums);

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

    return 0;
}