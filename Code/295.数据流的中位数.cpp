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

// �ҵĽⷨ�����ȶ��У�ʱ�� 272 ms 81.67%���ռ� 114.1 MB 89.28%
class MedianFinder {
private:
	// �󶥶ѣ�������ڶѶ�
	priority_queue<int, vector<int>, less<int>> queMin;
	// С���ѣ���С���ڶѶ�
	priority_queue<int, vector<int>, greater<int>> queMax;

public:
	MedianFinder() {}

	void addNum(int num) {
		// queMinΪ�ջ���numС��queMin�е����ֵ
		if (queMin.empty() || num < queMin.top()) {
			queMin.emplace(num);
			// ��queMin��Ԫ��������queMax��Ԫ��������2������
			if (queMax.size() + 1 < queMin.size()) {
				// ��queMin�����ֵŲ��queMax��
				queMax.emplace(queMin.top());
				queMin.pop();
			}
		}
		// queMin��Ϊ����num���ڵ���queMin�����ֵ
		else {
			queMax.emplace(num);
			// ��queMax��Ԫ��������queMin��Ԫ��������
			if (queMin.size() < queMax.size()) {
				// ��queMax����СֵŲ����queMin��
				queMin.emplace(queMax.top());
				queMax.pop();
			}
		}
	}

	double findMedian() {
		// ��queMinԪ��������queMax��˵��ĿǰԪ������Ϊ��������λ��ΪqueMin���ֵ
		if (queMin.size() > queMax.size()) {
			return queMin.top();
		}
		// ������λ��ΪqueMin���ֵ��queMax��Сֵ��ƽ��ֵ
		else {
			return static_cast<double>(queMin.top() + queMax.top()) / 2.0;
		}
	}
};

// �ٷ����������򼯺�+˫ָ��
// ����ʹ�����򼯺�ά����Щ����ʹ��˫ָ��ָ�����򼯺��е���λ��Ԫ�ؼ��ɡ����ۼ���ӵ���������Ϊ����ʱ��˫ָ��ָ��ͬһ��Ԫ�ء����ۼ���ӵ���������Ϊż��ʱ��˫ָ��ֱ�ָ�򹹳���λ������������
// �������һ����num�����򼯺���ʱ�������������
// 1. ��ʼ���򼯺�Ϊ��ʱ������ֱ��������ָ��ָ��num���ڵ�λ�á�
// 2. ���򼯺�Ϊ��Ԫ��Ϊ����ʱ��left �� right ͬʱָ����λ������� num ���ڵ�����λ������ôֻҪ�� right ���ƣ������� left ���Ƽ��ɡ�
// 3. ���򼯺�Ϊ��Ԫ��Ϊż��ʱ��left �� right �ֱ�ָ�򹹳���λ����������:
// 3.1 �� num ��Ϊ�µ�Ψһ����λ��(���ڵ���left��С��right)����ô������ left ���ƣ�right ���ƣ��������Ǽ���ָ�� num ���ڵ�λ��.
// 3.2 �� num ���ڵ���right����left���ơ�
// 3.3 ��num С�� left ��С�� right����ô��right���ơ�
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