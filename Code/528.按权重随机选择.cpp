#include<iostream>
#include<vector>
#include<numeric>
#include<algorithm>

using std::vector;
using std::partial_sum;
using std::lower_bound;

// LeetCode 101�ⷨ����partial_sum��ǰ׺�ͣ�����ǰλ�ú�ǰ���������ֵĺ͡���������Ϊ����������
// ʱ�� 68 ms 90.99%���ռ� 39.1 MB 95.42%
// ÿ����Ҫ����ʱ������[1,Ȩ�غ�]���������һ�����֣�Ȼ���ö��ֲ�������ǰ׺���е�λ�ã�ģ���Ȩ�������̡�
class Solution {
private:
	vector<int> sums;
public:
	Solution(vector<int>& w) : sums(move(w)) {
		partial_sum(sums.begin(), sums.end(), sums.begin());
	}

	int pickIndex() {
		int pos = (rand() % sums.back()) + 1;
		return lower_bound(sums.begin(), sums.end(), pos) - sums.begin();
	}
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */