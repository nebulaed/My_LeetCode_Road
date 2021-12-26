#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨһ����������鵽��0ɾȥ����β����ͬ������0��ʱ�� 92 ms���ռ� 18.8 MB
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		int count = 0;
		for (auto it = nums.begin(); it != nums.end();) {
			if (*it != 0) {
				++it;
				continue;
			}
			it = nums.erase(it);
			++count;
		}
		for (int i = 0; i < count; ++i) {
			nums.emplace_back(0);
		}
	}
};

// �ҵĽⷨ����˫ָ�뷨������0�����������ǰ�棬ʱ��O(n) 20 ms���ռ�O(1) 18.6 MB
// ptr0ָ����0������ptr1ָ�������
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		size_t ptr0 = 0, ptr1 = 0, length = nums.size();
		while (ptr1 < length && ptr0 < length) {
			while (ptr0 < length && nums[ptr0] != 0) {
				++ptr0;
			}
			while (ptr1 < length && nums[ptr1] == 0) {
				++ptr1;
			}
			if (ptr1 < length && ptr0 < length && ptr1 > ptr0) {
				swap(nums[ptr0], nums[ptr1]);
				++ptr0;
			}
			++ptr1;
		}
	}
};

// �ٷ��ⷨһ��˫ָ�룬ʱ��O(n) 20 ms���ռ�O(1) 18.7 MB
class Solution {
public:
	void moveZeroes(vector<int>& nums) {
		size_t length = nums.size(), left = 0, right = 0;
		while (right < length) {
			if (nums[right]) {
				swap(nums[left], nums[right]);
				++left;
			}
			++right;
		}
	}
};