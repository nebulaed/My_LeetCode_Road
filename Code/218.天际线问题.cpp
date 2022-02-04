#include<iostream>
#include<vector>
#include<queue>

using std::priority_queue;
using std::vector;
using std::pair;

// LeetCode 101解法：优先队列，时间 20 ms 91.34%，空间 13.2 MB 85.64%
class Less {
public:
	bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) {
		return (lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
};
class Solution {
public:
	vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		// 这里直接使用priority_queue<pair<int,int>>是一样的效果
		// 默认使用大顶堆，pair的first越大越靠近堆顶，first相等的话second越大越靠近堆顶
		priority_queue<pair<int, int>, vector<pair<int, int>>, Less> queMax;
		vector<vector<int>> ret;
		int i = 0, length = buildings.size();
		while (i < length || !queMax.empty()) {
			int curX = 0;
			// buildings[i]的左端点小于等于queMax大顶堆堆顶的右端点或队列为空
			if (queMax.empty() || i < length && buildings[i][0] <= queMax.top().second) {
				// 天际线的左端点的x坐标为buildings[i]的左端点x坐标
				curX = buildings[i][0];
				// 假如buildings[i]的左端点与天际线左端点相等，直接放到队列中并++i，而不往ret中添加点
				while (i < length && curX == buildings[i][0]) {
					queMax.emplace(buildings[i][2], buildings[i][1]);
					++i;
				}
			}
			// 假如queMax不为空且[i>=length 或buildings[i]的左端点大于queMax的堆顶元素的右端点]
			else {
				// 天际线的左端点的x坐标为堆顶元素的右端点x坐标
				curX = queMax.top().second;
				// 若queMax不为空且当前天际线左端点x坐标大于等于堆顶元素右端点x坐标
				while (!queMax.empty() && curX >= queMax.top().second) {
					queMax.pop();
				}
			}
			// 若队列为空，则该条天际线左端点的y坐标(高度)为0，否则为堆顶元素的高度
			int curHeight = queMax.empty() ? 0 : queMax.top().first;
			// 若结果数组为空或当前天际线高度不等于结果数组中最后一个天际线左端点的高度
			if (ret.empty() || curHeight != ret.back()[1]) {
				ret.emplace_back(vector<int>{curX, curHeight});
			}
		}
		return ret;
	}
};

// 我的解法：根据LeetCode 101思路，优先队列，时间 20 ms 91.34%，空间 13 MB 91.96%
class Solution {
public:
	vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		priority_queue<pair<int, int>> queMax;
		vector<vector<int>> ret;
		int ind = 0, buildNum = buildings.size();
		while (!queMax.empty() || ind < buildNum) {
			int curX = 0, curHeight = 0;
			if (queMax.empty() || (ind < buildNum && buildings[ind][0] <= queMax.top().second)) {
				int curLeft = buildings[ind][0];
				while (ind < buildNum && buildings[ind][0] == curLeft) {
					queMax.emplace(buildings[ind][2], buildings[ind][1]);
					++ind;
				}
				curHeight = queMax.top().first;
				curX = curLeft;
			}
			else {
				int curRight = queMax.top().second;
				while (!queMax.empty() && queMax.top().second <= curRight) {
					queMax.pop();
				}
				curHeight = queMax.empty() ? 0 : queMax.top().first;
				curX = curRight;
			}
			if (ret.empty() || ret.back()[1] != curHeight) {
				ret.emplace_back(vector<int>{curX, curHeight});
			}
		}
		return ret;
	}
};