#include<iostream>
#include<list>
#include<vector>
#include<algorithm>

using std::list;
using std::vector;
using std::find;

int MyHash(int key, int tableSize) {
	return key % tableSize;
}

template <typename T>
class HashTable {
public:
	// size���������
	HashTable(int size = 31) {
		hash_table_.reserve(size);
		hash_table_.resize(size);
	}
	~HashTable() {}

	// ���ҹ�ϣ���Ƿ���ڸ�ֵ
	bool Contains(const T& obj) {
		const list<T>& slot = hash_table_[Hash(obj)];
		auto it = slot.cbegin();
		for (; it != slot.cend() && *it != obj; ++it);
		return it != slow.cend();
	}

	// ����ֵ
	bool Insert(const T& obj) {
		if (Contains(obj)) {
			return false;
		}
		hash_table_[Hash(obj)].push_front(obj);
		return true;
	}

	// ɾ��ֵ
	bool Remove(const T& obj) {
		list<T> slot = hash_table_[Hash(obj)];
		auto it = find(slot.begin(), slot.end(), obj);
		slot.find(obj);
		if (it == slow.end()) {
			return false;
		}
		slot.erase(it);
		return true;
	}
private:
	vector<list<T>> hash_table_;
	// ��ϣ����
	int Hash(const T& obj) const {
		return MyHash(obj, hash_table_.size());
	}
};