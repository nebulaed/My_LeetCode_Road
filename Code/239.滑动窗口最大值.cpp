#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<queue>
using namespace std;

// 我的解法一：超时，时间O(nk)，空间O(1)
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

// 我的解法二：二叉排序树集合，时间O(n logn) 560 ms，空间O(n) 197.4 MB
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

// 官方题解一：优先队列，时间O(n logn) 268 ms，空间O(n) 137.5 MB
// 优先队列(堆)，其中的大根堆可以实时维护一系列元素中的最大值。
// 初始时，将数组nums的前k个元素放进优先队列中。每当向右移动窗口时，就把一个新的元素放入优先队列中，同时检查堆顶元素是否在滑动窗口中，若不在就移除掉该元素，直到堆顶元素在滑动窗口中，此时堆顶元素就是滑动窗口中的最大值。
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

// 官方题解二：单调队列，时间O(n) 236 ms，空间O(k) 128.9 MB
// 1. 若当前滑动窗口中有两个下标i和j，其中i<j，并且nums[i]<=nums[j]
// 当滑动窗口向右移动时，只要i还在窗口中，那么j也一定还在窗口中。那么由于nums[j]的存在，nums[i]一定不会是滑动窗口中的最大值，故将nums[i]移除
// 因此可以使用一个队列存储所有还没被移除的下标，[在队列中从队头到队尾的]这些下标按照，从小到大的顺序被存储
// 且这些下标对应的nums值是从大到小单调递减的
// 滑动窗口向右移动时，需要将新元素与队尾元素比较，若前者大于等于后者，则队尾元素被移除，直到队列为空或新元素小于队尾元素
// 2. 此外，当窗口向右移动时，若队首元素不在窗口内，则需从队首弹出。
// 由于需要同时弹出队首和队尾的元素，需要使用双端队列。队列中的所有下标和下标对应值满足单调性，故称作单调队列
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