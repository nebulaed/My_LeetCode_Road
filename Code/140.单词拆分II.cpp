#include<vector>
#include<string>
#include<unordered_set>
using namespace std;

// 我的解法：DFS+哈希集合，时间 0 ms 100%，空间 6.9 MB 86.48%
// TODO: 优化方式：使用哈希表存储字符串 ss 的每个下标和从该下标开始的部分可以组成的句子列表，在回溯过程中如果遇到已经访问过的下标，则可以直接从哈希表得到结果，而不需要重复计算。如果到某个下标发现无法匹配，则哈希表中该下标对应的是空列表，因此可以对不能拆分的情况进行剪枝优化。
class Solution {
private:
    vector<string> ret;

    void dfs(string& s, unordered_set<string>& wordSet, bool len[], int pos, string& curr) {
        if (pos == s.size()) {
            ret.emplace_back(curr);
            return;
        }
        for (int cnt = 0; pos + cnt < s.size() && cnt < 10; ++cnt) {
            if (len[cnt]){
                string word = s.substr(pos, cnt + 1);
                if (wordSet.count(word)){
                    curr += curr.empty() ? word : ' ' + word;
                    dfs(s, wordSet, len, pos + cnt + 1, curr);
                    if (pos == 0) {
                        curr.erase(curr.size() - cnt - 1, cnt + 1);
                    } else {
                        curr.erase(curr.size() - cnt - 2, cnt + 2);
                    }
                }
            }
        }
    }
public:
    vector<string> wordBreak(string s, vector<string>& wordDict) {
        unordered_set<string> wordSet;
        bool len[10]{false};
        for (auto& word: wordDict) {
            len[word.size() - 1] = true;
            wordSet.emplace(word);
        }
        string curr;
        dfs(s, wordSet, len, 0, curr);
        return ret;
    }
};