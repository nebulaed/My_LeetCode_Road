#include<iostream>
#include<array>
#include<vector>
using namespace std;

// �Ҳο��ٷ�˼·��д������̬�滮��ʱ��O(n) 8 ms���ռ�O(1) 13.4 MB
// ���������͵Ļ����ϣ�Ҫ���ǵ�ǰλ�õ����Žⲻһ����ǰһλ�õ����Ž�ת�Ƶõ��������Ҫͬʱά����С�˻������˻����Ա�֤[���ø���]�ĳ˻���������������������������
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int curMax = 1, curMin = 1, maxProduct = nums[0];
		array<int, 3> temp; 
		for (const auto& num : nums) {
			temp[0] = curMax * num;
			temp[1] = curMin * num;
			temp[2] = num;
			curMax = *max_element(temp.begin(), temp.end());
			curMin = *min_element(temp.begin(), temp.end());
			maxProduct = maxProduct > curMax ? maxProduct : curMax;
		}
		return maxProduct;
	}
};

// �ٷ��ⷨһ����̬�滮��ʱ��O(n) 12 ms���ռ�O(1) 13.4 MB
class Solution {
public:
	int maxProduct(vector<int>& nums) {
		int maxF = nums[0], minF = nums[0], ans = nums[0];
		for (int i = 1; i < nums.size(); ++i) {
			int mx = maxF, mn = minF;
			maxF = max(mx * nums[i], max(nums[i], mn * nums[i]));
			minF = min(mn * nums[i], min(nums[i], mx * nums[i]));
			ans = max(maxF, ans);
		}
		return ans;
	}
};