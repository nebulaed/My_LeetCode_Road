#include<iostream>
#include<vector>
#include<unordered_map>

using std::vector;
using std::unordered_map;

// �ҵĽⷨ��ǰ׺��+��ϣ��ʱ�� 84 ms 25.68%���ռ� 40.7 MB 13%
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		// count��ʾ����0��ʼ�ĺ�Ϊk��������������
		int prefixSum = 0, count = 0;
		// ǰ׺�ͳ��ִ�����ϣ��keyΪǰ׺�ͣ�valΪ���ִ���
		unordered_map<int, int> prefixSumFreq;
		for (int num : nums) {
			// ��ǰλ��ǰ׺��
			prefixSum += num;
			// ��ǰ׺�ͳ��ִ���+1
			++prefixSumFreq[prefixSum];
			// ����prefixSum - (prefixSum - k) == k������ǰ׺�͵���prefixSum - k�ĳ��ִ������ǲ���0��ʼ�ĺ�Ϊk��������������
			// ��kΪ0ʱ��Ҫע��prefixSum - k == prefixSum��Ҫ-1ȥ���Լ�
			count += prefixSumFreq[prefixSum - k] + (k == 0 ? -1 : 0);
		}
		return prefixSumFreq[k] + count;
	}
};

// �ҵĽⷨС�Ż���ǰ׺��+��ϣ��ʱ�� 84 ms 25.68%���ռ� 40.7 MB 16.51%
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		// count��ʾ����0��ʼ�ĺ�Ϊk��������������
		int prefixSum = 0, count = 0;
		// ǰ׺�ͳ��ִ�����ϣ��keyΪǰ׺�ͣ�valΪ���ִ���
		unordered_map<int, int> prefixSumFreq;
		for (int num : nums) {
			// ��ǰλ��ǰ׺��
			prefixSum += num;
			// ����prefixSum - (prefixSum - k) == k������ǰ׺�͵���prefixSum - k�ĳ��ִ������ǲ���0��ʼ�ĺ�Ϊk��������������
			count += prefixSumFreq[prefixSum - k];
			// ��ǰ׺�ͳ��ִ���+1
			++prefixSumFreq[prefixSum];
		}
		return prefixSumFreq[k] + count;
	}
};

// LeetCode 101�ⷨ��ǰ׺��+��ϣ��ʱ�� 80 ms 31.49%���ռ� 40.6 MB 22.97%
// ˼·������ǰ׺�ͣ���ͬ������������ʹ��һ����ϣ��hashmap�������ǰ׺�ͣ���ֵ�Ǹ�ǰ׺�ͳ��ֵĴ����������Ǳ�����λ��i ʱ�����赱ǰ��ǰ׺����psum����ôhashmap[psum - k]��Ϊ�Ե�ǰλ�ý�β���������������������
class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		int prefixSum = 0, count = 0;
		unordered_map<int, int> prefixSumFreq;
		prefixSumFreq[0] = 1;
		for (int num : nums) {
			prefixSum += num;
			count += prefixSumFreq[prefixSum - k];
			++prefixSumFreq[prefixSum];
		}
		return count;
	}
};