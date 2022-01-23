#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::sort;
using std::max;

// �ҵĽⷨһ����̬�滮��ʱ�� 176 ms 53.51%���ռ� 22.2 MB 57.84%
class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		sort(pairs.begin(), pairs.end(), [](const vector<int> & lhs, const vector<int> & rhs) {
			return lhs[1] < rhs[1];
			});
		size_t n = pairs.size();
		vector<int> dp(n, 1);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				if (pairs[i - 1][0] > pairs[j - 1][1]) {
					cur = max(dp[j - 1] + 1, cur);
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// �ҵĽⷨ������̬�滮��ʱ�� 168 ms 54.73%���ռ� 22.2 MB 64.73%
class Solution {
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		sort(pairs.begin(), pairs.end(), [](const vector<int> & lhs, const vector<int> & rhs) {
			return lhs[0] < rhs[0];
			});
		size_t n = pairs.size();
		vector<int> dp(n, 1);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				if (pairs[i - 1][0] > pairs[j - 1][1]) {
					cur = max(dp[j - 1] + 1, cur);
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// �ҵĽⷨ����̰��+���ֲ��ң�ʱ�� 44 ms 99%���ռ� 22 MB 74%
// ˼·������300������������У��Ƚ�pairs�����Ҷ˵����򣬽�������Ҷ˵�ŵ�endArr�У�����pairs���ҵ�����һ��pair�����pair����˵�С��endArr�����һ��Ԫ�أ���ô����pair���Ҷ˵�Ҳ�ŵ�endArr��������С��endArr�����һ��Ԫ�أ��Ǿ���endArr���ҵ���С��pair�Ҷ˵�ĵ�һ��Ԫ�أ����ҵõ��ͽ���Ԫ���滻Ϊ��pair�Ҷ˵㡣
// ��󷵻�endArr�ĳ���
class Solution {
private:
	static bool cmp(const vector<int>& lhs, const vector<int>& rhs) {
		return lhs[1] < rhs[1];
	}
public:
	int findLongestChain(vector<vector<int>>& pairs) {
		sort(pairs.begin(), pairs.end(), cmp);
		size_t n = pairs.size();
		vector<int> endArr{ pairs.front()[1] };
		for (size_t i = 1; i < n; ++i) {
			const auto& pair = pairs[i];
			int lEnd = pair[0], rEnd = pair[1];
			if (endArr.back() < lEnd) {
				endArr.emplace_back(rEnd);
			}
			else {
				auto it = lower_bound(endArr.begin(), endArr.end(), rEnd);
				if (it != endArr.end()) {
					*it = rEnd;
				}
			}
		}
		return endArr.size();
	}
};