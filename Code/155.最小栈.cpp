#include<iostream>
#include<stack>
#include<algorithm>
using namespace std;

// �ҵĽⷨ�ο����ۣ�ʱ�� 20 ms���ռ�15.9 MB
class MinStack {
private:
	int minVal;
	stack<pair<int, int>> stk;
public:
	MinStack() {
		this->minVal = INT_MAX;
	}

	void push(int val) {
		this->minVal = val < this->minVal ? val : this->minVal;
		stk.emplace(val, this->minVal);
	}

	void pop() {
		stk.pop();
		minVal = stk.empty() ? INT_MAX : stk.top().second;
	}

	int top() {
		return stk.top().first;
	}

	int getMin() {
		return stk.top().second;
	}
};

// �ٷ��ⷨ������ջ��ʱ��O(1) 24 ms,�ռ�O(n) 15.8 MB
class MinStack {
private:
	stack<int> x_stack;
	stack<int> min_stack;
public:
	MinStack() {
		min_stack.emplace(INT_MAX);
	}

	void push(int val) {
		x_stack.emplace(val);
		min_stack.emplace(min(min_stack.top(), val));
	}

	void pop() {
		x_stack.pop();
		min_stack.pop();
	}

	int top() {
		return x_stack.top();
	}

	int getMin() {
		return min_stack.top();
	}
};

// ���۽ⷨ��ջ+��ֵ��ʱ��O(1)���ռ�O(1)
class MinStack {
private:
	stack<long long> stk;
	long long minVal;
public:
	MinStack() {
		minVal = -1;
	}

	void push(int val) {
		if (stk.empty()) {
			stk.emplace(0);
			minVal = val;
		}
		else { // ��η����ֵ��ȥ������Сֵ
			long long diff = val - minVal;
			stk.emplace(diff);
			minVal = diff < 0 ? val : minVal;
		}
	}

	void pop() {
		long long diff = stk.top();
		stk.pop();
		minVal -= diff < 0 ? diff : 0;
	}

	int top() {
		long long diff = stk.top();
		return diff < 0 ? minVal : minVal + diff;
	}

	int getMin() {
		return minVal;
	}
};