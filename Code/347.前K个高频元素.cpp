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

// �ٷ��ⷨ�������ڿ�������
