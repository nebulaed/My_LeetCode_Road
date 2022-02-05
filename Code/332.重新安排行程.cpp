#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<unordered_map>
#include<stack>

using std::vector;
using std::string;
using std::set;
using std::multiset;
using std::unordered_map;
using std::stack;

// LeetCode 101�ⷨ��ʱ�� 20 ms 56.12%���ռ� 13.9 MB 49.17%
class Solution {
public:
	vector<string> findItinerary(vector<vector<string>>& tickets) {
		unordered_map<string, multiset<string>> hashMap;
		for (const auto& ticket : tickets) {
			hashMap[ticket[0]].emplace(ticket[1]);
		}
		stack<string> stk;
		stk.emplace("JFK");
		vector<string> ret;
		while (!stk.empty()) {
			string next = stk.top();
			if (hashMap[next].empty()) {
				ret.emplace_back(next);
				stk.pop();
			}
			else {
				stk.emplace(*hashMap[next].begin());
				hashMap[next].erase(hashMap[next].begin());
			}
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

// LeetCode 101�ⷨС�Ż���ʱ�� O(m log m) 20 ms 56.12%���ռ� O(m) 13.7 MB 63.96%
// mΪͼ�бߵ�����
// �ù�ϣ���¼��ֹ���������м�����ʼ������ֵ��һ�����ؼ��ϣ���ʾ��Ӧ����ֹ��������Ϊһ���˿��������ظ�����·������������Ҫʹ�ö��ؼ��ϴ����ظ�ֵ��
// �������֮�����ǿ�������ջ���ָ����յ㵽�����е�˳���ٽ��������õ�����㵽�յ��˳��
// ����Ĺؼ�������Ҫ������˼�����Ǹ��������Ȳ�Ϊ1�Ľڵ�ᵼ������ͬ�����Ա��������һ�������Ľڵ�
class Solution {
public:
	vector<string> findItinerary(vector<vector<string>>& tickets) {
		// ʹ��multiset����vector��Ŀ���Ƕ���һ����Ӧ���յ㰴���ֵ�����
		unordered_map<string, multiset<string>> hashMap;
		for (const auto& ticket : tickets) {
			hashMap[ticket[0]].emplace(ticket[1]);
		}
		// ջ-�Ƚ����������Ƚ������Ի����������飬�����Ҫ��ת
		stack<string> stk;
		stk.emplace("JFK");
		vector<string> ret;
		while (!stk.empty()) {
			const string& next = stk.top();
			// �ҵ��������յ㼯��
			auto& nextSet = hashMap[next];
			// ��Ϊ�գ�˵���ýڵ�������һ�ڵ㣬��ʼ���ݣ���ջ�д洢�Ľڵ㲻��ȡ���ŵ���������β
			if (nextSet.empty()) {
				ret.emplace_back(next);
				stk.pop();
			}
			// ���ݹ��̻���������������������ýڵ�����һ�ڵ㣬���ýڵ����һ�ڵ㰴�ֵ���ĵ�һ��ȡ������ջ�в�����
			else {
				stk.emplace(*nextSet.begin());
				nextSet.erase(nextSet.begin());
			}
		}
		// ��ת�������
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

// �ҵĽⷨ��ʱ�� 28 ms 15.14%���ռ� 15.4 MB 6.24%
class Solution {
public:
	vector<string> findItinerary(vector<vector<string>>& tickets) {
		set<string> locSet;
		for (const auto& pair : tickets) {
			locSet.emplace(pair[0]);
			locSet.emplace(pair[1]);
		}
		unordered_map<string, int> locMap;
		unordered_map<int, string> locMap2;
		int ind = 0;
		for (const auto& str : locSet) {
			locMap[str] = ind;
			locMap2[ind++] = str;
		}
		unordered_map<int, multiset<int>> hashMap;
		for (const auto& ticket : tickets) {
			hashMap[locMap[ticket[0]]].emplace(locMap[ticket[1]]);
		}
		stack<int> stk;
		stk.emplace(locMap["JFK"]);
		vector<string> ret;
		while (!stk.empty()) {
			int next = stk.top();
			if (hashMap[next].empty()) {
				ret.emplace_back(locMap2[next]);
				stk.pop();
			}
			else {
				stk.emplace(*hashMap[next].begin());
				hashMap[next].erase(hashMap[next].begin());
			}
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
};