#include<array>
using namespace std;

// 官方解法一：时间：初始化为O(1)，其余操作为O(|S|)，其中|S|是每次插入或查询的字符串长度
//            空间：O(|T|·Σ)，其中|T|为所有插入字符串的长度之和，Σ为字符集的大小，本题Σ=26。
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