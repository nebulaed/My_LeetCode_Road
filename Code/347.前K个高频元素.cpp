#include<iostream>
#include<vector>
#include<map>
#include<unordered_map>
#include<queue>
using namespace std;

// �ҵĽⷨ����ϣ��+������������ʱ��O(n log n) 16 ms���ռ�O(n) 13.5 MB
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreq;
		for (int num : nums) {
			++numFreq[num];
		}
		multimap<int, int> freqNum;
		for (auto it = numFreq.begin(); it != numFreq.end(); ++it) {
			freqNum.emplace(it->second, it->first);
		}
		vector<int> ret;
		int count = 0;
		for (auto rit = freqNum.rbegin(); count < k; ++rit) {
			ret.emplace_back(rit->second);
			++count;
		}
		return ret;
	}
};

// �ٷ��ⷨһ���ѣ�ʱ��O(n log k) 16 ms���ռ�O(n)+O(k) = O(n) 13.2 MB
// ���ù�ϣ���¼ÿ�����ֳ��ֵĴ������γ�һ�������ִ������顱
// ���öѵ�˼�룺����һ��С���ѣ�Ȼ��������ִ������飺
// 1. ����ѵ�Ԫ�ظ���С��k��ֱ�Ӳ������
// 2. ����ѵ�Ԫ�ظ�������k������Ѷ��뵱ǰ�����ִ����Ĵ�С������Ѷ�����������ǰֵ�����򵯳��Ѷ�������ǰֵ�������
class Solution {
private:
	static bool cmp(pair<int, int>& left, pair<int, int>& right){
		return left.second > right.second;
	}
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreq;
		for (int num : nums) {
			++numFreq[num];
		}

		priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> q(cmp);
		for (const auto& item : numFreq) {
			if (q.size() == k) {
				if (q.top().second < item.second) {
					q.pop();
					q.emplace(item);
				}
			}
			else q.emplace(item);
		}
		vector<int> ret;
		while (!q.empty()) {
			ret.emplace_back(q.top().first);
			q.pop();
		}
		return ret;
	}
};

// �ٷ��ⷨ�������ڿ�������ʱ���O(n^2)��ƽ��O(n) 8 ms���ռ�O(n) 13.3 MB
// ������arr[l...r]����������Ĺ����У������黮��Ϊ��������arr[i...q-1]��arr[q+1...j]����ʹ��arr[i...q-1]�е�ÿһ��ֵ��������arr[q]����arr[q+1...j]�е�ÿһ��ֵ������arr[q]��
// ����k�����������arr[i...q-1]�ĳ���q-i�Ĵ�С��ϵ��
// 1. ��k<=q-i��������arr[l...r]ǰk���ֵ���͵���������arr[i...q-1]ǰk���ֵ��
// 2. ����arr[l...r]ǰk���ֵ���͵������������ȫ��Ԫ�أ������Ҳ�������arr[q+1...j]��ǰk-(q-i)���ֵ��
class Solution {
private:
	void qsort(vector<pair<int, int>>& vec, size_t start, size_t end, vector<int>& ret, int k) {
		int picked = rand() % (end - start + 1) + start;
		swap(vec[picked], vec[start]);
		
		int pivot = vec[start].second;
		size_t index = start;
		for (size_t i = start + 1; i <= end; ++i) {
			if (vec[i].second >= pivot) {
				swap(vec[index + 1], vec[i]);
				++index;
			}
		}
		swap(vec[start], vec[index]);

		if (k <= index - start) {
			qsort(vec, start, index - 1, ret, k);
		}
		else {
			for (size_t i = start; i <= index; ++i) {
				ret.emplace_back(vec[i].first);
			}
			if (k > index - start + 1) {
				qsort(vec, index + 1, end, ret, k - (index - start + 1));
			}
		}
	}

public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreqs;
		for (int num : nums) {
			++numFreqs[num];
		}
		vector<pair<int, int>> values;
		for (const auto& pair : numFreqs) {
			values.emplace_back(pair);
		}
		vector<int> ret;
		qsort(values, 0, values.size() - 1, ret, k);
		return ret;
	}
};

// LeetCode 101�ⷨ��Ͱ����ʱ�� 16 ms���ռ� 13.5 MB
// ˼·��Ͱ����ĺ�����Ϊÿ��ֵ����һ��Ͱ��Ͱ�ڼ�¼���ֵ���ֵĴ���(����������)��Ȼ���Ͱ��������
// ������[1,1,1,1,2,2,3,4]����ͨ��Ͱ����õ��ĸ�Ͱ[1,2,3,4]��ֵ�ֱ�Ϊ[4,2,1,1]����ʾÿ�����ֳ��ֵĴ�����
// Ȼ���Ͱ��Ƶ�ν�������ǰk���Ͱ����ǰk��Ƶ������������ʹ�ø��������㷨�����������ٽ���һ��Ͱ���򣬰�ÿ����Ͱ����Ƶ�η��ڲ�ͬ����Ͱ�ڡ�
// ������������ΪĿǰ���Ƶ����4������[1,2,3,4]�ĸ���Ͱ���ֱ����ľ�ͰΪ[[3,4],[2],[],[1]]����ʾ��ͬ���ֳ��ֵ�Ƶ�ʡ����Ӻ���ǰ������ֱ���ҵ�k����Ͱ��
class Solution {
public:
	vector<int> topKFrequent(vector<int>& nums, int k) {
		unordered_map<int, int> numFreqs;
		int maxCount = 0;
		for (int num : nums) {
			maxCount = max(maxCount, ++numFreqs[num]);
		}

		vector<vector<int>> buckets(maxCount + 1);
		for (const auto& pair : numFreqs){
			buckets[pair.second].emplace_back(pair.first);
		}

		vector<int> ret(k);
		int ptr = -1;
		for (int i = maxCount; i >= 0 && ptr < k - 1; --i) {
			for (int num : buckets[i]) {
				ret[++ptr] = num;
				if (ptr == k - 1) break;
			}
		}
		return ret;
	}
};