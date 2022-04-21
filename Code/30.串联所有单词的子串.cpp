#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        vector<int> ret;
        // 判断words为空，因为下面用到了words[0]
        if (words.empty()) {
            return ret;
        }

        int word_size = words[0].size();
        int word_num = words.size();

        unordered_map<string, int> m1; // 构造hashmap
        for (int i = 0; i < word_num; ++i) {
            ++m1[words[i]];
        }

        unordered_map<string, int> m2;
        // 截取的s符合题意
        for (int i = 0, j = i; (i + word_size * word_num) <= s.size();) {
            // 分段判断
            while (j < (i + word_size * word_num)) {
                string temp_str = s.substr(j, word_size);
                j += word_size;
                // 若m1中没有截取的串，说明不匹配
                if (m1[temp_str] == 0) {
                    i = j;
                    m2.clear();
                    break;
                }
                else {
                    ++m2[temp_str];
                    // 重复次数超过m1中出现次数，跳出
                    if (m1[temp_str] < m2[temp_str]) {
                        while (m1[temp_str] < m2[temp_str]) {
                            --m2[s.substr(i, word_size)];
                            i += word_size;
                        }
                        break;
                    }
                }
            }

            // 每一段都符合，则加入答案
            if (j == (i + word_size * word_num)) {
                ret.push_back(i);
                --m2[s.substr(i, word_size)];
                i += word_size;
            }
        }
        return ret;
    }
};

int main() {
    string s = "barfoothefoobarman";
    vector<string> words = { "foo","bar" };

    Solution sol;
    vector<int> ret = sol.findSubstring(s,words);

    cout << "[";
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << ",";
    }
    cout << "]";

    return 0;
}