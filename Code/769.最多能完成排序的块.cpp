#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// LeetCode 101�ⷨ������������ʱ�� O(n) 4 ms 17.38%���ռ� O(1) 6.9 MB 76.07%
class Solution {
public:
	int maxChunksToSorted(vector<int>& arr) {
		int blockNum = 0, curMax = 0, n = arr.size();
		for (int i = 0; i < n; ++i) {
			// ��¼����ǰλ�õ����ֵ
			curMax = max(curMax, arr[i]);
			// ����ǰ���ֵ��������λ�ã���˵���ұ�һ����С������λ�õ����֣���Ҫ����Ҳ����������
			// ������ǰλ�õ����ֵ�뵱ǰ����λ�����ʱ������Ϊp�������Գɹ����һ�ηָ��������һ�ָ�λ��q֮��Ŀ�һ����q+1��p����������
			if (curMax == i) {
				++blockNum;
			}
		}
		return blockNum;
	}
};