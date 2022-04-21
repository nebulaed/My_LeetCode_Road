#include<iostream>
#include<random>

int rand7(){
    return 1 + rand() % 7;
}
// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

// 我的解法：时间 4 ms 98.92%，空间 8.1 MB 35.94%
// rand() * rand()得到一个数num
// 乘积有1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 24, 25, 28, 30, 35, 36, 42, 49
// 权重为1, 2, 2, 3, 2, 4, 2, 2, 1, 2,  4,  2,  2,  1,  2,  2,  2,  2,  1,  2,  2,  2,  1,  2,  1
// 此时只需利用上所有概率和为4/49的组合即可，剩余的9/40直接拒绝掉
// rand()的循环次数期望为2.45
class Solution {
public:
    int rand10() {
        while (true) {
            int num = rand7() * rand7();
            if (num == 1 || num == 4) {
                return 1;
            }
            else if (num == 2 || num == 3) {
                return 2;
            }
            else if (num == 5 || num == 7) {
                return 3;
            }
            else if (num == 6) {
                return 4;
            }
            else if (num == 8 || num == 10) {
                return 5;
            }
            else if (num == 9 || num == 16 || num == 25 || num == 36) {
                return 6;
            }
            else if (num == 12) {
                return 7;
            }
            else if (num == 14 || num == 15) {
                return 8;
            }
            else if (num == 18 || num == 20) {
                return 9;
            }
            else if (num == 21 || num == 24) {
                return 10;
            }
        }
    }
};


// 我的解法优化：时间 4 ms 98.92%，空间 8.1 MB 35.94%
// 在以上基础上，当生成随机数在[41,49]内，相当于得到了一个[1,9]的随机数，再调用一次rand7()，就可以生成[1,63]的随机数，保留[1,60]并拒绝[61,63]，得到[1,3]的随机数，再调用rand7()，生成[1,21]的随机数，拒绝21，遇到21则从头开始，重新生成[1,49]的随机数。
// rand()循环次数期望为2.193


// 官方解法一：七进制+拒绝采样，时间 8 ms 78.48%，空间 8.1 MB 9.65%
class Solution {
public:
    int rand10() {
        int row, col, idx;
        do {
            row = rand7();
            col = rand7();
            idx = col + (row - 1) * 7;
        } while (idx > 40);
        return 1 + (idx - 1) % 10;
    }
};

// 官方解法二：七进制+拒绝采样，时间 4 ms 98.92%，空间 8 MB 53.14%
class Solution {
public:
    int rand10() {
        int a, b, idx;
        while (true) {
            a = rand7();
            b = rand7();
            idx = b + (a - 1) * 7;
            if (idx <= 40) {
                return 1 + (idx - 1) % 10;
            }
            a = idx - 40;
            b = rand7();
            // get uniform dist from 1 - 63
            idx = b + (a - 1) * 7;
            if (idx <= 60) {
                return 1 + (idx - 1) % 10;
            }
            a = idx - 60;
            b = rand7();
            // get uniform dist from 1 - 21
            idx = b + (a - 1) * 7;
            if (idx <= 20) {
                return 1 + (idx - 1) % 10;
            }
        }
    }
};