#include<iostream>
#include<vector>
#include<unordered_map>
#include<algorithm>
using namespace std;

// �ҵĽⷨ
//class Solution {
//public:
//	vector<vector<int>> fourSum(vector<int>& nums, int target) {
//		int n = nums.size();
//		sort(nums.begin(), nums.end());
//		vector<vector<int>> ans;
//		// ö��(a,b,c,d)�е�a
//		for (int first = 0; first < n; ++first) {
//			// ö�ٵ�a�������ϸ�ö�ٵ�a��ֵ����
//			if (first > 0 && nums[first] == nums[first - 1]) {
//				continue;
//			}
//			for (int second = first + 1; second < n; ++second) {
//				// ö�ٵ�b�������ϸ�ö�ٵ�b��ֵ����
//				if (second > first + 1 && nums[second] == nums[second - 1]) {
//					continue;
//				}
//				// c��Ӧ��ָ���ʼָ����������Ҷ�
//				int fourth = n - 1;
//				int cur_target = target-nums[first]-nums[second];
//				// ö��b
//				for (int third = second + 1; third < n; ++third) {
//					// ͬ��Ҫ��֤ö�ٵ�c�������ϸ�ö�ٵ�c��ֵ����
//					if (third > second + 1 && nums[third] == nums[third - 1]) {
//						continue;
//					}
//					// ��Ҫ��֤b��ָ����c��ָ�����
//					while (third<fourth && nums[third] + nums[fourth]>cur_target) {
//						--fourth;
//					}
//					// ��ָ���غϣ�����c����������
//					// �Ͳ���������a+b+c+d = 0����c<d��d�ˣ������˳�ѭ��
//					if (third == fourth) {
//						break;
//					}
//					if (nums[third] + nums[fourth] == cur_target) {
//						ans.push_back({ nums[first],nums[second],nums[third],nums[fourth] });
//					}
//				}
//			}
//		}
//		return ans;
//	}
//};

// �ҵĽⷨ+С�Ż�
class Solution {
public:
	vector<vector<int>> fourSum(vector<int>& nums, int target) {
		int n = nums.size();
		if (n < 4) return {};
		sort(nums.begin(), nums.end());
		vector<vector<int>> ans;
		// ö��(a,b,c,d)�е�a
		for (int first = 0; first < n - 3; ++first) {
			// ö�ٵ�a�������ϸ�ö�ٵ�a��ֵ����
			if (first > 0 && nums[first] == nums[first - 1]) continue;
			if (nums[first] + nums[first + 1]> target - nums[first + 2] - nums[first + 3]) break;
			if (nums[first] + nums[n - 3]< target - nums[n - 2] - nums[n - 1]) continue;
			for (int second = first + 1; second < n - 2; ++second) {
				// ö�ٵ�b�������ϸ�ö�ٵ�b��ֵ����
				if (second > first + 1 && nums[second] == nums[second - 1]) continue;
				if (nums[first] + nums[second] > target - nums[second + 1] - nums[second + 2]) break;
				if (nums[first] + nums[second] < target - nums[n - 2] - nums[n - 1]) continue;
				// c��Ӧ��ָ���ʼָ����������Ҷ�
				int fourth = n - 1;
				int cur_target = target - nums[first] - nums[second];
				// ö��b
				for (int third = second + 1; third < n - 1; ++third) {
					// ͬ��Ҫ��֤ö�ٵ�c�������ϸ�ö�ٵ�c��ֵ����
					if (third > second + 1 && nums[third] == nums[third - 1]) {
						continue;
					}
					// ��Ҫ��֤b��ָ����c��ָ�����
					while (third<fourth && nums[third] + nums[fourth]>cur_target) {
						--fourth;
					}
					// ��ָ���غϣ�����c����������
					// �Ͳ���������a+b+c+d = 0����c<d��d�ˣ������˳�ѭ��
					if (third == fourth) {
						break;
					}
					if (nums[third] + nums[fourth] == cur_target) {
						ans.push_back({ nums[first],nums[second],nums[third],nums[fourth] });
					}
				}
			}
		}
		return ans;
	}
};

// �ٷ��ⷨ�����ҵĻ����ϼ�С�Ż�


int main() {
	vector<int> input = { 2,2,2,2,2 };
	int target = 8;

	Solution s;
	vector<vector<int>> ret = s.fourSum(input, target);

	cout << '[';
	for (int i = 0; i < ret.size(); ++i) {
		cout << "[ ";
		for (int j = 0; j < ret[i].size(); ++j) {
			cout << ret[i][j] << " ";
		}
		cout << ']';
	}
	cout << ']' << endl;

	system("pause");
	return 0;
}