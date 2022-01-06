#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		// ����������ҽ��С�����������
		sort(intervals.begin(), intervals.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[1] < rhs[1];
			});
		// ��ʼ����������ΪtotalNum��Ҫ��������������Ϊ1
		int totalNum = intervals.size(), count = 1;
		// ��ʼ����ָ��Ϊ0
		size_t left = 0;
		for (size_t right = 1; right < totalNum; ++right) {
			// ����ָ��ָ������������ڵ�����ָ��ָ��������ҽ磬˵���������������ص���rightָ��ָ�������Ҫ����������������������count��һ
			// ͬʱ������ָ������䱣������ָ�����Ϊ��ָ��ָ������
			if (intervals[right][0] >= intervals[left][1]) {
				++count;
				left = right;
			}
		}
		// ������ȥ��������������Ϊ�Ƴ�������С����
		return totalNum - count;
	}
};