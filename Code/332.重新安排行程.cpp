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

// LeetCode 101解法：时间 20 ms 56.12%，空间 13.9 MB 49.17%
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

// LeetCode 101解法小优化：时间 O(m log m) 20 ms 56.12%，空间 O(m) 13.7 MB 63.96%
// m为图中边的数量
// 用哈希表记录起止机场，其中键是起始机场，值是一个多重集合，表示对应的终止机场。因为一个人可能坐过重复的线路，所以我们需要使用多重集合储存重复值。
// 储存完成之后，我们可以利用栈来恢复从终点到起点飞行的顺序，再将结果逆序得到从起点到终点的顺序。
// 本题的关键点在于要倒过来思考，那个入度与出度差为1的节点会导致死胡同，所以必须是最后一个遍历的节点
class Solution {
public:
	vector<string> findItinerary(vector<vector<string>>& tickets) {
		// 使用multiset而非vector的目的是对任一起点对应的终点按照字典排序
		unordered_map<string, multiset<string>> hashMap;
		for (const auto& ticket : tickets) {
			hashMap[ticket[0]].emplace(ticket[1]);
		}
		// 栈-先进后出，起点先进，所以会后放入结果数组，最后需要反转
		stack<string> stk;
		stk.emplace("JFK");
		vector<string> ret;
		while (!stk.empty()) {
			const string& next = stk.top();
			// 找到该起点的终点集合
			auto& nextSet = hashMap[next];
			// 若为空，说明该节点已无下一节点，开始回溯，将栈中存储的节点不断取出放到结果数组结尾
			if (nextSet.empty()) {
				ret.emplace_back(next);
				stk.pop();
			}
			// 回溯过程或正向遍历过程中若遇到该节点有下一节点，将该节点的下一节点按字典序的第一个取出放入栈中并擦除
			else {
				stk.emplace(*nextSet.begin());
				nextSet.erase(nextSet.begin());
			}
		}
		// 翻转结果数组
		reverse(ret.begin(), ret.end());
		return ret;
	}
};

// 我的解法：时间 28 ms 15.14%，空间 15.4 MB 6.24%
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