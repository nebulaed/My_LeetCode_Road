#include<iostream>
#include<cstring>
#include<vector>
#include<unordered_map>
using namespace std;

// 我的解法：利用哈希表的暴力遍历三次
//class Solution {
//private:
//	unordered_map<char, int> hashmap;
//public:
//	bool isValidSudoku(vector<vector<char>>& board) {
//		for (int i = 0; i < 9; ++i) {
//			hashmap = { {'1', 0},{'2', 0},{'3', 0},{'4', 0},{'5', 0},{'6', 0},{'7', 0},{'8', 0},{'9', 0} };
//			for (int j = 0; j < 9; ++j) {
//				if (hashmap.count(board[i][j])) {
//					++hashmap[board[i][j]];
//					if (hashmap[board[i][j]] > 1) {
//						return false;
//					}
//				}
//			}
//		}
//
//		for (int i = 0; i < 9; ++i) {
//			hashmap = { {'1', 0},{'2', 0},{'3', 0},{'4', 0},{'5', 0},{'6', 0},{'7', 0},{'8', 0},{'9', 0} };
//			for (int j = 0; j < 9; ++j) {
//				if (hashmap.count(board[j][i])) {
//					++hashmap[board[j][i]];
//					if (hashmap[board[j][i]] > 1) {
//						return false;
//					}
//				}
//			}
//		}
//
//		for (int i = 0; i < 9; i += 3) {
//			for (int j = 0; j < 9; j += 3) {
//				hashmap = { {'1', 0},{'2', 0},{'3', 0},{'4', 0},{'5', 0},{'6', 0},{'7', 0},{'8', 0},{'9', 0} };
//				for (int k = 0; k < 3; ++k) {
//					for (int l = 0; l < 3; ++l) {
//						if (hashmap.count(board[i + k][j + l])) {
//							++hashmap[board[i + k][j + l]];
//							if (hashmap[board[i + k][j + l]] > 1) {
//								return false;
//							}
//						}
//					}
//				}
//			}
//		}
//		return true;
//	}
//};

// 官方解法：因序号较少，可以只用数组不用哈希表，一次遍历完成
class Solution {
public:
    bool isValidSudoku(vector<vector<char>>& board) {
        int rows[9][9];
        int columns[9][9];
        int subboxes[3][3][9];

        // 一种初始化方法，将rows填满0
        memset(rows, 0, sizeof(rows));
        memset(columns, 0, sizeof(columns));
        memset(subboxes, 0, sizeof(subboxes));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                char c = board[i][j];
                if (c != '.') {
                    int index = c - '0' - 1;
                    ++rows[i][index];
                    ++columns[j][index];
                    ++subboxes[i / 3][j / 3][index];
                    if (rows[i][index] > 1 || columns[j][index] > 1 || subboxes[i / 3][j / 3][index] > 1) {
                        return false;
                    }
                }
            }
        }
        return true;
    }
};

int main() {
    vector<vector<char>> board;

    Solution s;
    bool ret = s.isValidSudoku(board);
    cout << ret << endl;

    return 0;
}