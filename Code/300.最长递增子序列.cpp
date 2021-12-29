#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ�ο��ٷ���һ˼·��ʱ��O(n^2) 228 ms���ռ�O(n) 10.4 MB
// ˼·������dp[i]Ϊ�Ե�i�����ֽ�β����������������еĳ��ȣ�ע��nums[i]���뱻ѡȡ
// ��С����ļ���dp�����ֵ��״̬ת�Ʒ���Ϊ��dp[i] = dp[j] + 1������0<=j<i��nums[j]<nums[i]��dp[j]>=dp[i]
// ��������dp[0...i-1]����ĵ������������к��ټ�һ��nums[i]��
// ��������������������������м�����dp[i]�е����ֵ��
class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> dp(length, 1);
		for (size_t i = 1; i <= length; ++i) {
			for (size_t j = i - 1; j > 0; --j) {
				if (nums[i - 1] > nums[j - 1] && dp[i - 1] <= dp[j - 1]) {
					dp[i - 1] = dp[j - 1] + 1;
				}
			}
		}
		return *max_element(dp.begin(), dp.end());
	}
};

// �ҵĽⷨ����̰��+���ֲ��ң�ʱ��O(n log n) 8 ms���ռ�O(n) 10.2 MB
// ����һ���򵥵�̰�ģ�Ҫʹ�������������о����ܵس������������������þ������������ϣ��ÿ�������������������ϵ��Ǹ���������С��
// ���ڸ�̰��˼·��ά��һ����d[i]����ʾ����Ϊi����������������е�ĩβԪ�ص���Сֵ����len��¼Ŀǰ��������������еĳ���
// ��ʼʱlenΪ1��d[1] = nums[0]
// d[i]�ǹ���i���������ġ�
// �������α�������nums�е�ÿ��Ԫ�أ�����������d��len��ֵ�����nums[i]>d[len]�������len = len + 1��������d[1...len]��������d[i-1] < nums[j] < d[i]���±�i��������d[i] = nums[j]��
// ����d����ĵ����ԣ����ǿ���ʹ�ö��ֲ���Ѱ���±�i��
// ��������㷨����Ϊ��
// 1.�赱ǰ���������������������еĳ���Ϊlen����ǰ�����������nums���ڱ�����nums[i]ʱ��
// 1.1 ��nums[i]>d[len]����ֱ�Ӽ��뵽d����ĩβ��������len = len + 1;
// 1.2 ������d�����ж��ֲ��ң��ҵ���һ����nums[i]С����d[k]��������d[k+1] = nums[i]
class Solution {
private:
	size_t binarySearch(const vector<int>& nums, int target) {
		int left = 0, right = nums.size() - 1;
		while (left <= right) {
			int mid = (left + right) >> 1;
			if (target <= nums[mid]) {
				right = mid - 1;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}

public:
	int lengthOfLIS(vector<int>& nums) {
		vector<int> endArr(1, nums[0]);
		size_t len = 1;
		for (size_t i = 1; i < nums.size(); ++i) {
			int curr = nums[i];
			if (curr > endArr[len - 1]) {
				endArr.emplace_back(curr);
				++len;
			}
			else {
				endArr[binarySearch(endArr, curr)] = curr;
			}
		}
		return len;
	}
};

int main() {

	vector<int> nums = { 5,7,-24,12,13,2,3,12,5,6,35 };

	Solution s;
	int ret = s.lengthOfLIS(nums);

	cout << ret << "\n";

	system("pause");
	return 0;
}