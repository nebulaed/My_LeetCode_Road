#include<iostream>
#include<queue>

using std::queue;

// 我的解法1：时间 4 ms 13%，空间 6.7 MB 35%
class MyStack {
private:
	queue<int> input;
	queue<int> output;
public:
	MyStack() {}

	void push(int x) {
		input.emplace(x);
	}

	int pop() {
		if (input.size() > 1) {
			while (input.size() != 1) {
				output.emplace(input.front());
				input.pop();
			}
		}
		int temp = input.front();
		input.pop();
		while (!output.empty()) {
			input.emplace(output.front());
			output.pop();
		}
		return temp;
	}

	int top() {
		if (input.size() > 1) {
			while (input.size() != 1) {
				output.emplace(input.front());
				input.pop();
			}
		}
		int temp = input.front();
		output.emplace(temp);
		input.pop();
		while (!output.empty()) {
			input.emplace(output.front());
			output.pop();
		}
		return temp;

	}

	bool empty() {
		return input.empty() && output.empty();
	}
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

// 我的解法2：时间 0 ms 100%，空间 6.6 MB 80.59%
class MyStack {
private:
	queue<int> input;
	queue<int> output;

	int in2out(bool pop) {
		int temp = 0;
		if (output.empty()) {
			if (input.size() > 1) {
				while (input.size() > 1) {
					output.emplace(input.front());
					input.pop();
				}
			}
			temp = input.front();
			if (!pop) output.emplace(temp);
			input.pop();
		}
		else {
			if (output.size() > 1) {
				while (output.size() > 1) {
					input.emplace(output.front());
					output.pop();
				}
			}
			temp = output.front();
			if (!pop) input.emplace(temp);
			output.pop();
		}
		return temp;
	}
public:
	MyStack() {}

	void push(int x) {
		if (output.empty()) input.emplace(x);
		else output.emplace(x);
	}

	int pop() {
		return in2out(true);
	}

	int top() {
		return in2out(false);
	}

	bool empty() {
		return input.empty() && output.empty();
	}
};

// 官方解法1：两个队列，时间 入栈O(n)，其余操作O(1) 100%，空间 O(n) 6.8 MB 11.58%
class MyStack {
private:
	queue<int> input;
	queue<int> output;
public:
	MyStack() {}

	void push(int x) {
		input.emplace(x);
		while (!output.empty()) {
			input.emplace(output.front());
			output.pop();
		}
		input.swap(output);
	}

	int pop() {
		int temp = output.front();
		output.pop();
		return temp;
	}

	int top() {
		return output.front();
	}

	bool empty() {
		return output.empty();
	}
};

// 官方解法二：一个队列，时间 入栈O(n)，其余操作O(1)，0 ms 100%，空间 O(n) 6.7 MB 36.19%
class MyStack {
private:
	queue<int> q;
public:
	MyStack() {}

	void push(int x) {
		int n = q.size();
		q.emplace(x);
		for (int i = 0; i < n; ++i) {
			q.emplace(q.front());
			q.pop();
		}
	}

	int pop() {
		int temp = q.front();
		q.pop();
		return temp;
	}

	int top() {
		return q.front();
	}

	bool empty() {
		return q.empty();
	}
};