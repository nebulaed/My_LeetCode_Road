#include<iostream>
#include<vector>
#include<unordered_set>

using std::vector;
using std::unordered_set;

// �ҵĽⷨһ����ϣ���ϣ�ʱ�� O(n) 12 ms 33.51%���ռ� O(n) 10.4 MB 31.63%
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		unordered_set<int> numSet;
		for (int num : nums) {
			if (numSet.count(num)) {
				numSet.erase(num);
			}
			else {
				numSet.emplace(num);
			}
		}
		auto it = numSet.begin();
		return { *it, *++it };
	}
};

// �ҵĽⷨ����λ���㣬ʱ�� O(n) 4 ms 98.50%���ռ� O(1) 9.7 MB 72.72%
// ԭ��������ֻ����һ�ε����ֱ�Ϊx1��x2
class Solution {
public:
	vector<int> singleNumber(vector<int>& nums) {
		int mask = 0;
		for (int num : nums) {
			mask ^= num;
		}
		// ��ʱmask = x1 ^ x2
		// ע�⵱mask == INT_MINʱ��-mask�������
		// mask & -mask ȡ����x1 ^ x2�Ķ����Ʊ�ʾ�����λ������Ϊ��lλ1
		// ��λx1��x2������һ������lλΪ0������һ������lλΪ1
		if (mask != INT_MIN) mask &= -mask;
		vector<int> ret(2, 0);
		int& ret1 = ret[0], &ret2 = ret[1];
		// ��ʱ���Խ�nums�е�����Ԫ�طֳ����࣬����һ��������ж����Ʊ�ʾ�ĵ�lλΪ0��������һ��������ж����Ʊ�ʾ�ĵ�lλΪ1������
		// 1. ����������nums�г������ε�Ԫ�أ���Ԫ�ص����γ��ֻᱻ������ͬһ���У����Ի�������е�������
		// 2. ��������һ��������nums��ֻ������һ�ε�Ԫ�أ���x1��x2�����ǻᱻ�����ڲ�ͬ���С�
		for (int num : nums) {
			if (num & mask) {
				ret1 ^= num;
			}
			else {
				ret2 ^= num;
			}
		}
		return ret;
	}
};