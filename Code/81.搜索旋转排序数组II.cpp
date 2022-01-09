#include<iostream>
#include<vector>
using std::vector;

// �ҵĽⷨ�����ֲ��ң�ʱ��O(log n) 4 ms 87.24%���ռ�O(1) 13.5 MB 88.74%
class Solution {
public:
	bool search(vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (nums[mid] == target) return true;
			// �е����˵�������ͬ���޷�ȷ����������ȫ����ͬ����������ȫ����ͬ��0 1 2 0 0 0 0Ҳ������3 3 3 3 0 1 2
			// ����޷��ж��ĸ������������
			// ��ˣ����Լ򵥵ذ���˵�����һλ��Ȼ��������ֲ���
			else if (nums[left] == nums[mid]) {
				++left;
			}
			// ������Ϊ����
			else if (nums[mid] <= nums[right]) {
				if (target > nums[mid] && target <= nums[right]) {
					left = mid + 1;
				}
				else {
					right = mid - 1;
				}
			}
			// ������Ϊ����
			else {
				if (target >= nums[left] && target < nums[mid]) {
					right = mid - 1;
				}
				else {
					left = mid + 1;
				}
			}
		}
		return false;
	}
};

// �ҵĽⷨ��ʱ�� 4 ms���ռ� 13.7 MB
class Solution {
public:
	bool search(vector<int>& nums, int target) {
		for (int num : nums) {
			if (num == target) {
				return true;
			}
		}
		return false;
	}
};