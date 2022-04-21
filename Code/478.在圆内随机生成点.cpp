#define _USE_MATH_DEFINES
#include<iostream>
#include<vector>
#include<random>
#include<cmath>
using namespace std;

// 我的解法：计算分布函数，时间O(1) 52 ms，空间O(1) 26.6 MB
class Solution {
private:
    double radius;
    double x_center;
    double y_center;
public:
    Solution(double radius, double x_center, double y_center) : radius(radius), x_center(x_center), y_center(y_center) {}

    vector<double> randPoint() {
        double angle = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (2 * M_PI)));
        double len = sqrt(static_cast<double>(rand()) / static_cast<double> (RAND_MAX))* radius;
        vector<double> ret = { cos(angle) * len, sin(angle) * len };
        ret[0] += x_center;
        ret[1] += y_center;
        return ret;
    }
};

// 官方解法一：计算分布函数，时间O(1) 80 ms，空间O(1) 26.7 MB
// 使用C++11的随机数生成器mt19937和均匀分布uniform_real_distribution<double>
class Solution {
private:
    double radius;
    double x_center;
    double y_center;
    mt19937 rng{ random_device{}() };
    uniform_real_distribution<double> uni{ 0, 1 };
public:
    Solution(double radius, double x_center, double y_center) : radius(radius), x_center(x_center), y_center(y_center) {}

    vector<double> randPoint() {
        double angle = uni(rng) * 2 * M_PI;
        double len = sqrt(uni(rng)) * radius;
        vector<double> ret = { cos(angle) * len + x_center, sin(angle) * len + y_center };
        return ret;
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(radius, x_center, y_center);
 * vector<double> param_1 = obj->randPoint();
 */

int main() {

    Solution s(1, 0, 0);
    vector<double> ret = s.randPoint();

    for (double num : ret) cout << num << ",";

    cout << endl;

    return 0;
}
