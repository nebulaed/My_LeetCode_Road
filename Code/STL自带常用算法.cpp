#include<algorithm>
#include<vector>
using namespace std;

int main() {

	vector<int> iter, iter1, iter2, dest, content, sub;
	int value, cnt, nth, mid, init, lo, hi;


	// <algorithm>
	pos = find(iter.begin(), iter.end(), value) - iter.begin(); // 找元素
	pos = search(content.begin(), content.end(), sub.begin(), sub.end()) - content.begin(); // 找子串
	fill(iter.begin(), iter.end(), value); // 填充
	reverse(iter.begin(), iter.end()); // 反转元素
	rotate(iter.begin(), iter.begin() + cnt, iter.end()); // 轮转 cnt 位：1 2 3 => 2 3 1 (1 位)
	unique(iter.begin(), iter.end()); // 连续元素去重
	bool fun(value) {}
	partition(iter.begin(), iter.end(), fun); // 分组（轴点），快排基础，返回值为第二组开始点
	partition_point(iter.begin(), iter.end(), fun); // 返回轴点位置
	sort(iter.begin(), iter.end()); // 排序，从小到大
	sort(iter.begin(), iter.end(), bool_fun); // 排序，自定义，true => 在前
	partial_sort(iter.begin(), iter.begin() + cnt, iter.end()); // 部分排序，全部的前 n 小排序好，如 0 1 2 7 8 6 5 9 4 3
	nth_element(iter.begin(), iter.begin() + nth, iter.end()); // 将有序的第 n 个放到对应位置，且前面都小于等于，后面都大于等于，但不保证有序，适用于第K大数
	lower_bound(iter.begin(), iter.end(), value); // 不小于 value 的第一个值位置
	upper_bound(iter.begin(), iter.end(), value); // 大于 value 的第一个位置
	binary_search(iter.begin(), iter.end(), value); // 二叉搜索元素是否存在
	merge(iter1.begin(), iter1.end(), iter2.begin(), iter2.end(), dest.begin()); // 合并有序的两个迭代器
	inplace_merge(iter.begin(), iter.begin() + mid, iter.end()); // 将前后有序的两部分合并，适用于写分治算法的时候
	includes set_difference set_intersection set_symmertric_difference set_union; // 集合用函数
	is_heap(iter.begin(), iter.end()); // 判断是否是大根堆
	make_heap(iter.begin(), iter.end()); // 大根堆化
	push_heap(iter.begin(), iter.end()); // 将末尾元素放入前 n - 1 个元素构成的堆
	pop_heap(iter.begin(), iter.end()); // 将堆顶放到末尾
	sort_heap(iter.begin(), iter.end()); // 将大根堆转为升序排列
	max_element(iter.begin(), iter.end()); // argmax
	min_element(iter.begin(), iter.end()); // argmin
	minmax_element(iter.begin(), iter.end()); // 同时返回 min max 的位置
	clamp(value, lo, hi); // C++17 限制在 [lo, hi] 内
	next_permutation(iter.begin(), iter.end()); // 返回下一个排序，“排序”间以字典序比较大小，字典序最大时返回 false
	prev_permutation(iter.begin(), iter.end()); // 与前者相反，返回字典序更小的下一个
	accumulate(iter.begin(), iter.end(), init, binary_op); // 对迭代器做聚合操作，默认 add => sum
	partial_sum(iter.begin(), iter.end(), dest.begin()); // 求前缀和，可以类似前者换函数做其他聚合操作
	iter.erase(unique(iter.begin(), iter.end()), iter.end()); // 去重小技巧
	stable_sort;
}

// std::shuffle用法
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