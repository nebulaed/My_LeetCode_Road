#include<iostream>
#include<vector>
using namespace std;

class Solution {
public:
	void rotate(vector<vector<int>>& matrix) {
		int temp;
		int n = matrix.size();
		for (int i = 0; i < n / 2; ++i) {
			for (int j = i; j < n - 1 - i; ++j) {
				temp = matrix[i][j];
				matrix[i][j] = matrix[n - 1 - j][i];
				matrix[n - 1 - j][i] = matrix[n - 1 - i][n - 1 - j];
				matrix[n - 1 - i][n - 1 - j] = matrix[j][n - 1 - i];
				matrix[j][n - 1 - i] = temp;
			}
		}
	}
};

int main() {
	vector<vector<int>> matrix;
	vector<int> temp = { 1,2,3 };
	matrix.emplace_back(temp);
	temp = { 4,5,6 };
	matrix.emplace_back(temp);
	temp = { 7,8,9 };
	matrix.emplace_back(temp);
	
	Solution s;
	s.rotate(matrix);

	cout << "[";
	for (int i = 0; i < matrix.size(); ++i) {
		cout << "[";
		for (int j = 0; j < matrix[i].size(); ++j) {
			cout << matrix[i][j];
			if (j != matrix[i].size() - 1) cout << ",";
		}
		cout << "]";
		if (i != matrix.size() - 1) cout << endl;
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}