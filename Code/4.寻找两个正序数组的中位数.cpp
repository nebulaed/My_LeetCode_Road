#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

void printint(int val)
{
	cout << val << " ";
}

class Solution {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		double ret;
		vector<int>vTarget;
		vTarget.resize(nums1.size() + nums2.size());
		merge(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), vTarget.begin());
		if (vTarget.size() % 2 == 0)
		{
			ret = (vTarget[vTarget.size() / 2] + vTarget[vTarget.size() / 2-1])/2.0;
			cout << ret << endl;
		}
		else
		{
			ret = vTarget[vTarget.size() / 2];
		}
		return ret;
	}
};

int main()
{
	vector<int> v1 = { 1,2 };
	vector<int> v2 = { 3,4 };
	for_each(v1.begin(), v1.end(), printint);
	cout << endl;
	for_each(v2.begin(), v2.end(), printint);
	cout << endl;

	Solution s;
	double ret = s.findMedianSortedArrays(v1, v2);
	cout << "中位数为：" << ret << endl;
	system("pause");
	return 0;
}