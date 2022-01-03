#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ������+������ʱ��O(n logn) 64 ms���ռ�O(1) 32.8 MB
//class Solution {
//public:
//	vector<int> findDisappearedNumbers(vector<int>& nums) {
//		int n = nums.size();
//		vector<int> ret;
//		sort(nums.begin(), nums.end());
//		if (nums.front() != 1) {
//			for (int i = 1; i < nums[0]; ++i) {
//				ret.emplace_back(i);
//			}
//		}
//		for (size_t i = 1; i < nums.size(); ++i) {
//			if (nums[i] != nums[i - 1] && nums[i] != nums[i - 1] + 1) {
//				for (int j = nums[i - 1] + 1; j < nums[i]; ++j) {
//					ret.emplace_back(j);
//				}
//			}
//		}
//		if (nums.back() != n) {
//			for (int i = nums.back() + 1; i <= n; ++i) {
//				ret.emplace_back(i);
//			}
//		}
//		return ret;
//	}
//};

// �ҵĽⷨ������ϣ��ʽ���飬ʱ��O(n) 44 ms���ռ�O(n) 33.2 MB������bool������vector<int>������Ϊ33.9 MB
//class Solution {
//public:
//	vector<int> findDisappearedNumbers(vector<int>& nums) {
//		vector<int> ret;
//		size_t n = nums.size();
//		bool* counts = new bool[n]();
//		for (int num : nums) {
//			counts[num - 1] = true;
//		}
//		for (int i = 0; i < n; ++i) {
//			if (!counts[i]) {
//				ret.emplace_back(i + 1);
//			}
//		}
//		return ret;
//	}
//};

// �ٷ��ⷨһ��ԭ���޸ģ�ʱ��O(n) 48 ms���ռ�O(1) 32.9 MB
// ��һ����ϣ���¼nums�е����֣���¼���ֺ����ù�ϣ����[1,n]��ÿһ�����Ƿ���֣��ҵ�ȱʧ������
// ��������ó���Ϊn����������ϣ��
// Ϊ�ÿռ临�Ӷ��Ż���O(1)������������nums�䵱��ϣ��
// ����nums�����ַ�Χ����[1,n]�У����ǿ���������һ��Χ֮������֣�������Ƿ���ڵĺ���
// ���巽��������nums��ÿ����һ����x������nums[x-1]����n������nums������������[1,n]�С������Ժ���Щ����Ȼ����n��������Ǳ���nums����nums[i]δ����n��˵��û��������i+1���������ҵ���ȱʧ�����֡�
class Solution {
public:
	vector<int> findDisappearedNumbers(vector<int>& nums) {
		int n = nums.size();
		for (int num : nums) {
			// ע�⣬����num�п�����֮ǰ��nums[num-1]�����ӹ�n������Ҫ��num-1���г���nȡ����
			int x = (num - 1) % n;
			nums[num - 1] += n;
		}
		vector<int> ret;
		for (int i = 0; i < n; ++i) {
			if (nums[i] <= n) {
				ret.emplace_back(i + 1);
			}
		}
		return ret;
	}
};

int main() {

	vector<int> nums = { 4,3,2,7,8,2,3,1 };

	Solution s;
	vector<int> ret = s.findDisappearedNumbers(nums);

	for (int num : ret) {
		cout << num << ",";
	}

	system("pause");
	return 0;
}