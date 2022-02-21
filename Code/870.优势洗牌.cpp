#include<iostream>
#include<vector>
#include<set>
#include<algorithm>
#include<numeric>

using namespace std;

// �ҵĽⷨ����������ؼ��ϣ�ʱ�� 208 ms 16.71%���ռ� 73.9 MB 10.77%
class Solution {
public:
	vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
		//��������
		vector<size_t> idx(nums2.size());
		//��0...n��ֵ����������
		iota(idx.begin(), idx.end(), 0);
		//����nums2Ԫ�ش�С��������������������
		sort(idx.begin(), idx.end(), [&nums2](size_t lhs, size_t rhs) {
			return nums2[lhs] < nums2[rhs];
			});
		//��������ϣ����ң�ɾ����Ϊlog n
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

// �ٷ��ⷨ���������ʱ�� 136 ms 57.79%���ռ� 58.3 MB 90.23%
// �Ա���������ú�������ؼ��ϣ�������ÿ��ʹ�ö��ֲ���
class Solution {
public:
	vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2) {
		sort(nums1.begin(), nums1.end());

		size_t n = nums2.size();
		//��ò�Ҫʹ�������ñ��������������ķ�������pairЧ�ʸ��ߣ���Ȼ�ռ�ռ�ø���
		vector<size_t> idx(n);
		iota(idx.begin(), idx.end(), 0);
		sort(idx.begin(), idx.end(), [&nums2](size_t lhs, size_t rhs) {
			return nums2[lhs] < nums2[rhs];
			});
		vector<int> ret(n, -1);
		size_t id1 = n - 1, id2 = n - 1;
		while (id1 != -1 && id2 != -1) {
			int originalID2 = idx[id2];
			//��nums1��ǰλ�õ�ֵ�ܻ���nums2��ǰλ�õ�ֵʱ
			if (nums1[id1] > nums2[originalID2]) {
				//����������Ӧλ������Ϊ�ܻ���nums2�ĸ�ֵ������id1�Լ�1
				ret[originalID2] = nums1[id1--];
			}
			//���۱Ȳ��ȵù�id2��Ӧ�Լ�1
			--id2;
		}
		//��id1��Ϊ-1��˵��������黹��һЩλ��δ���
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

// �ٷ��ⷨ�Ľ����������ʱ�� 116 ms 85.55%���ռ� 60 MB 78.33%(ʹ��pool_alloc�ɼ���Ϊ59.9 MB 78.62%)
// �����������������ԭ�������򣬶���ֱ�ӹ���vector<pair<int, size_t>>������first����Ч�ʸ��ߣ��ұ������whileѭ����Ҫ����operator[]
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