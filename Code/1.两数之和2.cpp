#include<iostream>
#include<vector>
using namespace std;

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

int main(){
    vector<int> input = {0,4,3,0};
    vector<int> output;
    int target = 0;

    Solution s;
    output = s.twoSum(input, target);
    printf("input:");
    for (int i = 0; i < input.size(); i++)
    {
        printf("%d ", input[i]);
    }

	printf("\noutput:");
	for (int i = 0; i < output.size(); i++)
	{
		printf("%d ", output[i]);
	}
	printf("\n");

    system("pause");
    return 0;
}