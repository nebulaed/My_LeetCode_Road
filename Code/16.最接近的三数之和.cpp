#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// ��������
//class Solution {
//public:
//	int threeSumClosest(vector<int>& nums, int target) {
//		int n = nums.size();
//		sort(nums.begin(), nums.end());
//		int deviation = INT_MAX;
//		// ö��(a,b,c)�е�a
//		for (int first = 0; first < n; ++first) {
//			// ö�ٵ�a�������ϸ�ö�ٵ�a��ֵ����
//			if (first > 0 && nums[first] == nums[first - 1]) {
//				continue;
//			}
//			// c��Ӧ��ָ���ʼָ����������Ҷ�
//			int third = n - 1;
//			int cur_target = target - nums[first];
//			// ö��b
//			for (int second = first + 1; second < n && second != third; ++second) {
//				// ͬ��Ҫ��֤ö�ٵ�b�������ϸ�ö�ٵ�b��ֵ����
//				if (second > first + 1 && nums[second] == nums[second - 1]) {
//					continue;
//				}
//				// ��Ҫ��֤b��ָ����c��ָ�����
//				while (second<third-1 && abs(cur_target - nums[second] - nums[third-1])<= abs(cur_target - nums[second] - nums[third])) {
//					--third;
//				}
//				if (abs(cur_target - nums[second] - nums[third]) < abs(deviation)) {
//					deviation = cur_target - nums[second] - nums[third];
//				}
//			}
//		}
//		return target - deviation;
//	}
//};

// �ٷ����1������ + ˫ָ��
class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int n = nums.size();
		sort(nums.begin(), nums.end());
		int deviation = INT_MAX;
		// ö��(a,b,c)�е�a
		for (int first = 0; first < n; ++first) {
			// ö�ٵ�a�������ϸ�ö�ٵ�a��ֵ����
			if (first > 0 && nums[first] == nums[first - 1]) {
				continue;
			}
			// b��Ӧ��ָ���ʼָ��a+1��c��Ӧ��ָ���ʼָ����������Ҷ�
			int third = n - 1;
			int second = first + 1;
			// ʹ��˫ָ��ö��b��c
			while (second < third) {
				if (abs(target - nums[first] - nums[second] - nums[third]) < abs(deviation)) {
					// ���¾���ֵ��С��deviation
					deviation = target - nums[first] - nums[second] - nums[third];
					// ����ǰ�͵���targetֱ�ӷ��ش�
					if (!deviation) return target;
				}
				// ���ʹ���target�������ƶ�c
				if (nums[first] + nums[second] + nums[third] >= target) {
					--third;
					// ��c��c+1��ȣ���c�ٴ������ƶ�
					while (second < third && nums[third] == nums[third + 1]) {
						--third;
					}
				}
				// ����С��target�������ƶ�b
				else {
					++second;
					// ��b��b-1��ȣ���b�ٴ������ƶ�
					while (second < third && nums[second] == nums[second - 1]) {
						++second;
					}
				}
			}
		}
		return target - deviation;
	}
};


int main() {
	vector<int> nums = { 1,1,-1,-1,3 };
	int target = -1;

	Solution s;
	int ret = s.threeSumClosest(nums,target);

	cout << ret << endl;
	system("pause");
	return 0;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
}