#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// 二分查找不合并的思路
//class Solution {
//public:
//	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//		double ret = 0;
//		int parity = (nums1.size() + nums2.size()) % 2;
//		int k = (nums1.size() + nums2.size() + parity) / 2;
//		int exclusion = 0;
//		for (; k != 1 && !nums1.empty() && !nums2.empty(); k = k - exclusion) {
//			if (k / 2 > nums1.size()) {
//				exclusion = nums1.size();
//			}
//			else if (k / 2 > nums2.size()) {
//				exclusion = nums2.size();
//			}
//			else {
//				exclusion = k / 2;
//			}
//			if (nums1[exclusion - 1] <= nums2[exclusion - 1]) {
//				nums1.erase(nums1.begin(), nums1.begin() + exclusion);
//			}
//			else {
//				nums2.erase(nums2.begin(), nums2.begin() + exclusion);
//			}
//		}
//		if (nums1.empty()) {
//			ret = parity ? nums2[k - 1] : double(nums2[k - 1] + nums2[k]) / 2;
//		}
//		else if (nums2.empty()) {
//			ret = parity ? nums1[k - 1] : double(nums1[k - 1] + nums1[k]) / 2;
//		}
//		else {
//			if (parity) {
//				ret = nums1[0] < nums2[0] ? nums1[0] : nums2[0];
//			}
//			else {
//				if (nums1[0] < nums2[0] && nums1.size()>1) {
//					ret = nums1[1] < nums2[0] ? double(nums1[0] + nums1[1]) / 2 : double(nums1[0] + nums2[0]) / 2;
//				}
//				else if (nums2.size() > 1) {
//					ret = nums2[1] < nums1[0] ? double(nums2[0] + nums2[1]) / 2 : double(nums2[0] + nums1[0]) / 2;
//				}
//				else {
//					ret = double(nums1[0] + nums2[0]) / 2;
//				}
//			}
//		}
//		return ret;
//	}
//};

// 改进，不删除vector元素，只用偏移量记录，因为顺序存储结构删除是O(n)
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		double ret = 0;
		int parity = (nums1.size() + nums2.size()) % 2;
		int k = (nums1.size() + nums2.size() + parity) / 2;
		int exclusion1 = 0;
		int exclusion2 = 0;
		int offset1 = 0;
		int offset2 = 0;
		for (int exclusion = 0; k != 1 && offset1 != nums1.size() && offset2 != nums2.size(); k = k - exclusion) {
			exclusion1 = k / 2 > (nums1.size() - offset1) ? (nums1.size() - offset1) : k / 2;
			exclusion2 = k / 2 > (nums2.size() - offset2) ? (nums2.size() - offset2) : k / 2;
			if (nums1[offset1 + exclusion1 - 1] <= nums2[offset2 + exclusion2 - 1]) {
				offset1 += exclusion1;
				exclusion = exclusion1;
			}
			else {
				offset2 += exclusion2;
				exclusion = exclusion2;
			}
		}
		if (offset1 == nums1.size()) {
			ret = parity ? nums2[offset2 + k - 1] : (nums2[offset2 + k - 1] + nums2[offset2 + k]) / 2.0;
		}
		else if (offset2 == nums2.size()) {
			ret = parity ? nums1[offset1 + k - 1] : (nums1[offset1 + k - 1] + nums1[offset1 + k]) / 2.0;
		}
		else {
			if (parity) {
				ret = nums1[offset1] < nums2[offset2] ? nums1[offset1] : nums2[offset2];
			}
			else {
				if (nums1[offset1] < nums2[offset2] && (nums1.size() - offset1)>1) {
					ret = nums1[offset1 + 1] < nums2[offset2] ? (nums1[offset1] + nums1[offset1 + 1]) / 2.0 : (nums1[offset1] + nums2[offset2]) / 2.0;
				}
				else if ((nums2.size() - offset2) > 1) {
					ret = nums2[offset2 + 1] < nums1[offset1] ? (nums2[offset2] + nums2[offset2 + 1]) / 2.0 : (nums2[offset2] + nums1[offset1]) / 2.0;
				}
				else {
					ret = (nums1[offset1] + nums2[offset2]) / 2.0;
				}
			}
		}
		return ret;
	}
};

// 官方答案1
//class Solution {
//public:
//	int getKthElement(const vector<int>& nums1, const vector<int>& nums2, int k) {
//		int m = nums1.size();
//		int n = nums2.size();
//		int index1 = 0, index2 = 0;
//
//		while (true) {
//			if (index1 == m) {
//				return nums2[index2 + k - 1];
//			}
//			if (index2 == n) {
//				return nums1[index1 + k - 1];
//			}
//			if (k == 1) {
//				return min(nums1[index1], nums2[index2]);
//			}
//
//			int newIndex1 = min(index1 + k / 2 - 1, m - 1);
//			int newIndex2 = min(index2 + k / 2 - 1, n - 1);
//			int pivot1 = nums1[newIndex1];
//			int pivot2 = nums2[newIndex2];
//			if (pivot1 <= pivot2) {
//				k -= newIndex1 - index1 + 1;
//				index1 = newIndex1 + 1;
//			}
//			else {
//				k -= newIndex2 - index2 + 1;
//				index2 = newIndex2 + 1;
//			}
//		}
//	}
//	
//	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
//		int totalLength = nums1.size() + nums2.size();
//		if (totalLength % 2 == 1) {
//			return getKthElement(nums1, nums2, (totalLength + 1) / 2);
//		}
//		else {
//			return (getKthElement(nums1, nums2, totalLength / 2) + getKthElement(nums1, nums2, totalLength / 2 + 1)) / 2.0;
//		}
//	}
//};

// 官方答案2
class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		if (nums1.size() > nums2.size()) {
			return findMedianSortedArrays(nums2, nums1);
		}

		int m = nums1.size();
		int n = nums2.size();
		int left = 0, right = m;
		// median1: 前一部分的最大值
		// median2: 后一部分的最小值
		int median1 = 0, median2 = 0;

		while (left <= right) {
			int i = (left + right) / 2;
			int j = (m + n + 1) / 2 - i;

			int nums_im1 = (i == 0 ? INT_MIN : nums1[i - 1]);
			int nums_i = (i == m ? INT_MAX : nums1[i]);
			int nums_jm1 = (j == 0 ? INT_MIN : nums2[j - 1]);
			int nums_j = (j == n ? INT_MAX : nums2[j]);

			if (nums_im1 <= nums_j) {
				median1 = max(nums_im1, nums_jm1);
				median2 = min(nums_i, nums_j);
				left = i + 1;
			}
			else {
				right = i - 1;
			}
		}
		return (m + n) % 2 == 0 ? (median1 + median2) / 2.0 : median1;
	}
};

int main() {
	vector<int>nums1 = { 1 };
	vector<int>nums2 = { 2,3,4,5,6 };
	Solution s;
	double ret = s.findMedianSortedArrays(nums1, nums2);

	cout << ret << endl;

	system("pause");
	return 0;
}