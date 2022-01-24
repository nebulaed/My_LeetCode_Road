#include<iostream>
#include<vector>
#include<unordered_map>

using std::vector;
using std::unordered_map;
using std::cout;
using std::endl;

// LeetCode 101�ⷨ������+���仯��ʱ�� 0 ms 100%���ռ� 7.8 MB 83.85%
// 1. ��ĿҪ��A[k]*2 != A[i] + A[j], ������i<k<j����֪��ʽ���Ϊż����ֻҪ��A[i]+A[j]Ϊ�������ɱ�֤������
// ��������+ż��=��������A[i]��A[j]һ��Ϊ����һ��Ϊż�����ɣ�����A[i]Ϊ������A[j]Ϊż����
// Ҳ����Ҫ�½�һ�����飬����Ϊn��������������ǰ�벿�֣�ż�����ں�벿�֡�
// 2. ��һ������ΪƯ�����飬�����Ա任�������Ҳ��Ư�����飬���[x1,x2,x3]��һ��Ư�����飬��ô[k*x1+b��k*x2+b,k*x3+b]Ҳ��Ư������
// 3. ���ڴ�1��n��������������������Ϊ(n+1)/2��ż������Ϊn/2
// 3.1 ���ڴ�1��(n+1)/2����������x���ó���Ư�����飬��ӳ���1��n��Χ�ڵ���������2*x-1
// 3.2 ����1��n/2����������x���ó���Ư�����飬��ӳ���1��n��Χ�ڵ�����ż��2*x
// 4. ��1��(n+1)/2�Լ�1��n/2��Χ��Ư�����飬�ǽ�һ���ݹ�õ��ġ��������ù�ϣ���¼�Ѽ���Ĵ�СΪn��Ư�����顣
class Solution {
private:
	unordered_map<int, vector<int>> memory;
public:
	vector<int> beautifulArray(int n) {
		if (memory.count(n)) {
			return memory[n];
		}

		vector<int> ret(n);
		if (n == 1) ret[0] = 1;
		else {
			int ind = 0;
			for (int x : beautifulArray((n + 1) / 2)) {
				ret[ind++] = 2 * x - 1;
			}
			for (int x : beautifulArray(n / 2)) {
				ret[ind++] = 2 * x;
			}
		}
		memory[n] = ret;
		return ret;
	}
};

int main() {

	Solution s;
	vector<int> ret = s.beautifulArray(5);

	cout << "[";
	for (int num : ret) {
		cout << num << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}