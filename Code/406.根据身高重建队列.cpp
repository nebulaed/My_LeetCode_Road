#include<iostream>
#include<vector>
#include<list>
#include<algorithm>
using namespace std;

// �ٷ����һ���ӵ͵��߿��ǣ�ʱ��O(n^2) 44 ms���ռ�O(log n) 11.4 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// ��people�������h_iΪ��һ�ؼ�������k_iΪ�ڶ��ؼ��ֽ����������
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] < rhs[0] || (lhs[0] == rhs[0] && lhs[1] > rhs[1]);
			});
		size_t n = people.size();
		// ��ʼ��һ������n��λ�õĿն���
		vector<vector<int>> ret(n);
		for (const auto& person : people) {
			// person��λ�ã�Ӧ���ڶ����д�����������k_i+1����λ��
			int spaces = person[1] + 1;
			for (size_t i = 0; i < n; ++i) {
				if (ret[i].empty()) {
					// ret[i]�ǿ�λ�ã�spaces�������Լ�1
					--spaces;
					// �ѵ����k_i+1����λ�ã���ֵ������ѭ��
					if (!spaces) {
						ret[i] = person;
						break;
					}
				}
			}
		}
		return ret;
	}
};

// �ٷ��������Ӹߵ��Ϳ��ǣ�ʱ��O(n^2) 140 ms���ռ�O(log n) 11.7 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// ��people�������h_iΪ��һ�ؼ��ֽ���k_iΪ�ڶ��ؼ��������������
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
			});
		vector<vector<int>> ret;
		// �����i����ʱ��������뵽k_i+1��λ��
		for (const vector<int>& person : people) {
			ret.emplace(ret.begin() + person[1], person);
		}
		return ret;
	}
};

// �ٷ������Ż�����˫��������߲���Ч�ʣ�ʱ��O(n^2) 32 ms���ռ�O(n) 12.8 MB
class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		// ��people�������h_iΪ��һ�ؼ��ֽ���k_iΪ�ڶ��ؼ��������������
		sort(people.begin(), people.end(), [](const vector<int>& lhs, const vector<int>& rhs) {
			return lhs[0] > rhs[0] || (lhs[0] == rhs[0] && lhs[1] < rhs[1]);
			});
		list<vector<int>> ret;
		// �����i����ʱ��������뵽k_i+1��λ��
		for (const vector<int>& person : people) {
			auto it = ret.begin();
			// ��it��������ǰ�ƶ�person[1]��
			advance(it, person[1]);
			ret.emplace(it, person);
		}
		return vector<vector<int>>(ret.begin(),ret.end());
	}
};