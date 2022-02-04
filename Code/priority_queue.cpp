#include<iostream>
#include<vector>

using std::vector;
using std::swap;

class priority_queue {
private:
	vector<int> heap;
public:
	// ������ֵ
	int top() {
		return heap[0];
	}

	// ��������ֵ�����µ����ַ������һλ��Ȼ���ϸ�
	void push(int val) {
		heap.emplace_back(val);
		swim(heap.size() - 1);
	}

	// ɾ�����ֵ�������һ������Ų����ͷ��Ȼ���³���ԭ���ֵ-��ͷ���ֱ�����
	void pop() {
		heap[0] = heap.back();
		heap.pop_back();
		sink(0);
	}

	// �ϸ�
	void swim(int pos) {
		while (pos > 1 && heap[pos / 2] < heap[pos]) {
			swap(heap[pos / 2], heap[pos]);
			pos /= 2;
		}
	}

	// �³�
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