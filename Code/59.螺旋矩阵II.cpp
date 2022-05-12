#include<vector>
using namespace std;

// 我的解法：按层模拟，时间 0 ms 100%，空间 6.3 MB 83.55%
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        size_t x = 0, y = 0, top = 0, bottom = n, left = 0, right = n;
        for (int i = 1, dir = 1; i <= n * n; ++i){
            matrix[x][y] = i;
            switch(dir){
                case 1:
                    if (y + 1 != right) ++y;
                    else {
                        ++dir;
                        ++top;
                        ++x;
                    }
                    break;
                case 2:
                    if (x + 1 != bottom) ++x;
                    else {
                        ++dir;
                        --right;
                        --y;
                    }
                    break;
                case 3:
                    if (y != left) --y;
                    else {
                        ++dir;
                        --bottom;
                        --x;
                    }
                    break;
                case 4:
                    if (x != top) --x;
                    else {
                        dir = 1;
                        ++left;
                        ++y;
                    }
                    break;
            }
        }
        return matrix;
    }
};