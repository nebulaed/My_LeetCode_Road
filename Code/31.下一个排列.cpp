#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ(�ο��ٷ�˼·)
//class Solution {
//public:
//	void nextPermutation(vector<int>& nums) {
//		int pos = -1;
//		for (int i = 0; i < nums.size() - 1; ++i) {
//			if (nums[i] < nums[i + 1]) {
//				pos = i;
//			}
//		}
//		if (pos != -1) {
//			int pos2;
//			for (pos2 = nums.size() - 1; pos2 > pos; --pos2) {
//				if (nums[pos] < nums[pos2]) {
//					break;
//				}
//			}
//			int temp = nums[pos];
//			nums[pos] = nums[pos2];
//			nums[pos2] = temp;
//			reverse(nums.begin() + pos + 1, nums.end());
//		}
//		else {
//			reverse(nums.begin(), nums.end());
//		}
//	}
//};

// �ٷ��ⷨ������ɨ�裬ʱ��O(n)���ռ� O(1)
// ����ϣ���ҵ�һ�ַ������ܹ��ҵ�һ�����ڵ�ǰ���е������У��ұ��ķ��Ⱦ�����С��
// 1.������Ҫ��һ����ߵġ���С������һ���ұߵġ��ϴ��������������ܹ��õ�ǰ���б�󣬴Ӷ��õ���һ�����С�
// 2.ͬʱ����Ҫ���������С�����������ң������ϴ�����������С����������ɺ󣬡��ϴ������ұߵ�����Ҫ���������������С����������ڱ�֤�����д���ԭ�����е�����£�ʹ���ķ��Ⱦ�����С��
// ���ڳ���Ϊ n ������ a��
// 1. ���ȴӺ���ǰ���ҵ�һ��˳��� (i,i+1)������ a[i] < a[i+1]����������С������Ϊ a[i]����ʱ [i+1,n) ��Ȼ���½����С�
// 2. ����ҵ���˳��ԣ���ô������ [i+1,n) �дӺ���ǰ���ҵ�һ��Ԫ�� j ���� a[i] < a[j]���������ϴ�������Ϊ a[j]��
// 3. ���� a[i] �� a[j]����ʱ����֤������ [i+1,n) ��Ϊ�������ǿ���ֱ��ʹ��˫ָ�뷴ת���� [i+1,n) ʹ���Ϊ���򣬶�����Ը������������

class Solution {
public:
	void nextPermutation(vector<int>& nums) {
		int i = nums.size() - 2;
		while (i >= 0 && nums[i] >= nums[i + 1]) {
			--i;
		}

		if (i >= 0) {
			int j = nums.size() - 1;
			while (j >= 0 && nums[i] >= nums[j]) {
				--j;
			}
			swap(nums[i], nums[j]);
		}
		reverse(nums.begin() + i + 1, nums.end());
	}
};

int main() {
	vector<int> nums = { 1,3,1,4,3 };

	Solution s;
	s.nextPermutation(nums);

	cout << '[';
	for (int i = 0; i < nums.size(); ++i) {
		cout << nums[i] << ',';
	}
	cout << ']' << endl;

	system("pause");
	return 0;
}