#include<iostream>
#include<vector>

using std::vector;
using std::swap;

class priority_queue {
private:
	vector<int> heap;
public:
	// 获得最大值
	int top() {
		return heap[0];
	}

	// 插入任意值：把新的数字放在最后一位，然后上浮
	void push(int val) {
		heap.emplace_back(val);
		swim(heap.size() - 1);
	}

	// 删除最大值：把最后一个数字挪到开头，然后下沉，原最大值-开头数字被覆盖
	void pop() {
		heap[0] = heap.back();
		heap.pop_back();
		sink(0);
	}

	// 上浮
	void swim(int pos) {
		while (pos > 1 && heap[pos / 2] < heap[pos]) {
			swap(heap[pos / 2], heap[pos]);
			pos /= 2;
		}
	}

	// 下沉
	void sink(int pos) {
		const int n = heap.size();
		while (2 * pos < n) {
			int i = 2 * pos;
			if (i < n - 1 && heap[i] < heap[i + 1]) {
				++i;
			}
			if (heap[pos] >= heap[i]) break;
			swap(heap[pos], heap[i]);
			pos = i;
		}
	}
};