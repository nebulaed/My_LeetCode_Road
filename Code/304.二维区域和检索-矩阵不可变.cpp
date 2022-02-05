#include<iostream>
#include<vector>
using namespace std;

// 我的解法：二维和矩阵，时间 352 ms 71%，空间 144.5 MB 49%
// 我的解法：二维和矩阵+移动构造函数，时间 324 ms 98.27%，空间 141.5 MB 99.28%
class NumMatrix {
private:
	vector<vector<int>> sumMatrix;
public:
	// sumMatrix[i][j]等于以matrix[0][0]为左上角，matrix[i][j]为右下角的矩阵和
	NumMatrix(vector<vector<int>>& matrix) : sumMatrix(move(matrix)) {
	//NumMatrix(vector<vector<int>> & matrix) : sumMatrix(matrix) {
		size_t height = sumMatrix.size(), width = sumMatrix[0].size();
		// 先对第一列处理，sumMatrix[0][i]等于从matrix[0][0]到matrix[0][i]的矩阵和
		for (size_t i = 1; i < width; ++i) {
			sumMatrix[0][i] += sumMatrix[0][i - 1];
		}
		for (size_t i = 1; i < height; ++i) {
			// sumMatrix[i][j]等于从matrix[i][0]到matrix[i][j]的矩阵和
			for (size_t j = 1; j < width; ++j) {
				sumMatrix[i][j] += sumMatrix[i][j - 1];
			}
			// sumMatrix[i][j]叠加上一行的sumMatrix[i - 1][j]
			for (size_t j = 0; j < width; ++j) {
				sumMatrix[i][j] += sumMatrix[i - 1][j];
			}
		}
	}

	int sumRegion(int row1, int col1, int row2, int col2) {
		return sumMatrix[row2][col2] - (row1 > 0 ? sumMatrix[row1 - 1][col2] : 0) - (col1 > 0 ? sumMatrix[row2][col1 - 1] : 0) + ((row1 > 0 && col1 > 0) ? sumMatrix[row1 - 1][col1 - 1] : 0);
	}
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */