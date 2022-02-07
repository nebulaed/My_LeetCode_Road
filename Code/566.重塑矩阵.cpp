#include<iostream>
#include<vector>

using std::vector;

// 我的解法：迭代器，时间 4 ms 98.97%，空间 10.5 MB 38.34% 
class Solution {
public:
	vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
		int m = mat.size(), n = mat[0].size();
		if (m * n != r * c || (m == r && n == c)) return mat;
		vector<vector<int>> ret(r, vector<int>(c));
		auto mit = mat.begin();
		auto nit = (*mit).begin();
		for (auto rit = ret.begin(); rit != ret.end(); ++rit) {
			for (auto cit = (*rit).begin(); cit != (*rit).end(); ++cit) {
				*cit = *nit;
				++nit;
				if (nit == (*mit).end() && mit != mat.end() - 1) {
					nit = (*(++mit)).begin();
				}
			}
		}
		return ret;
	}
};

// 官方解法1：二维数组的一维表示，时间 O(rc) 12 ms 40.50%，空间 O(1) 10.2 MB 95.10%
//                                        8  ms 86.45%，         10.4 MB 57.13%
class Solution {
public:
	vector<vector<int>> matrixReshape(vector<vector<int>>& mat, int r, int c) {
		int m = mat.size(), n = mat[0].size();
		if (m * n != r * c || (m == r && n == c)) return mat;
		vector<vector<int>> ret(r, vector<int>(c));
		for (int x = 0; x < m * n; ++x) {
			ret[x / c][x % c] = mat[x / n][x % n];
		}
		return ret;
	}
};