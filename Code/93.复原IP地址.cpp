#include<vector>
#include<string>
using namespace std;

// 我的解法：时间 0 ms 100%，空间 6.5 MB 52.47%
class Solution {
private:
    const static int SEG_COUNT = 4;
    vector<int> segments;
    vector<string> ret;

    void dfs(const string& s, int segNum, int segStart) {
        if (segNum == SEG_COUNT) {
            if (segStart == s.size()) {
                string currIP;
                for (int i = 0; i < SEG_COUNT; ++i) {
                    currIP += to_string(segments[i]);
                    if (i != SEG_COUNT - 1) currIP += ".";
                }
                ret.emplace_back(move(currIP));
            }
            return;
        }
        if (segStart == s.size()) return;
        if (s[segStart] == '0') {
            segments[segNum] = 0;
            dfs(s, segNum + 1, segStart + 1);
        }

        int addr = 0;
        for (int segEnd = segStart; segEnd < s.size(); ++segEnd) {
            addr = addr * 10 + (s[segEnd] - '0');
            if (addr > 0 && addr <= 255) {
                segments[segNum] = addr;
                dfs(s, segNum + 1, segEnd + 1);
            }
            else break;
        }
    }
public:
    Solution() : segments(SEG_COUNT) {}
    vector<string> restoreIpAddresses(string s) {
        dfs(s, 0, 0);
        return ret;
    }
};