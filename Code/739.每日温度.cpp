#include<iostream>
#include<vector>
#include<stack>

using std::vector;
using std::stack;

// LeetCode 101�ⷨ������ջ��ʱ�� 128 ms 83.79%���ռ� 86.9 MB 30.89%
// ά��һ�������ݼ���ջ����ջ�д��λ�ö�����ֵ���������ұ������飬����ÿ��λ��p�����p����ֵ��ջ���洢λ��q����ֵ����ȡ��q������¼p��q�ľ���Ϊp-q���ظ���һ���̣�ֱ��p��Ӧ��ֵС�ڵ���ջ���洢λ�õ���ֵ(���ջ)ʱ����p����ջ����Ȼ�������
// ����������У�ջ�����鱣����Զ�����ݼ�������ʹ��������бȽϡ�
// ���ջ��ʣ��һЩ���ڣ�˵������֮��û�г��ָ������ֵ��
class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		stack<int> stk;
		int n = temperatures.size();
		vector<int> ret(n, 0);
		for (int i = 0; i < n; ++i) {
			while (!stk.empty()) {
				int prev = stk.top();
				if (temperatures[i] <= temperatures[prev]) {
					break;
				}
				stk.pop();
				ret[prev] = i - prev;
			}
			stk.emplace(i);
		}
		return ret;
	}
};

// �ҵĽⷨ������ջ��ʱ�� O(n) 132 ms 75.87%���ռ� O(n) 86.9 MB 14.69%
class Solution {
public:
	vector<int> dailyTemperatures(vector<int>& temperatures) {
		stack<int> stk;
		int n = temperatures.size();
		vector<int> ret(n, 0);
		for (int i = 0; i < n; ++i) {
			while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
				int prev = stk.top();
				ret[prev] = i - prev;
				stk.pop();
			}
			stk.emplace(i);
		}
		return ret;
	}
};