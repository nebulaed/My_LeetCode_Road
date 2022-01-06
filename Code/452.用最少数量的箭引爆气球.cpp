#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ��̰���㷨��ʱ�� 360 ms���ռ� 87.7 MB
// ��435�����ƣ�Ψһ��������ָ��ָ���������������ָ��ָ��������ҽ��˵�����ص�������Ҳ���ص�
class Solution {
public:
	int findMinArrowShots(vector<vector<int>>& points) {
		sort(points.begin(), points.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[1] < rhs[1];
			});
		int count = 1;
		size_t length = points.size(), left = 0;
		for (size_t right = 1; right < length; ++right) {
			if (points[right][0] > points[left][1]) {
				++count;
				left = right;
			}
		}
		return count;
	}
};