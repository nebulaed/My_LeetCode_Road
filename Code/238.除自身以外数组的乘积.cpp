#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ�����õݹ飬�ҳ˻�ͨ���ݹ��𲽵���ȥ����˻���Ϊȫ�ֱ����������ҳ˹�ȥ��ʱ��O(n) 28 ms���ռ�O(n) 28.1 MB
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

// �ٷ��ⷨһ�����ҳ˻��б�ʱ��O(n) 24 ms���ռ�O(n) 24.5 MB
// ��ʼ������������L��R���Ը�������i��L[i]����i����������ֳ˻���R[i]����i�Ҳ��������ֳ˻�
// ��Ҫ������ѭ�������L��R�����ֵ����������L��L[0]Ӧ����1��������Ԫ�أ�L[i]=L[i-1]*nums[i-1]
// ������R��R[length-1]ӦΪ1��R[i] = R[i+1]*nums[i+1]
// ��R��L���������ɣ�ֻ�������������ϵ�����������i����ֵΪL[i]*R[i]��
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> L(length), R(length);
		vector<int> answer(length);

		// L[i] Ϊ���� i �������Ԫ�صĳ˻�
		// ��������Ϊ '0' ��Ԫ�أ���Ϊ���û��Ԫ�أ����� L[0] = 1
		L[0] = 1;
		for (size_t i = 1; i < length; ++i) {
			L[i] = nums[i - 1] * L[i - 1];
		}

		// R[i] Ϊ���� i �Ҳ�����Ԫ�صĳ˻�
		// ��������Ϊ 'length-1' ��Ԫ�أ���Ϊ�Ҳ�û��Ԫ�أ����� R[length-1] = 1
		R[length - 1] = 1;
		for (size_t i = length - 1; i > 0; --i) {
			R[i - 1] = nums[i] * R[i];
		}

		// �������� i���� nums[i] ֮�������Ԫ�صĳ˻������������Ԫ�صĳ˻������Ҳ�����Ԫ�صĳ˻�
		for (size_t i = 0; i < length; ++i) {
			answer[i] = L[i] * R[i];
		}
		return answer;
	}
};

// �ٷ��ⷨ����ʱ��O(n) 24 ms���ռ�O(1) 23.5 MB
// 1.��ʼ��answer���飬���ڸ�������i��answer[i]����i����������ֵĳ˻�
// 2.���췽ʽ��֮ǰ��L��ͬ
// 3.��һ�����������ұ�Ԫ�صĳ˻�������������answer[i] = answer[i] * R��Ȼ��R����ΪR = R * nums[i]�����б���R��ʾ�����Ҳ����ֵĳ˻���
class Solution {
public:
	vector<int> productExceptSelf(vector<int>& nums) {
		size_t length = nums.size();
		vector<int> answer(length);

		// answer[i] ��ʾ���� i �������Ԫ�صĳ˻�
		// ��Ϊ����Ϊ '0' ��Ԫ�����û��Ԫ�أ� ���� answer[0] = 1
		answer[0] = 1;
		for (size_t i = 1; i < length; ++i) {
			answer[i] = nums[i - 1] * answer[i - 1];
		}

		// R Ϊ�Ҳ�����Ԫ�صĳ˻�
		// �տ�ʼ�ұ�û��Ԫ�أ����� R = 1
		int R = 1;
		for (size_t i = length; i > 0; --i) {
			// �������� i����ߵĳ˻�Ϊ answer[i]���ұߵĳ˻�Ϊ R
			answer[i - 1] = answer[i - 1] * R;
			// R ��Ҫ�����ұ����еĳ˻������Լ�����һ�����ʱ��Ҫ����ǰֵ�˵� R ��
			R *= nums[i - 1];
		}
		return answer;
	}
};


// ���������Žⷨ��һ�α��������۳ˣ�ʱ��O(n) 16 ms���ռ�O(1) 23.5 MB
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