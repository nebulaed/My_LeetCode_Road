#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<numeric>
using namespace std;

// 我的解法：时间 44 ms，空间 21.9 MB
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        vector<string> duplication = strs;
        unordered_map<string, vector<int>> hashmap;
        vector<vector<string>> ret;


        for (int i = 0; i < strs.size(); ++i) {
            sort(strs[i].begin(), strs[i].end());
            if (hashmap.count(strs[i])) {
                hashmap[strs[i]].emplace_back(i);
            }
            else {
                pair<string, vector<int>> temp(strs[i], { i });
                hashmap.insert(temp);
            }
        }
        for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
            vector<string> cur;
            for (int i = 0; i < it->second.size(); ++i) {
                cur.emplace_back(duplication[it->second[i]]);
            }
            ret.emplace_back(cur);
        }
        return ret;
    }
};

// 官方解法1：排序 时间O(nk log k) 32 ms, 空间O(nk) 19.1 MB
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        vector<vector<string>> ret;

        for (int i = 0; i < strs.size(); ++i) {
            string key = strs[i];
            sort(key.begin(), key.end());
            mp[key].emplace_back(strs[i]);
        }
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ret.emplace_back(it->second);
        }
        return ret;
    }
};

// 官方解法2：计数，用每个字母出现得次数作为key设计哈希表
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        // 自定义对 array<int, 26> 类型的哈希函数
        auto arrayHash = [fn = hash<int>{}](const array<int, 26>& arr)->size_t {
            return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
                return (acc << 1) ^ fn(num);
            });
        };

        unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
        for (string& str : strs) {
            array<int, 26> counts{};
            int length = str.length();
            for (int i = 0; i < length; ++i) {
                counts[str[i] - 'a'] ++;
            }
            mp[counts].emplace_back(str);
        }
        vector<vector<string>> ans;
        for (auto it = mp.begin(); it != mp.end(); ++it) {
            ans.emplace_back(it->second);
        }
        return ans;
    }
};

// 类似官方解法2的评论解法
class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> mp;
        vector<vector<string>> ret;

        for (auto& str : strs) {
            string count = string(26, '0');
            for (auto& c : str) {
                ++count[c - 'a'];
            }
            mp[count].emplace_back(str);
        }
        for (auto& it : mp) {
            ret.emplace_back(it.second);
        }
        return ret;
    }
};

int main() {

    vector<string> strs = { "eat","tea","tan","ate","nat","bat" };

    Solution s;
    vector<vector<string>> ret = s.groupAnagrams(strs);


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