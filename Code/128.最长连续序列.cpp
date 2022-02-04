#include<iostream>
#include<vector>
#include<set>
#include<unordered_set>
#include<algorithm>
using namespace std;

// �������ṹ
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// �ҵĽⷨһ���Խ�������+���������ʱ�� 200 ms���ռ� 28.5 MB
class Solution {
private:
	int maxLength = 0;
	int temp = INT_MIN;
public:
	bool searchBST(TreeNode* T, int key, TreeNode* parent, TreeNode** p) {
		if (T == nullptr) {
			*p = parent;
			return false;
		}
		else if (T->val == key) {
			*p = T;
			return true;
		}
		else if (T->val > key) return searchBST(T->left, key, T, p);
		else return searchBST(T->right, key, T, p);
	}
	void createBST(TreeNode** T, int key) {
		TreeNode* p;
		if (searchBST(*T, key, nullptr, &p)) return;
		TreeNode* node = new TreeNode(key);
		if (p == nullptr) {
			*T = node;
		}
		else if (p->val > key) {
			p->left = node;
		}
		else {
			p->right = node;
		}
	}
	void inorderTraverse(TreeNode* T, int& length) {
		if (T == nullptr) return;
		inorderTraverse(T->left, length);
		if (T->val == temp + 1) {
			++length;
		}
		else {
			length = 1;
		}
		temp = T->val;
		maxLength = length > maxLength ? length : maxLength;
		inorderTraverse(T->right, length);
	}
	int longestConsecutive(vector<int>& nums) {
		TreeNode* root = nullptr;
		for (const auto& num : nums) {
			createBST(&root, num);
		}
		int length = 0;
		inorderTraverse(root, length);
		return maxLength;
	}
};

// �ҵĽⷨ��������set��ʱ�� 80 ms���ռ� 32.1 MB
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		set<int> numSet;
		for (const auto& num : nums) {
			numSet.emplace(num);
		}
		int maxLength = 0, length = 0, temp = INT_MIN;
		for (auto it = numSet.begin(); it != numSet.end(); ++it) {
			if (*it == temp + 1) {
				++length;
			}
			else {
				length = 1;
			}
			temp = *it;
			maxLength = length > maxLength ? length : maxLength;
		}
		return maxLength;
	}
};

// �ҵĽⷨ����ֱ��sort��ʱ�� 36 ms���ռ� 21.9 MB
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		sort(nums.begin(), nums.end());
		int maxLength = 0, length = 0, temp = INT_MIN;
		for (const auto& num : nums) {
			if (num == temp) continue;
			if (num == temp + 1) {
				++length;
			}
			else {
				length = 1;
			}
			temp = num;
			maxLength = length > maxLength ? length : maxLength;
		}
		return maxLength;
	}
};

// �ٷ��ⷨһ����ϣ��ʱ��O(n) 40 ms���ռ�O(n) 30.8 MB
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> numSet;
		for (const auto& num : nums) {
			numSet.emplace(num);
		}

		int maxLength = 0;
		for (const auto& num : numSet) {
			if (!numSet.count(num - 1)) {
				int lengthFromCur = 1;
				int temp = num;
				while (numSet.count(temp + 1)) {
					++temp;
					++lengthFromCur;
				}
				maxLength = lengthFromCur > maxLength ? lengthFromCur : maxLength;
				if (maxLength > nums.size() / 2) break;
			}
		}
		return maxLength;
	}
};

// �ҵĵڶ��νⷨ��ʱ�� 52 ms 85%���ռ� 30.1 MB 50%
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		if (nums.empty()) return 0;
		int maxLength = 1;
		unordered_map<int, int> numMap;
		for (int num : nums) {
			numMap[num] = 1;
		}
		for (auto& [curNum, curLength] : numMap) {
			int nextNum = curNum;
			while (numMap.count(++nextNum)) {
				if (numMap[nextNum] != 1) {
					curLength += numMap[nextNum];
					numMap.erase(nextNum);
					break;
				}
				else {
					++curLength;
					numMap.erase(nextNum);
				}
			}
			int prevNum = curNum;
			while (numMap.count(--prevNum)) {
				++curLength;
				numMap.erase(prevNum);
			}
			maxLength = max(curLength, maxLength);
		}
		return maxLength;
	}
};

// LeetCode 101�ⷨ����ϣ���ϣ�ʱ�� 52 ms 84.57%���ռ� 28.3 MB 82.71%
// ���������ַŵ�һ����ϣ��Ȼ�󲻶ϵشӹ�ϣ��������ȡһ��ֵ����ɾ������֮ǰ֮��������������֣�Ȼ�����Ŀǰ����������г��ȡ��ظ���һ���̣����ǾͿ����ҵ����е������������С�
class Solution {
public:
	int longestConsecutive(vector<int>& nums) {
		unordered_set<int> numSet(nums.begin(), nums.end());
		int ret = 0;
		while (!numSet.empty()) {
			int cur = *(numSet.begin());
			numSet.erase(cur);
			int next = cur, prev = cur;
			while (numSet.count(++next)) {
				numSet.erase(next);
			}
			while (numSet.erase(--prev)) {
				numSet.erase(prev);
			}
			ret = max(ret, next - prev - 1);
		}
		return ret;
	}
};

int main() {

	vector<int> nums = { 100, 4, 200, 1, 3, 2 };

	Solution s;
	int ret = s.longestConsecutive(nums);

	cout << ret << endl;

	system("pause");
	return 0;
}