#include<iostream>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

//我的解法：回溯 568 ms, 130.3 MB
class Solution {
public:
    void dfs(const vector<int>& candidates, vector<vector<int>>& ret, int target, vector<int> nums) {
        int sum = accumulate(nums.begin(), nums.end(), 0);
        if (sum > target) return;
        if (sum == target) {
            sort(nums.begin(), nums.end());
            if (!count(ret.begin(), ret.end(), nums)) {
                ret.emplace_back(nums);
            }
        }
        for (int i = 0; i < candidates.size(); ++i) {
            nums.emplace_back(candidates[i]);
            dfs(candidates, ret, target, nums);
            nums.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        auto it = candidates.begin();
        while (it != candidates.end()) {
            if (*it > target) {
                it = candidates.erase(it);
            }
            else {
                ++it;
            }
        }
        dfs(candidates, ret, target, {});

        return ret;
    }
};

//官方解法：回溯 88 ms, 44.5 MB
class Solution {
public:
    void dfs(const vector<int>& candidates, vector<vector<int>>& ret, int target, vector<int> combine, int idx) {
        if (idx == candidates.size()) {
            return;
        }
        if (target == 0) {
            ret.emplace_back(combine);
            return;
        }
        // 直接跳过candidates[idx]
        dfs(candidates, ret, target, combine, idx + 1);
        // 计算candidates[idx]
        if (target - candidates[idx] >= 0) {
            combine.emplace_back(candidates[idx]);
            dfs(candidates, ret, target - candidates[idx], combine, idx);
            combine.pop_back();
        }
    }

    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        vector<vector<int>> ret;
        vector<int> combine;
        dfs(candidates, ret, target, combine, 0);
        return ret;
    }
};

int main() {
    vector<int> candidates = { 2,3,6,7 };
    int target = 5;

    Solution s;
    vector<vector<int>> ret = s.combinationSum(candidates, target);

    for (const auto& line: ret){
        for (int num: line){
            cout << num << ",";
        }
        cout << endl;
    }
    return 0;
}