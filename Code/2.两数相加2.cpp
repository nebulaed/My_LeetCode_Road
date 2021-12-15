#include<iostream>
#include<vector>
#include<unordered_map>
using namespace std;

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> hashtable; // ��ϣ����������map
		for (int i = 0; i < nums.size(); i++) {
			unordered_map<int, int>::iterator it = hashtable.find(target - nums[i]); // ���� target - nums[i]���ҵ�Ϊ���ڵĵ��������Ҳ���Ϊĩβ������
			if (it != hashtable.end()) {
				return { it->second, i };
			}
			hashtable.insert(pair<int, int>(nums[i], i)); // ��δ�ҵ�����뵱ǰnums[i]
		}
		return {}; // δ�ҵ��򷵻ؿ�
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