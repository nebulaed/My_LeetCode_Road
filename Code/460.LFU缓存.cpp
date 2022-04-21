#include<iostream>
#include<climits>
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

// 我的解法：将尾插头删改为头插尾删，时间 416 ms 84.71%，空间 175.5 MB 72.09%
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
            insertedList.emplace_front(key, findVal, findFreq);
            it->second = insertedList.begin();
            return findVal;
        }
        else return -1;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            if (keyTable.size() == capacity) {
                int preDelKey = freqTable[minFreq].back().key;
                freqTable[minFreq].pop_back();
                if (minFreq != 1 && freqTable[minFreq].empty()) {
                    freqTable.erase(minFreq);
                }
                keyTable.erase(preDelKey);
            }
            auto& insertedList = freqTable[1];
            insertedList.emplace_front(key, value);
            keyTable.emplace(key, insertedList.begin());
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
            insertedList.emplace_front(key, value, findFreq);
            it->second = insertedList.begin();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */

struct DListNode {
    int key, value, freq;
    DListNode* prev, * next;
    DListNode(int _key = -1, int _val = -1, int _fre = 1, DListNode* _prev = nullptr, DListNode* _next = nullptr) : key(_key), value(_val), freq(_fre), prev(_prev), next(_next) {}
};

class LFUCache {
private:
    unordered_map<int, pair<DListNode*, DListNode*>> freqTable;
    unordered_map<int, DListNode*> keyTable;
    int capacity, minFreq;

    void removeNode(DListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }

    void pushFrontNode(pair<DListNode*, DListNode*>& insertedList, DListNode* node) {
        auto& [head, tail] = insertedList;
        node->next = head->next;
        head->next->prev = node;
        node->prev = head;
        head->next = node;
    }

    void popBackNode(pair<DListNode*, DListNode*>& insertedList) {
        auto& tail = insertedList.second;
        DListNode* delNode = tail->prev;
        delNode->prev->next = tail;
        tail->prev = delNode->prev;
        delete delNode;
    }

    void constructList(pair<DListNode*, DListNode*>& insertedList) {
        auto& [head, tail] = insertedList;
        head = new DListNode(), tail = new DListNode(-2, -2, 1, head);
        head->next = tail;
    }
public:
    LFUCache(int capacity) : capacity(capacity), minFreq(INT_MAX) {}

    int get(int key) {
        if (capacity == 0) return -1;
        auto it = keyTable.find(key);
        if (it != keyTable.end()) {
            DListNode* preDel = it->second;
            int findVal = preDel->value, findFreq = preDel->freq;
            removeNode(preDel);
            auto& findList = freqTable[findFreq];
            if (findList.first->next == findList.second && findFreq == minFreq) {
                ++minFreq;
            }
            auto& insertedList = freqTable[++findFreq];
            if (insertedList.first == nullptr) constructList(insertedList);
            DListNode* newNode = new DListNode(key, findVal, findFreq);
            pushFrontNode(insertedList, newNode);
            it->second = newNode;
            return findVal;
        }
        else return -1;
    }

    void put(int key, int value) {
        if (capacity == 0) return;
        auto it = keyTable.find(key);
        if (it == keyTable.end()) {
            if (keyTable.size() == capacity) {
                auto& delList = freqTable[minFreq];
                int preDelKey = delList.second->prev->key;
                popBackNode(delList);
                keyTable.erase(preDelKey);
            }
            auto& insertedList = freqTable[1];
            if (insertedList.first == nullptr) constructList(insertedList);
            DListNode* newNode = new DListNode(key, value);
            pushFrontNode(insertedList, newNode);
            keyTable.emplace(key, newNode);
            minFreq = 1;
        }
        else {
            DListNode* preDel = it->second;
            int findFreq = preDel->freq;
            removeNode(preDel);
            auto& findList = freqTable[findFreq];
            if (findList.first->next == findList.second && findFreq == minFreq) {
                ++minFreq;
            }
            auto& insertedList = freqTable[++findFreq];
            if (insertedList.first == nullptr) constructList(insertedList);
            DListNode* newNode = new DListNode(key, value, findFreq);
            pushFrontNode(insertedList, newNode);
            it->second = newNode;
        }
    }
};

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

    return 0;
}