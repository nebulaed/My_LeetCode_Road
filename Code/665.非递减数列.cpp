#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

// �ҵĽⷨ��̰���㷨+˫ָ�룬ʱ��O(n) 20 ms 83%���ռ�O(1) 26.4 MB 68%
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		int count = 0;
		size_t left = 0, right = 1, n = nums.size();
		while (right < n) {
			// ��leftָ��Ԫ�ش���rightָ��Ԫ��
			if (nums[left] > nums[right]) {
				// ��Ҫ�ı��Ԫ��+1
				++count;
				// ���ı�Ԫ�ش���2������false
				if (count > 1) return false;
				// ��right����n-1��leftָ��Ԫ��С�ڵ���right+1ָ��Ԫ��(�ܱ�֤�ǵݼ�)
				if (right == n - 1 || nums[left] <= nums[right + 1]) {
					// ��leftָ��Ԫ�ظ���rightָ��λ��
					nums[right] = nums[left];
				}
				// ��left����0��rightָ��Ԫ�ش��ڵ���left-1ָ��Ԫ��(�ܱ�֤�ǵݼ�)
				else if (left == 0 || nums[right] >= nums[left - 1]) {
					// ��rightָ��Ԫ�ظ���leftָ��λ��
					nums[left] = nums[right];
				}
				// �����������㣬����false
				else return false;
			}
			++left;
			++right;
		}
		return true;
	}
};

// �ҵĽⷨ�����淽��С�Ż�, ̰���㷨��ʱ�� 16 ms 95.53%���ռ� 26.2 MB 97.94%
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		int count = 0;
		size_t n = nums.size();
		for (size_t i = 0; i < n - 1; ++i) {
			int curr = nums[i], next = nums[i + 1];
			if (curr > next) {
				++count;
				if (count > 1) return false;
				if (i + 1 == n - 1 || curr <= nums[i + 2]) {
					nums[i + 1] = curr;
				}
				else if (i == 0 || next >= nums[i - 1]) {
					nums[i] = next;
				}
				else return false;
			}
		}
		return true;
	}
};


// �ٷ��ⷨ�����飬ʱ�� 16 ms 95.53%���ռ� 26.4 MB 43.92%
// ˼���������⣺Ҫʹnums���һ���ǵݼ����У������������ж��ٸ�i����nums[i]>nums[i+1]��
// �Լ�˼����֪����һ��
// ��������������޷���֤�޸ĺ��ܽ����Ϊ�ǵݼ����У���[3,4,1,2]����Ȼֻ��4����nums[i]>nums[i+1]��������4��ô�޸Ķ����ܱ�ɷǵݼ�����
// ��ˣ����ҵ�����nums[i]>nums[i+1]��i���������޸�nums[i]��nums[i+1]��nums�Ƿ��ɷǵݼ�����
// �޸�ʱ����nums[i]�޸ĳ�nums[i+1]����õģ���nums[i+1]�������޸ĳ�nums[i]����õ�
class Solution {
public:
	bool checkPossibility(vector<int>& nums) {
		size_t n = nums.size();
		for (size_t i = 0; i < n - 1; ++i) {
			int x = nums[i], y = nums[i + 1];
			if (x > y) {
				nums[i] = y;
				// �����޸�nums[i]Ϊnums[i+1]���Ƿ��ѳɷǵݼ����У����򷵻�true
				if (is_sorted(nums.begin(), nums.end())) {
					return true;
				}
				nums[i] = x;	// ��ԭ
				nums[i + 1] = x;
				// �޸�nums[i]Ϊnums[i+1]�����У������޸�nums[i+1]Ϊnums[i]�����ѳɷǵݼ����У�����true�����򷵻�false
				return is_sorted(nums.begin(), nums.end());
			}
		}
		// nums���Ƿǵݼ�����
		return true;
	}
};