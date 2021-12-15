#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> result = {};
		for (vector<int>::iterator it1 = nums.begin(); it1 != nums.end(); it1++) {
			for (vector<int>::iterator it2 = it1 + 1; it2 != nums.end(); it2++) {
				if (*it1 + *it2 == target) {
					result = { int(it1 - nums.begin()),int(it2 - nums.begin()) };
					return result;
				}
			}
		}
		return result;
	}
};

void myprint(int val)
{
	cout << val << " ";
}

int main()
{
	vector<int>nums = { 2,7,11,15 };
	int target = 26;

	Solution s;
	vector<int> result = s.twoSum(nums, target);
	for_each(result.begin(), result.end(), myprint);
	cout << endl;
	
	system("pause");
	return 0;
}