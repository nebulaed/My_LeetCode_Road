#include<iostream>
#include<array>
#include<vector>
using namespace std;

// �ҵĽⷨ�����򻯣��������+1�������ҽ�-1�����¹����е����������ʱ��O(n log n) 12 ms���ռ�O(n) 11.7 MB
class Solution {
public:
	int minMeetingRooms(vector<vector<int>>& intervals) {
		size_t length = intervals.size();
		vector<array<int, 2>> nums(2 * length);
		for (size_t i = 0; i < length; ++i) {
			nums[2 * i][0] = intervals[i][0];
			nums[2 * i][1] = 1;
			nums[2 * i + 1][0] = intervals[i][1];
			nums[2 * i + 1][1] = 0;
		}
		sort(nums.begin(), nums.end());
		int maxNum = 0, count = 0;
		for (size_t i = 0; i < 2 * length; ++i) {
			if (nums[i][1] == 1) {
				++count;
				maxNum = max(count, maxNum);
			}
			else --count;
		}
		return maxNum;
	}
};

