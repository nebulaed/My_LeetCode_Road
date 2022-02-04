#include<iostream>
#include<vector>
#include<queue>

using std::priority_queue;
using std::vector;
using std::pair;

// LeetCode 101�ⷨ�����ȶ��У�ʱ�� 20 ms 91.34%���ռ� 13.2 MB 85.64%
class Less {
public:
	bool operator() (const pair<int, int>& lhs, const pair<int, int>& rhs) {
		return (lhs.first < rhs.first) || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
};
class Solution {
public:
	vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
		// ����ֱ��ʹ��priority_queue<pair<int,int>>��һ����Ч��
		// Ĭ��ʹ�ô󶥶ѣ�pair��firstԽ��Խ�����Ѷ���first��ȵĻ�secondԽ��Խ�����Ѷ�
		priority_queue<pair<int, int>, vector<pair<int, int>>, Less> queMax;
		vector<vector<int>> ret;
		int i = 0, length = buildings.size();
		while (i < length || !queMax.empty()) {
			int curX = 0;
			// buildings[i]����˵�С�ڵ���queMax�󶥶ѶѶ����Ҷ˵�����Ϊ��
			if (queMax.empty() || i < length && buildings[i][0] <= queMax.top().second) {
				// ����ߵ���˵��x����Ϊbuildings[i]����˵�x����
				curX = buildings[i][0];
				// ����buildings[i]����˵����������˵���ȣ�ֱ�ӷŵ������в�++i��������ret����ӵ�
				while (i < length && curX == buildings[i][0]) {
					queMax.emplace(buildings[i][2], buildings[i][1]);
					++i;
				}
			}
			// ����queMax��Ϊ����[i>=length ��buildings[i]����˵����queMax�ĶѶ�Ԫ�ص��Ҷ˵�]
			else {
				// ����ߵ���˵��x����Ϊ�Ѷ�Ԫ�ص��Ҷ˵�x����
				curX = queMax.top().second;
				// ��queMax��Ϊ���ҵ�ǰ�������˵�x������ڵ��ڶѶ�Ԫ���Ҷ˵�x����
				while (!queMax.empty() && curX >= queMax.top().second) {
					queMax.pop();
				}
			}
			// ������Ϊ�գ�������������˵��y����(�߶�)Ϊ0������Ϊ�Ѷ�Ԫ�صĸ߶�
			int curHeight = queMax.empty() ? 0 : queMax.top().first;
			// ���������Ϊ�ջ�ǰ����߸߶Ȳ����ڽ�����������һ���������˵�ĸ߶�
			if (ret.empty() || curHeight != ret.back()[1]) {
				ret.emplace_back(vector<int>{curX, curHeight});
			}
		}
		return ret;
	}
};

// �ҵĽⷨ������LeetCode 101˼·�����ȶ��У�ʱ�� 20 ms 91.34%���ռ� 13 MB 91.96%
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