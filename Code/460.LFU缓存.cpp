#include<iostream>
#include<unordered_map>
#include<list>
using namespace std;

struct Node {
    int key, value, freq;
    Node(int _key, int _val, int _fre = 1) : key(_key), value(_val), freq(_fre) {}
};

// 我的解法参考官方思路：双哈希表内含双向链表，时间 496 ms 26.72%，空间 178.3 MB 31.49% 
class LFUCache {
private:
    unordered_map<int, list<Node>> freqTable;
    unordered_map<int, list<Node>::iterator> keyTable;
    int capacity, minFreq;
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(INT_MAX) {}

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            int findVal = it->second->value, findFreq = it->second->freq;
            freqTable[findFreq].erase(it->second);
            if (freqTable[findFreq].empty()) {
                freqTable.erase(findFreq);
                if (findFreq == minFreq) ++minFreq;
            }
            keyTable.erase(it);
            auto& insertedList = freqTable[++findFreq];
            insertedList.emplace_back(key, findVal, findFreq);
            keyTable.emplace(key, --insertedList.end());
            return findVal;
        }
        else return -1;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            if (keyTable.size() == capacity) {
                int preDelKey = freqTable[minFreq].front().key;
                freqTable[minFreq].pop_front();
                keyTable.erase(preDelKey);
            }
            auto& insertedList = freqTable[1];
            insertedList.emplace_back(key, value);
            keyTable.emplace(key, --insertedList.end());
            minFreq = 1;
        }
        else {
            int findFreq = it->second->freq;
            freqTable[findFreq].erase(it->second);
            if (freqTable[findFreq].empty()) {
                freqTable.erase(findFreq);
                if (findFreq == minFreq) ++minFreq;
            }
            keyTable.erase(it);
            auto& insertedList = freqTable[++findFreq];
            insertedList.emplace_back(key, value, findFreq);
            keyTable.emplace(key, --insertedList.end());
        }
    }
};

// 我的解法改进：不用每次get和replace时删除keyTable，直接在相应位置上插入，时间 428 ms 77.77%，空间 175.7 MB 51.23%
class LFUCache {
private:
    unordered_map<int, list<Node>> freqTable;
    unordered_map<int, list<Node>::iterator> keyTable;
    int capacity, minFreq;
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(INT_MAX) {}

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            int findVal = it->second->value, findFreq = it->second->freq;
            freqTable[findFreq].erase(it->second);
            if (freqTable[findFreq].empty()) {
                freqTable.erase(findFreq);
                if (findFreq == minFreq) ++minFreq;
            }
            auto& insertedList = freqTable[++findFreq];
            insertedList.emplace_back(key, findVal, findFreq);
            it->second = --insertedList.end();
            return findVal;
        }
        else return -1;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            if (keyTable.size() == capacity) {
                int preDelKey = freqTable[minFreq].front().key;
                freqTable[minFreq].pop_front();
                if (minFreq != 1 && freqTable[minFreq].empty()) {
                    freqTable.erase(minFreq);
                }
                keyTable.erase(preDelKey);
            }
            auto& insertedList = freqTable[1];
            insertedList.emplace_back(key, value);
            keyTable.emplace(key, --insertedList.end());
            minFreq = 1;
        }
        else {
            int findFreq = it->second->freq;
            freqTable[findFreq].erase(it->second);
            if (freqTable[findFreq].empty()) {
                freqTable.erase(findFreq);
                if (findFreq == minFreq) ++minFreq;
            }
            auto& insertedList = freqTable[++findFreq];
            insertedList.emplace_back(key, value, findFreq);
            it->second = --insertedList.end();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

int main() {

    LFUCache LFU(2);

    LFU.put(1, 1);
    LFU.put(2, 2);
    cout << LFU.get(1) << endl;
    LFU.put(3, 3);
    cout << LFU.get(2) << endl;
    cout << LFU.get(3) << endl;
    LFU.put(4, 4);
    cout << LFU.get(1) << endl;
    cout << LFU.get(3) << endl;
    cout << LFU.get(4) << endl;

    system("pause");
    return 0;
}