#include<array>
#include<vector>
#include<string>
#include<queue>
using namespace std;

// �ҵĽⷨ����ϣ���¼λ�úͳ��ִ�����ʱ�� 132 ms 64.97%���ռ� 46.9 MB 46.60%
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
                // �˴������ظ�����operator[]��ԭʱ��180 ms 42.18%���ռ�46.9 MB 42.52%
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

// �ٷ��ⷨ��ָ����һ����ĸ��ָ�룬ʱ�� 112 ms 81.29%���ռ� 40 MB 54.77%
class Solution {
public:
    int numMatchingSubseq(string s, vector<string>& words) {
        // buckets�б��浥����words�е������͸õ�����һ��Ҫ�������ĸ�ڸõ����е�λ��
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
                // �����϶��д�ŵ���words�����е��ʵ�ָ�룬��ָ���ߵ�word�ľ�ͷ��˵�����wordȷʵ��s��������
                if (++wordPosInd == words[wordInd].size()) {
                    ++count;
                }
                // ��δ��word��β������һ������
                else {
                    buckets[words[wordInd][wordPosInd] - 'a'].emplace(wordInd, wordPosInd);
                }
            }
        }
        return count;
    }
};