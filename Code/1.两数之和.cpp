#include<iostream>
#include<vector>
#include<algorithm>
#include<unordered_map>
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

// 我的解法：自建哈希表
//-----------------------------------------------------------------
typedef struct HashNode {
	int key;
	bool status;
}HashNode;

class HashTable {
public:
	HashTable(int HASHSIZE)
	{
		m = HASHSIZE;
		this->count = m;
		this->elem = (HashNode*)malloc(m * sizeof(HashNode));
		for (int i = 0; i < m; i++)
		{
			this->elem[i].key = 0;
			this->elem[i].status = false;
		}
	}
	int Hash(int key)
	{
		// 解决了直接用key%m可能返回负值的问题
		key += (abs(key) / m + 1) * m;
		return key % m;
	}
	void InsertHash(int key)
	{
		int addr = Hash(key);
		while (this->elem[addr].status)
		{
			addr = (addr + 1) % m;
		}
		this->elem[addr].key = key;
		this->elem[addr].status = true;
	}
	bool SearchHash(int key)
	{
		int addr;
		addr = Hash(key);
		while (this->elem[addr].key != key)
		{
			addr = (addr + 1) % m;
			if (!this->elem[addr].status || addr == Hash(key))
			{
				return false;
			}
		}
		if (this->elem[addr].status) {
			return true;
		}
		else {
			return false;
		}
	}
	HashNode* elem;
	int count;
	int m;
};

class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> result = {};
		int ret1 = -1;
		int ret2 = -1;
		HashTable H(nums.size());
		for (vector<int>::iterator it1 = nums.begin(); it1 != nums.end(); it1++) {
			if (!H.SearchHash(target - *it1)) {
				H.InsertHash(*it1);
			}
			else {
				ret1 = target - *it1;
				ret2 = int(it1 - nums.begin());
				break;
			}
		}
		for (vector<int>::iterator it2 = nums.begin(); it2 != nums.end(); it2++) {
			if (*it2 == ret1)
			{
				ret1 = int(it2 - nums.begin());
				break;
			}
		}
		result = { ret1,ret2 };
		return result;
	}
};
//-----------------------------------------------------------------


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

// 我的第二次解法：哈希表，时间 4 ms 99.39%，空间 10.5 MB 43.70%
class Solution {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		unordered_map<int, int> record;
		int n = nums.size();
		for (int i = 0; i < n; ++i) {
			auto it = record.find(target - nums[i]);
			if (it != record.end()) {
				return { it->second, i };
			}
			else {
				record.emplace(nums[i], i);
			}
		}
		return {};
	}
};

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

//int main() {
//	vector<int> input = { 0,4,3,0 };
//	vector<int> output;
//	int target = 0;
//
//	Solution s;
//	output = s.twoSum(input, target);
//	printf("input:");
//	for (int i = 0; i < input.size(); i++)
//	{
//		printf("%d ", input[i]);
//	}
//
//	printf("\noutput:");
//	for (int i = 0; i < output.size(); i++)
//	{
//		printf("%d ", output[i]);
//	}
//	printf("\n");
//
//	system("pause");
//	return 0;
//}

//int main() {
//	vector<int> nums = { 0,2,3,4 };
//	int target = 6;
//
//	Solution s;
//	cout << "[ ";
//	vector<int> ret = s.twoSum(nums, target);
//
//	for (int i = 0; i < ret.size(); ++i) {
//		cout << ret[i] << " ";
//	}
//	cout << ']' << endl;
//
//	system("pause");
//	return 0;
//}