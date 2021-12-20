#include<iostream>
#include<array>
using namespace std;

// �ٷ��ⷨһ��ʱ�䣺��ʼ��ΪO(1)���������ΪO(|S|)������|S|��ÿ�β�����ѯ���ַ�������
//            �ռ䣺O(|T|����)������|T|Ϊ���в����ַ����ĳ���֮�ͣ���Ϊ�ַ����Ĵ�С�����⦲=26��
class Trie {
private:
	array<Trie*, 26> children;
	bool isEnd;

	Trie* searchPrefix(string prefix) {
		Trie* node = this;
		for (char ch : prefix) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				return nullptr;
			}
			node = node->children[ch];
		}
		return node;
	}
public:
	Trie() : children(), isEnd(false) { }

	void insert(string word) {
		Trie* node = this;
		for (char ch : word) {
			ch -= 'a';
			if (node->children[ch] == nullptr) {
				node->children[ch] = new Trie();
			}
			node = node->children[ch];
		}
		node->isEnd = true;
	}

	bool search(string word) {
		Trie* node = this->searchPrefix(word);
		return node != nullptr && node->isEnd;
	}

	bool startsWith(string prefix) {
		return this->searchPrefix(prefix) != nullptr;
	}
};