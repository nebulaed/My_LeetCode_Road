#include<iostream>
#include<vector>
#include<algorithm>

using std::vector;
using std::max;

// �ҵĽⷨһ����̬�滮��ʱ�� 8 ms 11.92%���ռ� 7.1 MB 9.36%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		vector<int> dp(n, 1);
		vector<int> prev(n, -1);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1], curNum = nums[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				int pre = dp[j - 1], preNum = nums[j - 1];
				if (curNum > preNum && (j < 2 || preNum < prev[j - 1])) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = preNum;
					}
				}
				else if (curNum < preNum && (j < 2 || preNum > nums[j - 2])) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = preNum;
					}
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// �ҵĽⷨ������̬�滮��ʱ�� 8 ms 11.92%���ռ� 7.1 MB 15.03%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		vector<int> dp(n, 1);
		vector<bool> prev(n, false);
		int maxLength = 0;
		for (size_t i = 1; i <= n; ++i) {
			int& cur = dp[i - 1], curNum = nums[i - 1];
			for (size_t j = i - 1; j > 0; --j) {
				int pre = dp[j - 1], preNum = nums[j - 1];
				bool preFlag = prev[j - 1];
				if (j < 2) {
					if (cur <= pre) {
						if (curNum > preNum) {
							cur = pre + 1;
							prev[i - 1] = true;
						}
						else if (curNum < preNum) {
							cur = pre + 1;
							prev[i - 1] = false;
						}
					}
					continue;
				}
				if (curNum > preNum && !preFlag) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = !preFlag;
					}
				}
				else if (curNum < preNum && preFlag) {
					if (cur <= pre) {
						cur = pre + 1;
						prev[i - 1] = !preFlag;
					}
				}
			}
			maxLength = max(maxLength, cur);
		}
		return maxLength;
	}
};

// �ҵĽⷨ����̰�ģ�ʱ�� 0 ms 100%���ռ� 7 MB 19.62%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		size_t n = nums.size();
		if (n == 1) return n;
		// ���ڶ���Ԫ�ص��ڵ�һ��Ԫ�أ��ڶ����еĿ�ͷֻ��һ��Ԫ�أ�����������
		bool equal = nums[0] == nums[1];
		vector<int> endArr{ nums[0] };
		if (!equal) {
			endArr.emplace_back(nums[1]);
		}
		// �жϵڶ���Ԫ���Ǵ��ڵ�һ��Ԫ�ػ���С�ڵ�һ��Ԫ��
		bool swing = nums[0] < nums[1];
		for (size_t i = 2; i < n; ++i) {
			int num = nums[i];
			// ����ǰԪ�ص��ڰڶ����н�βԪ�أ�ֱ������
			if (num == endArr.back()) {
				continue;
			}
			// ���ڶ�����Ŀǰֻ��һ��Ԫ�أ���ǰԪ��ֻҪ���Ԫ�ز���ȣ������ԷŽ��ڶ�����
			if (equal) {
				// ���ڶ�Ԫ��С�ڰڶ����е�һԪ�أ����swingΪ��
				if (num < endArr.back()) {
					swing = false;
				}
				// ���ڶ�Ԫ�ش��ڰڶ����е�һԪ�أ����swingΪ��
				else {
					swing = true;
				}
				endArr.emplace_back(num);
				// �ڶ����в���ֻ��һ��Ԫ��
				equal = false;
				continue;
			}
			// ���ڶ����н�βԪ�ر���һԪ�ش�
			if (swing) {
				// ����ǰԪ�رȰڶ����н�βԪ��С������prev < end > num�����ԷŽ��ڶ����У������swingΪ��
				if (num < endArr.back()) {
					endArr.emplace_back(num);
					swing = false;
				}
				// ����ǰԪ�رȰڶ����н�βԪ�ش󣬸��°ڶ����н�βԪ��Ϊnum
				else {
					endArr.back() = num;
				}
			}
			// ���ڶ����н�βԪ�ر���һԪ��С
			else {
				// ����ǰԪ�رȰڶ����н�βԪ�ش󣬹���prev > end < num�����ԷŽ��ڶ����У������swingΪ��
				if (num > endArr.back()) {
					endArr.emplace_back(num);
					swing = true;
				}
				// ����ǰԪ�رȰڶ����н�βԪ��С�����°ڶ����н�βԪ��Ϊnum
				else {
					endArr.back() = num;
				}
			}
		}
		return endArr.size();
	}
};

// �ٷ��ⷨһ����̬�滮��ʱ��O(n) 4 ms 34.79%���ռ�O(n) 7.1 MB 16.44%
// �����ڶ����б�ʾ���һ��Ԫ�������İڶ����У�...
// ˼·���г�״̬���ʽΪ��
// 1.up[i]��ʾ��ǰi��Ԫ���е�ĳһ��Ϊ��β��������ڶ����еĳ���
// 2.down[i]��ʾ��ǰi��Ԫ���е�ĳһ��Ϊ��β������½��ڶ����г���
// ��up[i]Ϊ����˵����״̬ת�ƹ���
// 1. ��nums[i] <= nums[i - 1]�������ڶ������޷���չ��up[i] = up[i - 1]
// 2. ��nums[i] > nums[i - 1]��up[i] = max(up[i - 1], down[i - 1] + 1)
// ���Ƶ��У�1.down[i] = down[i - 1]
// 2. down[i] = max(down[i-1], up[i - 1] + 1)
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return n;
		}
		vector<int> up(n), down(n);
		up[0] = down[0] = 1;
		for (int i = 1; i < n; i++) {
			if (nums[i] > nums[i - 1]) {
				up[i] = max(up[i - 1], down[i - 1] + 1);
				down[i] = down[i - 1];
			}
			else if (nums[i] < nums[i - 1]) {
				up[i] = up[i - 1];
				down[i] = max(up[i - 1] + 1, down[i - 1]);
			}
			else {
				up[i] = up[i - 1];
				down[i] = down[i - 1];
			}
		}
		return max(up[n - 1], down[n - 1]);
	}
};

// �ٷ��ⷨ������̬�滮+�������飬ʱ��O(n) 0 ms 100%���ռ�O(1) 6.8 MB 69.86%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return n;
		}
		int up = 1, down = 1;
		for (int i = 1; i < n; i++) {
			if (nums[i] > nums[i - 1]) {
				// ע�⵽ÿ��һ���嵽�ȣ�down�Ż�+1��ÿ��һ���ȵ���up�Ż�+1��������down��up�Ĳ�㲻����1�����up<=down + 1��down <= up + 1����˲���Ҫ��up��down+1ȡ���ֵ��Ҳ���ض�up+1��downȡ���ֵ
				//up = max(up, down + 1);
				up = down + 1;
				
			}
			else if (nums[i] < nums[i - 1]) {
				//down = max(up + 1, down);
				down = up + 1;
			}
		}
		return max(up, down);
	}
};

// �ٷ��ⷨ����̰�ģ�ʱ��O(n) 0 ms 100%���ռ�O(1) 6.9 MB 60.73%
class Solution {
public:
	int wiggleMaxLength(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) return n;
		int prevdiff = nums[1] - nums[0];
		int ret = prevdiff != 0 ? 2 : 1;
		for (int i = 2; i < n; i++) {
			int diff = nums[i] - nums[i - 1];
			if ((diff > 0 && prevdiff <= 0) || (diff < 0 && prevdiff >= 0)) {
				++ret;
				prevdiff = diff;
			}
		}
		return ret;
	}
};