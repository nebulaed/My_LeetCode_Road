#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable; // 哈希函数构建的map
		for (int i = 0; i < nums.size(); i++) {
			unordered_map<int, int>::iterator it = hashtable.find(target - nums[i]); // 查找 target - nums[i]，找到为所在的迭代器，找不到为末尾迭代器
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable.insert(pair<int, int>(nums[i], i)); // 若未找到则插入当前nums[i]
		}
		return {}; // 未找到则返回空
	}
};

int main() {
	vector<int> input = { 0,4,3,0 };
	vector<int> output;
	int target = 0;

	Solution s;
	output = s.twoSum(input, target);

	for (int i = 0; i < output.size(); i++) {
		printf("%d ", output[i]);
	}
	printf("\n");

	system("pause");
	return 0;
}