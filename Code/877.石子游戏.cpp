#include<vector>
#include<list>
using namespace std;

// �ҵĽⷨ��˼·����ʱ�� 0 ms 100%���ռ� 7.5 MB 43.59%
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int Alice = 0, Bob = 0;
        list<int> pilesList(piles.begin(), piles.end());
        bool flag = true;
        while (!pilesList.empty()) {
            if (flag) {
                if (pilesList.front() > pilesList.back()) {
                    Alice += pilesList.front();
                    pilesList.pop_front();
                }
                else {
                    Alice += pilesList.back();
                    pilesList.pop_back();
                }
            }
            else {
                if (pilesList.front() > pilesList.back()) {
                    Bob += pilesList.front();
                    pilesList.pop_front();
                }
                else {
                    Bob += pilesList.back();
                    pilesList.pop_back();
                }
            }
            flag = ~flag;
        }
        return Alice > Bob;
    }
};

// �ҵĽⷨ2��˼·����ʱ�� 4 ms 69.03%���ռ� 7.2 MB 88.87%
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int Alice = 0, Bob = 0, left = 0, right = piles.size() - 1;
        bool flag = true;
        while (left <= right) {
            if (flag) {
                if (piles[left] > piles[right]) {
                    Alice += piles[left++];
                }
                else {
                    Alice += piles[right--];
                }
            }
            else {
                if (piles[left] > piles[right]) {
                    Bob += piles[left++];
                }
                else {
                    Bob += piles[right--];
                }
            }
            flag = ~flag;
        }
        return Alice > Bob;
    }
};

// �ٷ��ⷨ����̬�滮
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int length = piles.size();
        vector<vector<int>> dp(length, vector<int>(length));
        for (int i = 0; i < length; i++) {
            dp[i][i] = piles[i];
        }
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[i][j] = max(piles[i] - dp[i + 1][j], piles[j] - dp[i][j - 1]);
            }
        }
        return dp[0][length - 1] > 0;
    }
};
// �ٷ��ⷨ����̬�滮+��������
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        int length = piles.size();
        vector<int> dp(length);
        for (int i = 0; i < length; i++) {
            dp[i] = piles[i];
        }
        for (int i = length - 2; i >= 0; i--) {
            for (int j = i + 1; j < length; j++) {
                dp[j] = max(piles[i] - dp[j], piles[j] - dp[j - 1]);
            }
        }
        return dp[length - 1] > 0;
    }
};
// �ٷ��ⷨ2����ѧ�����ֱ�ʤ
class Solution {
public:
    bool stoneGame(vector<int>& piles) {
        return true;
    }
};