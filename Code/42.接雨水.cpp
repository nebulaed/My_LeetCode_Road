#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

// 官方解法1：动态规划，用动态规划的方法得到每个坐标两边的最大高度(包括本身)
class Solution {
public:
	int trap(vector<int>& height) {
		int n = height.size();
		if (n == 0) {
			return 0;
		}
		vector<int> leftMax(n);
		leftMax[0] = height[0];
		for (int i = 1; i < n; ++i) {
			leftMax[i] = max(leftMax[i - 1], height[i]);
		}
		vector<int> rightMax(n);
		rightMax[n - 1] = height[n - 1];
		for (int i = n - 2; i >= 0; --i) {
			rightMax[i] = max(rightMax[i + 1], height[i]);
		}
		int sum = 0;
		for (int i = 0; i < n; ++i) {
			sum += min(leftMax[i], rightMax[i]) - height[i];
		}
		return sum; 
	}
};

// 官方解法2：单调栈，时间O(n) 12 ms，空间O(n) 15.6 MB
class Solution {
public:
	int trap(vector<int>& height) {
		int ret = 0;
		stack<int> stk;
		int n = height.size();
		for (int i = 0; i < n; ++i) {
			while (!stk.empty() && height[i] > height[stk.top()]) {
				int top = stk.top();
				stk.pop();
				if (stk.empty()) {
					break;
				}
				int left = stk.top();
				int curWidth = i - left - 1;
				int curHeight = min(height[left], height[i]) - height[top];
				ret += curWidth * curHeight;
			}
			stk.push(i);
		}
		return ret;
	}
};

// 官方解法3：双指针，时间O(n) 12 ms，空间O(1) 15.3 MB
class Solution {
public:
	int trap(vector<int>& height) {
		int ret = 0;
		int left = 0, right = height.size() - 1;
		int leftMax = 0, rightMax = 0;
		while (left < right) {
			leftMax = max(leftMax, height[left]);
			rightMax = max(rightMax, height[right]);
			if (height[left] < height[right]) {
				ret += leftMax - height[left];
				++left;
			}
			else {
				ret += rightMax - height[right];
				--right;
			}
		}
		return ret;
	}
};

int main() {
	vector<int> height = { 0,1,0,2,1,0,1,3,2,1,2,1 };

	Solution s;
	int ret = s.trap(height);

	cout << ret << endl;

	system("pause");
	return 0;
}