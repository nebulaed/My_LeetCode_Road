#include<random>
#include<vector>
#include<unordered_set>
#include<unordered_map>
#include<algorithm>

using namespace std;

// 我的解法：可变数组+哈希表，前缀和+二分查找，时间 328 ms 5.18%，空间 100.2 MB 98.49%
class RandomizedCollection {
private:
    vector<pair<int, int>> vec;
    vector<int> prefix;
    unordered_map<int, int> hashMap;
public:
    RandomizedCollection() {
        srand((unsigned) time(NULL));
    }

    bool insert(int val) {
        auto it = hashMap.find(val);
        if (it != hashMap.end()) {
            ++vec[it->second].second;
            for_each(prefix.begin() + it->second, prefix.end(), [](int &num) { ++num; });
            return false;
        } else {
            int pos = vec.size();
            vec.emplace_back(val, 1);
            if (prefix.empty()) prefix.emplace_back(1);
            else prefix.emplace_back(1 + prefix.back());
            hashMap.emplace(val, pos);
            return true;
        }
    }

    bool remove(int val) {
        auto it = hashMap.find(val);
        if (it == hashMap.end()) {
            return false;
        }
        int pos = it->second;
        if (--vec[pos].second == 0) {
            if (pos != vec.size() - 1) {
                hashMap[vec.back().first] = pos;
                for_each(prefix.begin() + pos, prefix.end(),
                         [pos, this](int &num) { num += vec.back().second - vec[pos].second; });
                swap(vec[pos], vec.back());
            }
            vec.pop_back();
            prefix.pop_back();
            hashMap.erase(it);
        } else {
            for_each(prefix.begin() + pos, prefix.end(), [](int &num) { --num; });
        }
        return true;
    }

    int getRandom() {
        int randNum = (rand() % prefix.back()) + 1;
        int pos = lower_bound(prefix.begin(), prefix.end(), randNum) - prefix.begin();
        return vec[pos].first;
    }
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */

// 官方解法：可变数组+哈希表套哈希集合，时间 O(1) 208 ms 83.59%，空间 O(n) 105.1 MB 81.86%
class RandomizedCollection {
private:
    unordered_map<int, unordered_set<int>> hashMap;
    vector<int> nums;

public:
    RandomizedCollection() {
        srand((unsigned) time(NULL));
    }

    bool insert(int val) {
        nums.emplace_back(val);
        hashMap[val].emplace(nums.size() - 1);
        return hashMap[val].size() == 1;
    }

    bool remove(int val) {
        auto it = hashMap.find(val);
        if (it == hashMap.end()) return false;
        int preDel = *(it->second.begin());
        nums[preDel] = nums.back();
        it->second.erase(preDel);
        hashMap[nums[preDel]].erase(nums.size() - 1);
        if (preDel < nums.size() - 1) {
            hashMap[nums[preDel]].emplace(preDel);
        }
        if (it->second.empty()) {
            hashMap.erase(it);
        }
        nums.pop_back();
        return true;
    }

    int getRandom() {
        return nums[rand() % nums.size()];
    }
};