#include<iostream>
#include<vector>
#include<queue>
#include<set>
#include<functional>

using std::vector;
using std::priority_queue;
using std::less;
using std::greater;
using std::multiset;

// 我的解法：优先队列，时间 272 ms 81.67%，空间 114.1 MB 89.28%
class MedianFinder {
private:
	// 大顶堆，最大数在堆顶
	priority_queue<int, vector<int>, less<int>> queMin;
	// 小顶堆，最小数在堆顶
	priority_queue<int, vector<int>, greater<int>> queMax;

public:
	MedianFinder() {}

	void addNum(int num) {
		// queMin为空或者num小于queMin中的最大值
		if (queMin.empty() || num < queMin.top()) {
			queMin.emplace(num);
			// 若queMin的元素数量比queMax的元素数量大2或以上
			if (queMax.size() + 1 < queMin.size()) {
				// 将queMin的最大值挪到queMax中
				queMax.emplace(queMin.top());
				queMin.pop();
			}
		}
		// queMin不为空且num大于等于queMin的最大值
		else {
			queMax.emplace(num);
			// 若queMax的元素数量比queMin的元素数量大
			if (queMin.size() < queMax.size()) {
				// 将queMax的最小值挪到的queMin中
				queMin.emplace(queMax.top());
				queMax.pop();
			}
		}
	}

	double findMedian() {
		// 若queMin元素数量比queMax大，说明目前元素数量为奇数，中位数为queMin最大值
		if (queMin.size() > queMax.size()) {
			return queMin.top();
		}
		// 否则中位数为queMin最大值和queMax最小值的平均值
		else {
			return static_cast<double>(queMin.top() + queMax.top()) / 2.0;
		}
	}
};

// 官方题解二：有序集合+双指针
// 可以使用有序集合维护这些数。使用双指针指向有序集合中的中位数元素即可。当累计添加的数的数量为奇数时，双指针指向同一个元素。当累计添加的数的数量为偶数时，双指针分别指向构成中位数的两个数。
// 尝试添加一个数num到有序集合中时，有三种情况：
// 1. 初始有序集合为空时，我们直接让左右指针指向num所在的位置。
// 2. 有序集合为中元素为奇数时，left 和 right 同时指向中位数。如果 num 大于等于中位数，那么只要让 right 右移，否则让 left 左移即可。
// 3. 有序集合为中元素为偶数时，left 和 right 分别指向构成中位数的两个数:
// 3.1 当 num 成为新的唯一的中位数(大于等于left，小于right)，那么我们让 left 右移，right 左移，这样它们即可指向 num 所在的位置.
// 3.2 当 num 大于等于right，令left右移。
// 3.3 当num 小于 left 且小于 right，那么令right左移。
class MedianFinder {
private:
	multiset<int> nums;
	multiset<int>::iterator left, right;

public:
	MedianFinder() : left(nums.end()), right(nums.end()) {}

	void addNum(int num) {
		const size_t n = nums.size();
		nums.emplace(num);
		if (n == 0) {
			left = right = nums.begin();
		}
		else if (n & 1) {
			if (num >= *left) {
				++right;
			}
			else {
				--left;
			}
		}
		else {
			if (num >= *left && num < *right) {
				++left;
				--right;
			}
			else if (num >= *right) {
				++left;
			}
			else {
				--right;
			}
		}
	}

	double findMedian() {
		return static_cast<double>(*left + *right) / 2.0;
	}
};