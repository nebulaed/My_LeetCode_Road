#include<vector>
using namespace std;

// 我的解法：模拟，时间 O(mn) 0 ms 100%，空间 O(mn) 6.7 MB 44.60%
//class Solution {
//public:
//    vector<int> spiralOrder(vector<vector<int>>& matrix) {
//        size_t m = matrix.size(), n = matrix[0].size(), len = m * n;
//        vector<bool> visited(len, false);
//        vector<int> ret(len);
//        int dir = 1;
//        for (size_t i = 0, x = 0, y = 0; i < len; ++i){
//            ret[i] = matrix[x][y];
//            visited[x * n + y] = true;
//            switch(dir){
//                case 1:
//                    if (y + 1 != n && !visited[x * n + y + 1]){
//                        ++y;
//                    } else{
//                        ++dir;
//                        ++x;
//                    }
//                    break;
//                case 2:
//                    if (x + 1 != m && !visited[(x + 1) * n + y]){
//                        ++x;
//                    } else {
//                        ++dir;
//                        --y;
//                    }
//                    break;
//                case 3:
//                    if (y != 0 && !visited[x * n + y - 1]){
//                        --y;
//                    } else {
//                        ++dir;
//                        --x;
//                    }
//                    break;
//                case 4:
//                    if (!visited[(x - 1) * n + y]){
//                        --x;
//                    } else {
//                        dir = 1;
//                        ++y;
//                    }
//                    break;
//            }
//        }
//        return ret;
//    }
//};

// 我的解法：按层模拟，时间 O(mn) 0 ms 100%，空间 O(1) 6.7 MB 46.35%
class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        size_t m = matrix.size(), n = matrix[0].size(), len = m * n;
        size_t top = 1, bottom = m, left = 0, right = n;
        vector<int> ret(len);
        int dir = 1;
        for (size_t i = 0, x = 0, y = 0; i < len; ++i){
            ret[i] = matrix[x][y];
            switch(dir){
                case 1:
                    if (y + 1 != right){
                        ++y;
                    } else{
                        ++dir;
                        ++x;
                        --right;
                    }
                    break;
                case 2:
                    if (x + 1 != bottom){
                        ++x;
                    } else {
                        ++dir;
                        --y;
                        --bottom;
                    }
                    break;
                case 3:
                    if (y != left){
                        --y;
                    } else {
                        ++dir;
                        --x;
                        ++left;
                    }
                    break;
                case 4:
                    if (x != top){
                        --x;
                    } else {
                        dir = 1;
                        ++y;
                        ++top;
                    }
                    break;
            }
        }
        return ret;
    }
};