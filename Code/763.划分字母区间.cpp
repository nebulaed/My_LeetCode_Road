#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<chrono>
using namespace std;
using namespace chrono;

// 我的解法：哈希表 + 合并区间，时间 0 ms，空间 6.5 MB
// 长度为5000的字符串耗时1.022-1.229 ms，时间上比官方解法无优势
class Solution {
public:
	vector<int> partitionLabels(string s) {
		array<array<int, 2>, 26> alphabet{};
		for (auto& item : alphabet) {
			item[0] = item[1] = -1;
		}
		for (size_t i = 0; i < s.size(); ++i) {
			size_t ind = s[i] - 'a';
			if (alphabet[ind][0] == -1) {
				alphabet[ind][0] = i;
			}
			alphabet[ind][1] = i;
		}
		vector<array<int, 2>> intervals;
		for (const auto& interval : alphabet) {
			if (interval[0] != -1) {
				intervals.emplace_back(interval);
			}
		}
		sort(intervals.begin(), intervals.end(), [](const array<int, 2>& lhs, const array<int, 2>& rhs) {
			return lhs[0] < rhs[0];
			});
		vector<int> ranges;
		size_t length = intervals.size(), left = 0;
		for (size_t right = 1; right < length; ++right) {
			if (intervals[right][0] > intervals[left][1]) {
				ranges.emplace_back(intervals[left][1] - intervals[left][0] + 1);
				left = right;
			}
			else intervals[left][1] = max(intervals[left][1], intervals[right][1]);
		}
		ranges.emplace_back(intervals[left][1] - intervals[left][0] + 1);
		return ranges;
	}
};

// 我的尝试：用通用vector换array，时间 4 ms，空间 7.1 MB，用unordered_map + vector效率更低，8 ms，7.3 MB，unordered_map + array效率也低，4 ms， 6.7 MB
class Solution {
public:
	vector<int> partitionLabels(string s) {
		vector<vector<int>> alphabet(26, vector<int>(2, -1));
		for (size_t i = 0; i < s.size(); ++i) {
			size_t ind = s[i] - 'a';
			if (alphabet[ind][0] == -1) {
				alphabet[ind][0] = i;
			}
			alphabet[ind][1] = i;
		}
		vector<vector<int>> intervals;
		for (const auto& interval : alphabet) {
			if (interval[0] != -1) {
				intervals.emplace_back(interval);
			}
		}
		sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] < rhs[0];
			});
		vector<int> ranges;
		size_t length = intervals.size(), left = 0;
		for (size_t right = 1; right < length; ++right) {
			if (intervals[right][0] > intervals[left][1]) {
				ranges.emplace_back(intervals[left][1] - intervals[left][0] + 1);
				left = right;
			}
			else intervals[left][1] = max(intervals[left][1], intervals[right][1]);
		}
		ranges.emplace_back(intervals[left][1] - intervals[left][0] + 1);
		return ranges;
	}
};

// 官方解法一：贪心算法，时间O(n) 4 ms，空间O(|Σ|) 6.5 MB，Σ是字符串中的字符集，由于字符串只包含小写字母，Σ=26
// 长度为5000的字符串耗时0.973-1.07 ms
class Solution {
public:
	vector<int> partitionLabels(string s) {
		int rightEndPoints[26];
		int length = s.size();
		for (int i = 0; i < length; ++i) {
			rightEndPoints[s[i] - 'a'] = i;
		}
		vector<int> partition;
		int start = 0, end = 0;
		for (int i = 0; i < length; ++i) {
			end = max(end, rightEndPoints[s[i] - 'a']);
			if (i == end) {
				partition.emplace_back(end - start + 1);
				start = end + 1;
			}
		}
		return partition;
	}
};

int main() {
	
	string str = "ababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacaababcbacadefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdedefegdehijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklijhijhklij";

	Solution s;

	auto timeStart = system_clock::now();
	vector<int> partition = s.partitionLabels(str);
	auto timeEnd = system_clock::now();
	auto duration = duration_cast<microseconds>(timeEnd - timeStart);

	cout << "耗时" << static_cast<double>(duration.count())* microseconds::period::num / microseconds::period::den * 1000 << " ms" << endl;

	for (int num : partition) {
		cout << num << ",";
	}
	cout << endl;

	system("pause");
	return 0;
}