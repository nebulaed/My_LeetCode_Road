#include<array>
#include<vector>
#include<string>
#include<queue>
using namespace std;

// 我的解法：哈希表记录位置和出现次数，时间 132 ms 64.97%，空间 46.9 MB 46.60%
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        array<vector<int>, 26> hashMap{};
        int n = s.size();
        for (int i = 0; i < n; ++i) {
            hashMap[s[i] - 'a'].emplace_back(i);
        }
        int count = 0;
        for (const auto& word : words) {
            int prev = -1, curr = 0;
            array<int, 26> charFreq{};
            bool flag = false;
            for (char ch : word) {
                // 此处避免重复调用operator[]，原时间180 ms 42.18%，空间46.9 MB 42.52%
                int ind = ch - 'a', currFreq = hashMap[ind].size(), & wordchFreq = charFreq[ind];
                if (wordchFreq >= currFreq) {
                    flag = true;
                    break;
                }
                curr = hashMap[ind][wordchFreq++];
                while (wordchFreq < currFreq && curr <= prev) {
                    curr = hashMap[ind][wordchFreq++];
                }
                if (curr <= prev) {
                    flag = true;
                    break;
                }
                prev = curr;
            }
            if (flag) continue;
            ++count;
        }
        return count;
    }
};

// 官方解法：指向下一个字母的指针，时间 112 ms 81.29%，空间 40 MB 54.77%
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // buckets中保存单词在words中的索引和该单词下一个要处理的字母在该单词中的位置
        array<queue<pair<int, int>>, 26> buckets;
        for (int i = 0; i < words.size(); ++i) {
            buckets[words[i][0] - 'a'].emplace(i, 0);
        }
        int count = 0;
        for (char ch : s) {
            auto& q = buckets[ch - 'a'];
            int currSize = q.size();
            while (currSize--) {
                auto [wordInd, wordPosInd] = q.front();
                q.pop();
                // 本质上队列存放的是words中所有单词的指针，当指针走到word的尽头，说明这个word确实是s的子序列
                if (++wordPosInd == words[wordInd].size()) {
                    ++count;
                }
                // 若未到word结尾，则将下一个放入
                else {
                    buckets[words[wordInd][wordPosInd] - 'a'].emplace(wordInd, wordPosInd);
                }
            }
        }
        return count;
    }
};