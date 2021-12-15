#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable;
		for (int i = 0; i < nums.size(); i++) {
			unordered_map<int, int>::iterator it = hashtable.find(target - nums[i]);
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable.insert(pair<int, int>(nums[i], i));
		}
		return {};
	}
};

int main() {
	vector<int> nums = { 0,2,3,4 };
	int target = 6;

	Solution s;
	cout << "[ ";
	vector<int> ret = s.twoSum(nums, target);

	for (int i = 0; i < ret.size(); ++i) {
		cout << ret[i] << " ";
	}
	cout << ']' << endl;

	system("pause");
	return 0;
}