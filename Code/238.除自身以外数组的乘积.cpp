#include<iostream>
#include<vector>
using namespace std;

// 我的解法：利用递归，右乘积通过递归逐步倒回去，左乘积作为全局变量不断向右乘过去，时间O(n) 28 ms，空间O(n) 28.1 MB
class Solution {
private:
	int leftProduct = 1;
	vector<int> output;
	void dfs(const vector<int>& nums, size_t pos, int rightProduct) {
		if (pos == 0) return;
		if (pos < nums.size()) {
			rightProduct *= nums[pos];
		}
		dfs(nums, pos - 1, rightProduct);
		if (pos >= 2) {
			leftProduct *= nums[pos - 2];
		}
		output[pos - 1] = rightProduct * leftProduct;
	}
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		output.resize(length);
		dfs(nums, length, 1);
		return output;
	}
};

// 官方解法一：左右乘积列表，时间O(n) 24 ms，空间O(n) 24.5 MB
// 初始化两个空数组L和R，对给定索引i，L[i]代表i左侧所有数字乘积，R[i]代表i右侧所有数字乘积
// 需要用两个循环来填充L和R数组的值。对于数组L，L[0]应该是1。对其他元素：L[i]=L[i-1]*nums[i-1]
// 对数组R，R[length-1]应为1，R[i] = R[i+1]*nums[i+1]
// 当R和L数组填充完成，只需在输入数组上迭代，且索引i处的值为L[i]*R[i]。
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> L(length), R(length);
		vector<int> answer(length);

		// L[i] 为索引 i 左侧所有元素的乘积
		// 对于索引为 '0' 的元素，因为左侧没有元素，所以 L[0] = 1
		L[0] = 1;
		for (size_t i = 1; i < length; ++i) {
			L[i] = nums[i - 1] * L[i - 1];
		}

		// R[i] 为索引 i 右侧所有元素的乘积
		// 对于索引为 'length-1' 的元素，因为右侧没有元素，所以 R[length-1] = 1
		R[length - 1] = 1;
		for (size_t i = length - 1; i > 0; --i) {
			R[i - 1] = nums[i] * R[i];
		}

		// 对于索引 i，除 nums[i] 之外其余各元素的乘积就是左侧所有元素的乘积乘以右侧所有元素的乘积
		for (size_t i = 0; i < length; ++i) {
			answer[i] = L[i] * R[i];
		}
		return answer;
	}
};

// 官方解法二：时间O(n) 24 ms，空间O(1) 23.5 MB
// 1.初始化answer数组，对于给定索引i，answer[i]代表i左侧所有数字的乘积
// 2.构造方式与之前的L相同
// 3.用一个遍历跟踪右边元素的乘积，并更新数组answer[i] = answer[i] * R，然后R更新为R = R * nums[i]，其中变量R表示索引右侧数字的乘积。
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> answer(length);

		// answer[i] 表示索引 i 左侧所有元素的乘积
		// 因为索引为 '0' 的元素左侧没有元素， 所以 answer[0] = 1
		answer[0] = 1;
		for (size_t i = 1; i < length; ++i) {
			answer[i] = nums[i - 1] * answer[i - 1];
		}

		// R 为右侧所有元素的乘积
		// 刚开始右边没有元素，所以 R = 1
		int R = 1;
		for (size_t i = length; i > 0; --i) {
			// 对于索引 i，左边的乘积为 answer[i]，右边的乘积为 R
			answer[i - 1] = answer[i - 1] * R;
			// R 需要包含右边所有的乘积，所以计算下一个结果时需要将当前值乘到 R 上
			R *= nums[i - 1];
		}
		return answer;
	}
};


// 评论区更优解法：一次遍历左右累乘，时间O(n) 16 ms，空间O(1) 23.5 MB
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		int leftProduct = 1, rightProduct = 1;
		vector<int> ret(length, 1);
		for (size_t i = 0; i < length; ++i) {
			ret[i] *= leftProduct;
			leftProduct *= nums[i];

			ret[length - 1 - i] *= rightProduct;
			rightProduct *= nums[length - 1 - i];
		}
		return ret;
	}
};