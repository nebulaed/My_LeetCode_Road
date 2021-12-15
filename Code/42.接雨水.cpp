#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
using namespace std;

// �ٷ��ⷨ1����̬�滮���ö�̬�滮�ķ����õ�ÿ���������ߵ����߶�(��������)
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

// �ٷ��ⷨ2������ջ��ʱ��O(n) 12 ms���ռ�O(n) 15.6 MB
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

// �ٷ��ⷨ3��˫ָ�룬ʱ��O(n) 12 ms���ռ�O(1) 15.3 MB
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