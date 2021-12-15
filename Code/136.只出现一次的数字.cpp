#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<numeric>
using namespace std;

// �ҵĽⷨ����ϣ��ʱ�� O(n) 32 ms���ռ� O(n) 22.6 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_multiset<int> numSet(nums.begin(), nums.end());
		for (const auto& num : numSet) {
			if (numSet.count(num) == 1) {
				return num;
			}
		}
		return 0;
	}
};

// �ҵĽⷨ�ο��ٽ�˼·һ��ʹ�ü��ϴ洢���֣�ʱ��O(n) 24 ms���ռ�O(n) 19.5 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		unordered_set<int> numSet;
		for (const auto& num : nums) {
			if (numSet.count(num)) {
				numSet.erase(num);
			}
			else {
				numSet.emplace(num);
			}
		}
		return *numSet.begin();
	}
};

// �ҵĽⷨ�ο��ٽ�˼·����ʹ�ü��ϴ洢�������������֣������㼯�ϵ�Ԫ��֮�ͳ���2��ȥ�����Ԫ��֮�ͣ�ʱ��O(n) 32 ms���ռ�O(n) 20.2 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		set<int> numSet(nums.begin(),nums.end());
		return 2 * accumulate(numSet.begin(), numSet.end(), 0) - accumulate(nums.begin(), nums.end(), 0);
	}
};

// �ٷ��ⷨһ��λ����(���)��ʱ�� O(n) 20 ms���ռ� O(1) 16.4 MB
class Solution {
public:
	int singleNumber(vector<int>& nums) {
		int ret = 0;
		for (const auto& num : nums) ret ^= num;
		return ret;
	}
};

int main() {

	vector<int> nums = { 4,1,2,1,2 };

	Solution s;
	int ret = s.singleNumber(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}