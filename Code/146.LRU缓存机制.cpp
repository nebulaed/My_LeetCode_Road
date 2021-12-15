#include<iostream>
#include<list>
#include<unordered_map>
using namespace std;

// �ҵ������ο��ٷ����˼·��ʱ�� 424 ms���ռ� 161.2 MB
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

// �ٷ��ⷨһ����ϣ��+˫������
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
		// ʹ��αͷ����αβ���ڵ�
		head = new DLinkedNode();
		tail = new DLinkedNode();
		head->next = tail;
		tail->prev = head;
	}

	int get(int key) {
		if (!cache.count(key)) {
			return -1;
		}
		// ��� key ���ڣ���ͨ����ϣ��λ�����Ƶ�ͷ��
		DLinkedNode* node = cache[key];
		moveToHead(node);
		return node->value;
	}

	void put(int key, int value) {
		if (!cache.count(key)) {
			// ��� key �����ڣ�����һ���µĽڵ�
			DLinkedNode* node = new DLinkedNode(key, value);
			// ��ӽ���ϣ��
			cache[key] = node;
			// �����˫�������ͷ��
			addToHead(node);
			++size;
			if (size > capacity) {
				// �������������ɾ��˫�������β���ڵ�
				DLinkedNode* removed = removeTail();
				// ɾ����ϣ���ж�Ӧ����
				cache.erase(removed->key);
				// ��ֹ�ڴ�й©
				delete removed;
				--size;
			}
		}
		else {
			// ��� key ���ڣ���ͨ����ϣ��λ�����޸� value�����Ƶ�ͷ��
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


// �Ҳο��ٷ�˼·�Լ�д�İ汾��ʱ�� 364 ms���ռ� 161.2 MB
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