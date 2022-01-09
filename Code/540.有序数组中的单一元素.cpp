#include<iostream>
#include<vector>
using std::vector;

// �ҵĽⷨ������������ʱ��O(n) 24 ms 24.76%���ռ�O(1) 21.7 MB 46.85%
class Solution {
public:
	int singleNonDuplicate(vector<int>& nums) {
		for (size_t i = 0; i < nums.size() - 1; i += 2) {
			if (nums[i] != nums[i + 1]) {
				return nums[i];
			}
		}
		return nums.back();
	}
};

// �ҵĽⷨ�����ʱ��O(n) 24 ms 24.76%���ռ�O(1) 21.9 MB 5.41%
class Solution {
public:
	int singleNonDuplicate(vector<int>& nums) {
		int ret = 0;
		for (int num : nums) {
			ret ^= num;
		}
		return ret;
	}
};

// �ҵĽⷨ�����ֲ��ң�ʱ��O(log n) 20 ms 40%���ռ�O(1) 21.8 MB 19%
class Solution {
public:
	int singleNonDuplicate(vector<int>& nums) {
		int length = nums.size();
		int left = 0, right = length - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			int midVal = nums[mid];
			bool parity = mid & 1;
			if ((parity && midVal == nums[mid - 1]) || (mid < length - 1 && !parity && midVal == nums[mid + 1])) {
				left = mid + 1;
			}
			else {
				right = mid - 1;
			}
		}
		return nums[left];
	}
};


// �ٷ��ⷨ2������������ʱ��O(log n) 16 ms 47.53%���ռ�O(1) 21.9 MB 5.41%
// ���������Ƴ�һ��Ԫ�غ�ʣ�������������������
// ��ԭ����һ������������Ԫ�ص�������Ԫ�ظ�����Ϊ����������������Ԫ�ص��������Ϊż���������㷨��
// 1. ��low ��highָ��������β����Ԫ�أ�Ȼ����ж������������������ռ���룬ֱ���ҵ���һԪ�ػ��ʣһ��Ԫ��Ϊֹ���������ռ�ֻʣһ��Ԫ�أ���Ԫ�ؾ��Ǵ𰸡�
// 2. ��ÿ��ѭ�������У�ȷ��mid������halvesAreEven = (high-mid)%2 == 0��ͨ���鿴�м�Ԫ��ͬһԪ��Ϊ�������������һ��Ԫ�ػ����Ҳ�����ĵ�һ��Ԫ�أ�����ȷ��������һ��Ԫ�ظ���Ϊ������������low��high
// 3. ���ѵ��Ǹ���mid��halvesAreEven������low��high.
// 3.1 �м�Ԫ�ص�ͬһԪ�����ұߣ���midΪż����low = mid + 2
// 3.2 �м�Ԫ�ص�ͬһԪ�����ұߣ���midΪ������high = mid - 1
// 3.3 �м�Ԫ�ص�ͬһԪ������ߣ���midΪż����high = mid - 2
// 3.4 �м�Ԫ�ص�ͬһԪ������ߣ���midΪ������low = mid + 1
class Solution {
public:
	int singleNonDuplicate(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		while (low < high) {
			int mid = (low + high) >> 1;
			int midVal = nums[mid];
			// mid�Ƿ�Ϊż������Ϊ1����Ϊ0
			bool midIsEven = !(mid & 1);
			// �м�Ԫ�ص�ͬһԪ�����ұ�
			if (nums[mid + 1] == midVal) {
				if (midIsEven) {
					low = mid + 2;
				}
				else {
					high = mid - 1;
				}
			}
			// �м�Ԫ�ص�ͬһԪ�������
			else if (nums[mid - 1] == midVal) {
				if (midIsEven) {
					high = mid - 2;
				}
				else {
					low = mid + 1;
				}
			}
			else return midVal;
		}
		return nums[low];
	}
};


// �ٷ��ⷨ3������ż���������ж���������ʱ��O(log n/2)=O(log n) 20 ms 39.31%���ռ�O(1) 21.8 MB 33.51%
// �ڵ���Ԫ�صĺ��棬�ɶ�Ԫ�ر����������������ǵ�ͬһԪ��
// ˵�������ڼ�������Ԫ�غ����ż������ʱ�����û������ͬһԪ�ء�
class Solution {
public:
	int singleNonDuplicate(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		while (low < high) {
			int mid = (low + high) >> 1;
			if (mid & 1) --mid;
			if (nums[mid] == nums[mid + 1]) {
				low = mid + 2;
			}
			else {
				high = mid;
			}
		}
		return nums[low];
	}
};