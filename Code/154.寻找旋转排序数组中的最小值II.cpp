#include<iostream>
#include<vector>
#include<algorithm>
using std::vector;
using std::min;

// �ҵĽⷨ������������ʱ�� O(n) 8 ms 42.89%���ռ� O(1) 12 MB 23.84%
class Solution {
public:
	int findMin(vector<int>& nums) {
		int minVal = 1e5;
		for (int num : nums) {
			minVal = min(minVal, num);
		}
		return minVal;
	}
};

// �ҵĽⷨ�����ֲ��ң�ʱ�� ƽ��O(log n)���O(n) 4 ms 87.02%���ռ� O(1) 12 MB 18.62%
class Solution {
public:
	int findMin(vector<int>& nums) {
		int left = 0, right = nums.size() - 1, minVal = 1e4;
		while (left <= right) {
			int mid = (left + right) >> 1, midVal = nums[mid];
			if (nums[left] == midVal) {
				minVal = min(minVal, midVal);
				++left;
			}
			// ������Ϊ����
			else if (midVal <= nums[right]) {
				minVal = min(minVal, midVal);
				right = mid - 1;
			}
			// ������Ϊ����
			else {
				minVal = min(minVal, nums[left]);
				left = mid + 1;
			}
		}
		return minVal;
	}
};

// �ٷ��ⷨ�����ֲ��ң�ʱ�� ƽ��O(log n)���O(n) 0 ms 100%���ռ�O(1) 11.9 MB 86.26%
// ���ǿ�����ת���������е����һ��Ԫ��x������Сֵ�Ҳ��Ԫ�أ�ֵһ��С�ڵ���x������Сֵ����Ԫ�أ�ֵһ�����ڵ���x��
// �����������ʣ�ͨ�����ֲ��ҵķ����ҳ���Сֵ
// ���ֲ��ҵ�ÿһ���У���Сֵ����low��high֮�䣬�е�Ϊpivot��
// ���е�Ԫ��nums[pivot]���ұ߽�Ԫ��nums[high]���бȽϣ��������������������
// 1. nums[pivot]<nums[high]������ͼ��ʾ��˵��nums[pivot]����Сֵ�Ҳ�Ԫ�أ����Ժ���pivot��high����Ҳ����䡣
// 2. nums[pivot]>nums[high]��˵��nums[pivot]����Сֵ���Ԫ�أ�����low��pivot֮���������䡣
// 3. nums[pivot]=nums[high]������ȷ��nums[pivot]����Сֵ��໹���Ҳࡣ��3 4 0 1 1 1 1��3 3 3 3 0 1 3��ֻ��ȷ��һ������nums[high]��ȵ�Ԫ�أ�ֻ�ܺ���high
class Solution {
public:
	int findMin(vector<int>& nums) {
		int low = 0, high = nums.size() - 1;
		while (low < high) {
			int pivot = (low + high) >> 1;
			int pivotVal = nums[pivot], highVal = nums[high];
			if (pivotVal < highVal) {
				high = pivot;
			}
			else if (pivotVal > highVal) {
				low = pivot + 1;
			}
			else --high;
		}
		return nums[low];
	}
};