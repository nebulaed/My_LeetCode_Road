#include<iostream>
#include<vector>

using std::vector;

// �ҵĽⷨ����������ʱ�� 4 ms 98.97%���ռ� 10.5 MB 38.34% 
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

// �ٷ��ⷨ1����ά�����һά��ʾ��ʱ�� O(rc) 12 ms 40.50%���ռ� O(1) 10.2 MB 95.10%
//                                        8  ms 86.45%��         10.4 MB 57.13%
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