#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ����ά�;���ʱ�� 352 ms 71%���ռ� 144.5 MB 49%
// �ҵĽⷨ����ά�;���+�ƶ����캯����ʱ�� 324 ms 98.27%���ռ� 141.5 MB 99.28%
class NumMatrix {
private:
	vector<vector<int>> sumMatrix;
public:
	// sumMatrix[i][j]������matrix[0][0]Ϊ���Ͻǣ�matrix[i][j]Ϊ���½ǵľ����
	NumMatrix(vector<vector<int>>& matrix) : sumMatrix(move(matrix)) {
	//NumMatrix(vector<vector<int>> & matrix) : sumMatrix(matrix) {
		size_t height = sumMatrix.size(), width = sumMatrix[0].size();
		// �ȶԵ�һ�д���sumMatrix[0][i]���ڴ�matrix[0][0]��matrix[0][i]�ľ����
		for (size_t i = 1; i < width; ++i) {
			sumMatrix[0][i] += sumMatrix[0][i - 1];
		}
		for (size_t i = 1; i < height; ++i) {
			// sumMatrix[i][j]���ڴ�matrix[i][0]��matrix[i][j]�ľ����
			for (size_t j = 1; j < width; ++j) {
				sumMatrix[i][j] += sumMatrix[i][j - 1];
			}
			// sumMatrix[i][j]������һ�е�sumMatrix[i - 1][j]
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