#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

// 官方题解一：从低到高考虑，时间O(n^2) 44 ms，空间O(log n) 11.4 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// 将people按照身高h_i为第一关键字升序，k_i为第二关键字降序进行排序
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
			});
		size_t n = people.size();
		// 初始化一个包含n个位置的空队列
		vector<vector<int>> ret(n);
		for (const auto& person : people) {
			// person的位置，应该在队列中从左往右数第k_i+1个空位置
			int spaces = person[1] + 1;
			for (size_t i = 0; i < n; ++i) {
				if (ret[i].empty()) {
					// ret[i]是空位置，spaces计数器自减1
					--spaces;
					// 已到达第k_i+1个空位置，赋值并结束循环
					if (!spaces) {
						ret[i] = person;
						break;
					}
				}
			}
		}
		return ret;
	}
};

// 官方题解二：从高到低考虑，时间O(n^2) 140 ms，空间O(log n) 11.7 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// 将people按照身高h_i为第一关键字降序，k_i为第二关键字升序进行排序
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
			});
		vector<vector<int>> ret;
		// 放入第i个人时，将其插入到k_i+1的位置
		for (const vector<int>& person : people) {
			ret.emplace(ret.begin() + person[1], person);
		}
		return ret;
	}
};

// 官方题解二优化：用双向链表提高插入效率，时间O(n^2) 32 ms，空间O(n) 12.8 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// 将people按照身高h_i为第一关键字降序，k_i为第二关键字升序进行排序
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
			});
		list<vector<int>> ret;
		// 放入第i个人时，将其插入到k_i+1的位置
		for (const vector<int>& person : people) {
			auto it = ret.begin();
			// 将it迭代器向前移动person[1]次
			advance(it, person[1]);
			ret.emplace(it, person);
		}
		return vector<vector<int>>(ret.begin(),ret.end());
	}
};