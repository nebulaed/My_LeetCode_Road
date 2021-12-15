#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

//class Solution {
//	int capacity(const vector<int>& height, int x1, int x2) {
//		return min(height[x1], height[x2]) * abs(x1 - x2);
//	}
//public:
//	int maxArea(vector<int>& height) {
//		// 错误思路：一次左指针向右移动，一次右指针向左移动
//		//bool flag = true;
//		// 正确思路：左指针和右指针中较小的那一个向另一个移动
//		int i = 0;
//		int j = height.size()-1;
//		int maxCapacity = 0;
//		int curCapacity = 0;
//		while (i != j) {
//			curCapacity = capacity(height, i, j);
//			maxCapacity = curCapacity > maxCapacity ? curCapacity : maxCapacity;
//			if (height[i] < height[j]) ++i;
//			else --j;
//			//flag = !flag;
//		}
//		return maxCapacity;
//	}
//};

// 尝试优化时间和空间
class Solution {
public:
	int maxArea(vector<int>& height) {
		// 错误思路：一次左指针向右移动，一次右指针向左移动
		//bool flag = true;
		// 正确思路：左指针和右指针中较小的那一个向另一个移动
		int i = 0;
		int j = height.size() - 1;
		int maxCapacity = 0;
		int curCapacity = 0;
		while (i != j) {
			curCapacity = capacity(height[i], height[j], i, j);
			maxCapacity = max(curCapacity, maxCapacity);
			if (height[i] < height[j]) ++i;
			else --j;
			//flag = !flag;
		}
		return maxCapacity;
	}

	int capacity(const int& d1, const int& d2, const int& x1, const int& x2) {
		return min(d1, d2) * abs(x1 - x2);
	}
};

int main() {
	vector<int> input = { 2,3,10,5,7,8,9 };

	Solution s;
	int ret = s.maxArea(input);

	cout << ret << endl;

	system("pause");
	return 0;
}