#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;

// �ҵĽⷨһ����ʱ��ʱ��O(nk)���ռ�O(1)
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		size_t length = nums.size();
		vector<int> output(length - k + 1);
		for (size_t i = 0; i <= length - k; ++i) {
			int maxNum = -1e5;
			for (size_t j = i; j < i + k; ++j) {
				maxNum = max(nums[j], maxNum);
			}
			output[i] = maxNum;
		}
		return output;
	}
};

// �ҵĽⷨ�����������������ϣ�ʱ��O(n logn) 560 ms���ռ�O(n) 197.4 MB
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		size_t length = nums.size();
		vector<int> output(length - k + 1);
		multiset<int> winSet(nums.begin(), nums.begin() + k);
		output[0] = *winSet.rbegin();
		for (size_t i = 0; i < length - k; ++i) {
			winSet.erase(winSet.find(nums[i]));
			winSet.emplace(nums[i + k]);
			output[i + 1] = *winSet.rbegin();
		}
		return output;
	}
};

// �ٷ����һ�����ȶ��У�ʱ��O(n logn) 268 ms���ռ�O(n) 137.5 MB
// ���ȶ���(��)�����еĴ���ѿ���ʵʱά��һϵ��Ԫ���е����ֵ��
// ��ʼʱ��������nums��ǰk��Ԫ�طŽ����ȶ����С�ÿ�������ƶ�����ʱ���Ͱ�һ���µ�Ԫ�ط������ȶ����У�ͬʱ���Ѷ�Ԫ���Ƿ��ڻ��������У������ھ��Ƴ�����Ԫ�أ�ֱ���Ѷ�Ԫ���ڻ��������У���ʱ�Ѷ�Ԫ�ؾ��ǻ��������е����ֵ��
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		size_t length = nums.size();
		priority_queue<pair<int, int>> q;
		for (size_t i = 0; i < k; ++i) {
			q.emplace(nums[i], i);
		}
		vector<int> output(length - k + 1);
		output[0] = q.top().first;
		for (size_t i = 0; i < length - k; ++i) {
			q.emplace(nums[i + k], i + k);
			while (q.top().second <= i) {
				q.pop();
			}
			output[i + 1] = q.top().first;
		}
		return output;
	}
};

// �ٷ��������������У�ʱ��O(n) 236 ms���ռ�O(k) 128.9 MB
// 1. ����ǰ�����������������±�i��j������i<j������nums[i]<=nums[j]
// ���������������ƶ�ʱ��ֻҪi���ڴ����У���ôjҲһ�����ڴ����С���ô����nums[j]�Ĵ��ڣ�nums[i]һ�������ǻ��������е����ֵ���ʽ�nums[i]�Ƴ�
// ��˿���ʹ��һ�����д洢���л�û���Ƴ����±꣬[�ڶ����дӶ�ͷ����β��]��Щ�±갴�գ���С�����˳�򱻴洢
// ����Щ�±��Ӧ��numsֵ�ǴӴ�С�����ݼ���
// �������������ƶ�ʱ����Ҫ����Ԫ�����βԪ�رȽϣ���ǰ�ߴ��ڵ��ں��ߣ����βԪ�ر��Ƴ���ֱ������Ϊ�ջ���Ԫ��С�ڶ�βԪ��
// 2. ���⣬�����������ƶ�ʱ��������Ԫ�ز��ڴ����ڣ�����Ӷ��׵�����
// ������Ҫͬʱ�������׺Ͷ�β��Ԫ�أ���Ҫʹ��˫�˶��С������е������±���±��Ӧֵ���㵥���ԣ��ʳ�����������
class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		size_t length = nums.size();
		deque<int> q;
		for (int i = 0; i < k; ++i) {
			while (!q.empty() && nums[i] >= nums[q.back()]) {
				q.pop_back();
			}
			q.emplace_back(i);
		}

		vector<int> ans = { nums[q.front()] };
		for (int i = k; i < length; ++i) {
			while (!q.empty() && nums[i] >= nums[q.back()]) {
				q.pop_back();
			}
			q.emplace_back(i);
			while (q.front() <= i - k) {
				q.pop_front();
			}
			ans.emplace_back(nums[q.front()]);
		}
		return ans;
	}
};