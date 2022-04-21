#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 超时
class Solution {
public:
    void dfs(const vector<int>& candidates, vector<vector<int>>& ret, int target, vector<int> nums, int idx) {
        if (target == 0) {
            sort(nums.begin(), nums.end());
            if (!count(ret.begin(), ret.end(), nums)) {
                ret.emplace_back(nums);
            }
            return;
        }
        if (idx == candidates.size()) return;
        // 直接跳过candidates[idx]
        dfs(candidates, ret, target, nums, idx + 1);
        // 计算candidates[idx]
        if (target - candidates[idx] >= 0) {
            nums.emplace_back(candidates[idx]);
            dfs(candidates, ret, target - candidates[idx], nums, idx + 1);
            nums.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        dfs(candidates, ret, target, {}, 0);
        return ret;
    }
};

// 官方解答1：递归+回溯
class Solution {
private:
    vector<pair<int, int>> freq;
    vector<vector<int>> ans;
    vector<int> sequence;

public:
    void dfs(int pos, int rest) {
        if (rest == 0) {
            ans.push_back(sequence);
            return;
        }
        if (pos == freq.size() || rest < freq[pos].first) {
            return;
        }

        dfs(pos + 1, rest);

        int most = min(rest / freq[pos].first, freq[pos].second);
        for (int i = 1; i <= most; ++i) {
            sequence.emplace_back(freq[pos].first);
            dfs(pos + 1, rest - i * freq[pos].first);
        }
        for (int i = 1; i <= most; ++i) {
            sequence.pop_back();
        }
    }

    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        for (int num : candidates) {
            if (freq.empty() || num != freq.back().first) {
                freq.emplace_back(num, 1);
            }
            else {
                ++freq.back().second;
            }
        }
        dfs(0, target);
        return ans;
    }
};

int main() {
    vector<int> candidates = { 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 };
    int target = 27;

    Solution s;
    vector<vector<int>> ret = s.combinationSum2(candidates, target);

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