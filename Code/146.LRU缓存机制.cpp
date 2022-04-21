#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

// 我的做法参考官方题解思路：时间 424 ms，空间 161.2 MB
class LRUCache {
private:
    unordered_map<int, list<pair<int, int>>::iterator> cache;
    list<pair<int, int>> history;
    int capacity;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            int ret = it->second->second;
            history.erase(it->second);
            history.emplace_back(key, ret);
            cache[key] = --history.end();
            return ret;
        }
        else {
            return -1;
        }
    }

    void put(int key, int value) {
        if (!cache.count(key) && cache.size() < capacity) {
            history.emplace_back(key, value);
            cache.emplace(key, --history.end());
        }
        else if (cache.count(key)) {
            history.erase(cache[key]);
            history.emplace_back(key, value);
            cache[key] = --history.end();
        }
        else {
            int temp = history.front().first;
            history.pop_front();
            cache.erase(temp);
            history.emplace_back(key, value);
            cache.emplace(key, --history.end());
        }
    }
};

// 官方解法一：哈希表+双向链表
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode* head;
    DLinkedNode* tail;
    int size;
    int capacity;

public:
    LRUCache(int _capacity) : capacity(_capacity), size(0) {
        // 使用伪头部和伪尾部节点
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        // 如果 key 存在，先通过哈希表定位，再移到头部
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            // 如果 key 不存在，创建一个新的节点
            DLinkedNode* node = new DLinkedNode(key, value);
            // 添加进哈希表
            cache[key] = node;
            // 添加至双向链表的头部
            addToHead(node);
            ++size;
            if (size > capacity) {
                // 如果超出容量，删除双向链表的尾部节点
                DLinkedNode* removed = removeTail();
                // 删除哈希表中对应的项
                cache.erase(removed->key);
                // 防止内存泄漏
                delete removed;
                --size;
            }
        }
        else {
            // 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }

    DLinkedNode* removeTail() {
        DLinkedNode* node = tail->prev;
        removeNode(node);
        return node;
    }
};


// 我参考官方思路自己写的版本，时间 364 ms，空间 161.2 MB
struct DListNode {
    int key, val;
    DListNode* prev, * next;
    DListNode() {
        key = 0;
        val = 0;
        prev = nullptr;
        next = nullptr;
    }
    DListNode(int _key, int _val) {
        key = _key;
        val = _val;
        prev = nullptr;
        next = nullptr;
    }
};

class LRUCache {
private:
    unordered_map<int, DListNode*> cache;
    int capacity;
    DListNode* head, * tail;
public:
    LRUCache(int capacity) {
        this->capacity = capacity;
        this->head = new DListNode();
        this->tail = new DListNode();
        this->head->next = this->tail;
        this->tail->prev = this->head;
    }

    int get(int key) {
        auto it = cache.find(key);
        if (it != cache.end()) {
            DListNode* temp = it->second;
            int ret = temp->val;
            removeNode(temp);
            pushBackNode(temp);
            return ret;
        }
        else {
            return -1;
        }
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            if (cache.size() >= capacity) {
                cache.erase(this->head->next->key);
                popBackFront();
            }
            DListNode* node = new DListNode(key, value);
            pushBackNode(node);
            cache.emplace(key, node);
        }
        else {
            cache[key]->val = value;
            removeNode(cache[key]);
            pushBackNode(cache[key]);
        }
    }

    void removeNode(DListNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void pushBackNode(DListNode* node) {
        node->next = this->tail;
        node->prev = this->tail->prev;
        this->tail->prev->next = node;
        this->tail->prev = node;
    }

    void popBackFront() {
        DListNode* node = this->head->next;
        node->next->prev = this->head;
        this->head->next = node->next;
        delete node;
    }
};