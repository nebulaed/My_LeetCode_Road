#include<iostream>
#include<vector>
#include<array>
#include<algorithm>
#include<chrono>
using namespace std;
using namespace chrono;

// �ҵĽⷨ����ϣ�� + �ϲ����䣬ʱ�� 0 ms���ռ� 6.5 MB
// ����Ϊ5000���ַ�����ʱ1.022-1.229 ms��ʱ���ϱȹٷ��ⷨ������
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

// �ҵĳ��ԣ���ͨ��vector��array��ʱ�� 4 ms���ռ� 7.1 MB����unordered_map + vectorЧ�ʸ��ͣ�8 ms��7.3 MB��unordered_map + arrayЧ��Ҳ�ͣ�4 ms�� 6.7 MB
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

// �ٷ��ⷨһ��̰���㷨��ʱ��O(n) 4 ms���ռ�O(|��|) 6.5 MB�������ַ����е��ַ����������ַ���ֻ����Сд��ĸ����=26
// ����Ϊ5000���ַ�����ʱ0.973-1.07 ms
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

	cout << "��ʱ" << static_cast<double>(duration.count())* microseconds::period::num / microseconds::period::den * 1000 << " ms" << endl;

	for (int num : partition) {
		cout << num << ",";
	}
	cout << endl;

	system("pause");
	return 0;
}