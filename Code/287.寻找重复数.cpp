#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ��ʱ��O(n logn) 124 ms���ռ�O(1) 59.8 MB
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		for (size_t i = 1; i < nums.size(); ++i) {
			if (nums[i] == nums[i - 1]) {
				return nums[i];
			}
		}
		return 0;
	}
};

// �ٷ����һ�����ֲ��ң�ʱ��O(n logn) 92 ms���ռ�O(1) 59.8 MB
// �ٶ��ظ���Ϊtarget����ô[1, target-1]��������������С�ڵ���i����cnt[i]<=i��[target,n]�������������cnt[i]>i�����е�����
// ��˿�����[1,n]��ʹ�ö��ֲ���
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		size_t n = nums.size();
		size_t left = 1, right = n - 1, ret = -1;
		while (left <= right) {
			size_t mid = (left + right) >> 1;
			int cnt = 0;
			for (size_t i = 0; i < n; ++i) {
				cnt += (nums[i] <= mid);
			}
			if (cnt <= mid) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
				ret = mid;
			}
		}
		return ret;
	}
};

// �ٷ������������ƣ�ʱ��O(n log n) 176 ms���ռ�O(1) 59.8 MB
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int n = nums.size(), ret = 0;
		// ȷ�������������λ�Ƕ���
		int bit_max = 31;
		while (!((n - 1) >> bit_max)) {
			bit_max -= 1;
		}
		for (int bit = 0; bit <= bit_max; ++bit) {
			int x = 0, y = 0;
			for (int i = 0; i < n; ++i) {
				if (nums[i] & 1 << bit) {
					x += 1;
				}
				if (i >= 1 && (i & (1 << bit))) {
					y += 1;
				}
			}
			if (x > y) {
				ret |= 1 << bit;
			}
		}
		return ret;
	}
};

// �ٷ������������ָ�룬ʱ��O(n) 84 ms���ռ�O(1) 59.8 MB
// �������ƻ��������е�Floyd��Ȧ�㷨
// ˼·����nums���齨ͼ��ÿ��λ��i����һ��i->nums[i]�ıߣ����ڴ����ظ�����target�����target���λ��һ������������ָ�����ıߣ��������ͼһ�����ڻ���
// ���ÿ�ָ�����ָ�룬��ָ��ÿ����һ������ָ��ÿ�����������������ٽ�slow�ŵ���㣬����ָ��ÿ��ͬʱ�ƶ�һ���������ĵ���Ǵ𰸡�
class Solution {
public:
	int findDuplicate(vector<int>& nums) {
		int slow = 0, fast = 0;
		do {
			slow = nums[slow];
			fast = nums[nums[fast]];
		} while (slow != fast);
		slow = 0;
		while (slow != fast) {
			slow = nums[slow];
			fast = nums[fast];
		}
		return slow;
	}
};