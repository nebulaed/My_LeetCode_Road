#include<iostream>
#include<vector>
#include<stack>
#include<algorithm>
using namespace std;

// �ҵĽⷨһ��ʹ����״ͼ���Ż�����������24 ms��11.6 MB
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size();
		if (m == 0) return 0;
		int n = matrix[0].size();

		vector<vector<int>> left(m, vector<int>(n, 0));

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
				}
			}
		}

		int ret = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				int width = left[i][j];
				int area = 1;
				for (int k = i - 1; k >= 0; --k) {
					width = min(width, left[k][j]);
					int height = i - k + 1;
					if (width >= height) {
						area = max(area, height * height);
					}
					else break;
				}
				ret = max(ret, area);
			}
		}
		return ret;
	}
};

// �ҵĽⷨ��������ջ
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size();
		if (m == 0) return 0;
		int n = matrix[0].size();

		vector<vector<int>> left(m, vector<int>(n, 0));

		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '1') {
					left[i][j] = (j == 0 ? 0 : left[i][j - 1]) + 1;
				}
			}
		}

		int ret = 0;
		for (int j = 0; j < n; ++j) {
			vector<int> up(m, 0), down(m, 0);
			stack<int> stk;
			for (int i = 0; i < m; ++i) {
				while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
					stk.pop();
				}
				up[i] = stk.empty() ? -1 : stk.top();
				stk.emplace(i);
			}
			stk = stack<int>();
			for (int i = m - 1; i >= 0; --i) {
				while (!stk.empty() && left[stk.top()][j] >= left[i][j]) {
					stk.pop();
				}
				down[i] = stk.empty() ? m : stk.top();
				stk.emplace(i);
			}
			for (int i = 0; i < m; ++i) {
				int sideLength = min(down[i] - up[i] - 1, left[i][j]);
				int area = sideLength * sideLength;
				ret = max(ret, area);
			}
		}
		return ret;
	}
};

// �ٷ����һ����������ʱ�� O(mn min(m,n)^2) 52 ms���ռ� O(1) 10.8 MB
// 1.���������е�ÿ��Ԫ�أ�ÿ������1���򽫸�Ԫ����Ϊ�����ε����Ͻ�
// 2.ȷ�������ε����ϽǺ󣬸������Ͻ����ڵ��к��м�����ܵ���������εı߳�(�����εķ�Χ���ܳ������������������)���ڸñ߳���Χ��Ѱ��ֻ����1�����������
// 3.ÿ�����·�����һ�����ҷ�����һ�У��ж��������к����Ƿ���������Ԫ�ض���1
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int rows = matrix.size(), columns = matrix[0].size();
		if (rows == 0 || columns == 0) return 0;
		int maxSide = 0;
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < columns; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				// ����һ��'1'��Ϊ�����ε����Ͻ�
				maxSide = max(maxSide, 1);
				// ������ܵ���������α߳�
				int currentMaxSide = min(rows - i, columns - j);
				for (int k = 1; k < currentMaxSide; ++k) {
					// �ж�������һ��һ���Ƿ��Ϊ1
					bool flag = true;
					if (matrix[i + k][j + k] == '0') {
						break;
					}
					for (int m = 0; m < k; ++m) {
						if (matrix[i + k][j + m] == '0' || matrix[i + m][j + k] == '0') {
							flag = false;
							break;
						}
					}
					if (flag) {
						maxSide = max(maxSide, k + 1);
					}
					else {
						break;
					}
				}
			}
		}
		int maxSquare = maxSide * maxSide;
		return maxSquare;
	}
};

// �ٷ��ⷨ������̬�滮��ʱ��O(mn) 24 ms���ռ�O(mn) 11.6 MB
// ��dp(i,j)��ʾ��(i,j)Ϊ���½ǣ���ֻ����1�������εı߳����ֵ�����ܼ��������dp(i,j)��ֵ����ô�������ֵ��ƽ����Ϊ�����
// ��ÿ��(i,j)������ھ����и�Ϊֹ��ֵ��
// 1.����λ����0����dp(i,j)=0
// 2.����λ����1����dp(i,j)��ֵ�����Ϸ����󷽺����Ϸ�����������λ�õ�dpֵ������������ԣ���ǰΪֹ��Ԫ��ֵ������������Ϊֹ��Ԫ���е���Сֵ+1
// �� dp(i,j) = min(dp(i-1,j),dp(i-1,j-1),dp(i,j-1)) + 1
// ����״̬ת�Ʒ���ԭ���1277��ٷ���⡣
// ���Ҫ���Ǳ߽����������i��j������һ��Ϊ0������(i,j)Ϊ���½ǵ���������εı߳�ֻ����1��
class Solution {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		int m = matrix.size(), n = matrix[0].size();
		vector<vector<int>> dp(m, vector<int>(n, 0));
		int maxSide = 0;
		for (int i = 0; i < m; ++i) {
			for (int j = 0; j < n; ++j) {
				if (matrix[i][j] == '0') {
					continue;
				}
				if (i == 0 || j == 0) {
					dp[i][j] = 1;
				}
				else {
					dp[i][j] = min({ dp[i - 1][j], dp[i - 1][j - 1], dp[i][j - 1] }) + 1;
				}
				maxSide = max(maxSide, dp[i][j]);
			}
		}
		return maxSide * maxSide;
	}
};