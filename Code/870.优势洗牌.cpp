#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<numeric>

using namespace std;

// 我的解法：红黑树多重集合，时间 208 ms 16.71%，空间 73.9 MB 10.77%
class Solution {
public:
	vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
		//索引数组
		vector<size_t> idx(nums2.size());
		//将0...n赋值给索引数组
		iota(idx.begin(), idx.end(), 0);
		//根据nums2元素从小到大对索引数组进行排序
		sort(idx.begin(), idx.end(), [&nums2](size_t lhs, size_t rhs) {
			return nums2[lhs] < nums2[rhs];
			});
		//红黑树集合，查找，删除均为log n
		multiset<int> numSet1(nums1.begin(), nums1.end());
		for (int i : idx) {
			auto it = numSet1.upper_bound(nums2[i]);
			if (it != numSet1.end()) {
				nums1[i] = *it;
			}
			else {
				it = numSet1.begin();
				nums1[i] = *it;
			}
			numSet1.erase(it);
		}
		return nums1;
	}
};

// 官方解法：田忌赛马，时间 136 ms 57.79%，空间 58.3 MB 90.23%
// 对比于上面采用红黑树多重集合，避免了每次使用二分查找
class Solution {
public:
	vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());

		size_t n = nums2.size();
		//最好不要使用这种用别的数组排序本数组的方法，用pair效率更高，虽然空间占用更大
		vector<size_t> idx(n);
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&nums2](size_t lhs, size_t rhs) {
			return nums2[lhs] < nums2[rhs];
			});
		vector<int> ret(n, -1);
		size_t id1 = n - 1, id2 = n - 1;
		while (id1 != -1 && id2 != -1) {
			int originalID2 = idx[id2];
			//当nums1当前位置的值能击败nums2当前位置的值时
			if (nums1[id1] > nums2[originalID2]) {
				//将结果数组对应位置设置为能击败nums2的该值，并让id1自减1
				ret[originalID2] = nums1[id1--];
			}
			//无论比不比得过id2都应自减1
			--id2;
		}
		//若id1不为-1，说明结果数组还有一些位置未填充
		if (id1 != -1) {
			for (int& num : ret) {
				if (num == -1) {
					num = nums1[id1--];
				}
			}
		}
		return ret;
	}
};

// 官方解法改进：田忌赛马，时间 116 ms 85.55%，空间 60 MB 78.33%(使用pool_alloc可减少为59.9 MB 78.62%)
// 不采用索引数组根据原数组排序，而是直接构建vector<pair<int, size_t>>，根据first排序，效率更高，且避免后面while循环需要两次operator[]
class Solution {
public:
	vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());

		size_t n = nums2.size();
		vector<pair<int, size_t>> val_idx(n);
		size_t i = 0;
		for (auto& [val, id] : val_idx) {
			val = nums2[i];
			id = i++;
		}
		sort(val_idx.begin(), val_idx.end(), [](const pair<int, int>& lhs, const pair<int, int>& rhs) {
			return lhs.first < rhs.first;
			});
		vector<int> ret(n, -1);
		size_t id1 = n - 1, id2 = n - 1;
		while (id1 != -1 && id2 != -1) {
			if (nums1[id1] > val_idx[id2].first) {
				ret[val_idx[id2].second] = nums1[id1--];
			}
			--id2;
		}
		if (id1 != -1) {
			for (int& num : ret) {
				if (num == -1) {
					num = nums1[id1--];
				}
			}
		}
		return ret;
	}
};