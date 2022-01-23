#include<algorithm>
#include<vector>
using namespace std;

int main() {

	vector<int> iter, iter1, iter2, dest, content, sub;
	int value, cnt, nth, mid, init, lo, hi;


	// <algorithm>
	pos = find(iter.begin(), iter.end(), value) - iter.begin(); // ��Ԫ��
	pos = search(content.begin(), content.end(), sub.begin(), sub.end()) - content.begin(); // ���Ӵ�
	fill(iter.begin(), iter.end(), value); // ���
	reverse(iter.begin(), iter.end()); // ��תԪ��
	rotate(iter.begin(), iter.begin() + cnt, iter.end()); // ��ת cnt λ��1 2 3 => 2 3 1 (1 λ)
	unique(iter.begin(), iter.end()); // ����Ԫ��ȥ��
	bool fun(value) {}
	partition(iter.begin(), iter.end(), fun); // ���飨��㣩�����Ż���������ֵΪ�ڶ��鿪ʼ��
	partition_point(iter.begin(), iter.end(), fun); // �������λ��
	sort(iter.begin(), iter.end()); // ���򣬴�С����
	sort(iter.begin(), iter.end(), bool_fun); // �����Զ��壬true => ��ǰ
	partial_sort(iter.begin(), iter.begin() + cnt, iter.end()); // ��������ȫ����ǰ n С����ã��� 0 1 2 7 8 6 5 9 4 3
	nth_element(iter.begin(), iter.begin() + nth, iter.end()); // ������ĵ� n ���ŵ���Ӧλ�ã���ǰ�涼С�ڵ��ڣ����涼���ڵ��ڣ�������֤���������ڵ�K����
	lower_bound(iter.begin(), iter.end(), value); // ��С�� value �ĵ�һ��ֵλ��
	upper_bound(iter.begin(), iter.end(), value); // ���� value �ĵ�һ��λ��
	binary_search(iter.begin(), iter.end(), value); // ��������Ԫ���Ƿ����
	merge(iter1.begin(), iter1.end(), iter2.begin(), iter2.end(), dest.begin()); // �ϲ����������������
	inplace_merge(iter.begin(), iter.begin() + mid, iter.end()); // ��ǰ������������ֺϲ���������д�����㷨��ʱ��
	includes set_difference set_intersection set_symmertric_difference set_union; // �����ú���
	is_heap(iter.begin(), iter.end()); // �ж��Ƿ��Ǵ����
	make_heap(iter.begin(), iter.end()); // ����ѻ�
	push_heap(iter.begin(), iter.end()); // ��ĩβԪ�ط���ǰ n - 1 ��Ԫ�ع��ɵĶ�
	pop_heap(iter.begin(), iter.end()); // ���Ѷ��ŵ�ĩβ
	sort_heap(iter.begin(), iter.end()); // �������תΪ��������
	max_element(iter.begin(), iter.end()); // argmax
	min_element(iter.begin(), iter.end()); // argmin
	minmax_element(iter.begin(), iter.end()); // ͬʱ���� min max ��λ��
	clamp(value, lo, hi); // C++17 ������ [lo, hi] ��
	next_permutation(iter.begin(), iter.end()); // ������һ�����򣬡����򡱼����ֵ���Ƚϴ�С���ֵ������ʱ���� false
	prev_permutation(iter.begin(), iter.end()); // ��ǰ���෴�������ֵ����С����һ��
	accumulate(iter.begin(), iter.end(), init, binary_op); // �Ե��������ۺϲ�����Ĭ�� add => sum
	partial_sum(iter.begin(), iter.end(), dest.begin()); // ��ǰ׺�ͣ���������ǰ�߻������������ۺϲ���
	iter.erase(unique(iter.begin(), iter.end()), iter.end()); // ȥ��С����
	stable_sort;
}

// std::shuffle�÷�
#include <iostream>
#include <random>
#include <algorithm>

int main()
{
	std::vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	std::cout << "before shuffle:\t";
	for (int n : v) {
		std::cout << n << "   ";
	}
	std::cout << std::endl;

	std::random_device rd;
	std::mt19937 rng(rd());

	std::shuffle(v.begin(), v.end(), rng);

	std::cout << "after shuffle: \t";
	for (int n : v) {
		std::cout << n << "   ";
	}
	std::cout << std::endl;

	return 0;
}