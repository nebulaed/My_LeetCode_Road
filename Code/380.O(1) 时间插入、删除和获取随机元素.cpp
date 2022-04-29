#include<vector>
#include<unordered_map>
using namespace std;

// 我的解法：可变数组+哈希表，时间 196 ms 60.06%，空间 94.7 MB 75.54%
// 此时getRandom不是O(1)时间复杂度
class RandomizedSet {
private:
    vector<int> vec;
    unordered_map<int, int> hashMap;
public:
    RandomizedSet() {}

    bool insert(int val) {
        if (hashMap.count(val)){
            return false;
        }
        int pos = vec.size();
        hashMap.emplace(val, pos);
        vec.emplace_back(val);
        return true;
    }

    bool remove(int val) {
        if (!hashMap.count(val)){
            return false;
        }
        hashMap.erase(val);
        return true;
    }

    int getRandom() {
        int n = vec.size(), ret = vec[rand() % n];
        while(!hashMap.count(ret)){
            ret = vec[rand() % n];
        }
        return ret;
    }
};

// 我的解法参考官方解法一：可变数组+哈希表，时间 196 ms 60.06%，空间 94.7 MB 51.86%
// 用find取代count，                     时间 180 ms 93.04%，空间 94.8 MB 46.82%
// 此方法关键在于删除函数
class RandomizedSet {
private:
    vector<int> vec;
    unordered_map<int, int> hashMap;
public:
    RandomizedSet() {
        srand((unsigned)time(NULL));
    }

    bool insert(int val) {
        if (hashMap.count(val)) {
            return false;
        }
        int pos = vec.size();
        hashMap.emplace(val, pos);
        vec.emplace_back(val);
        return true;
    }

    // 关键在删除函数，若查到val，得知其在vec中的位置pos，将vec[pos]与vec.back()交换，
    // 并在hashMap中原vec.back()的位置记录更改为pos，然后vec尾删，hashMap删除val
    bool remove(int val) {
        auto it = hashMap.find(val);
        if (it == hashMap.end()) {
            return false;
        }
        int pos = it->second;
        if (pos != vec.size() - 1) {
            swap(vec[pos], vec.back());
            hashMap[vec[pos]] = pos;
        }
        vec.pop_back();
        hashMap.erase(it);
        return true;
    }

    int getRandom() {
        return vec[rand() % vec.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */