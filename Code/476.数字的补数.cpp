#include<iostream>
#include<climits>
#include<cmath>

// 官方解法一：位运算，时间O(log num) 0 ms 100%，空间 O(1) 5.9 MB 25.52%
// 思路：以5=(101)_2为例，要做到对101取反得到010，显然不能直接使用~num，因为~num是将00000000 00000000 00000000 00000101取反得到11111111 11111111 11111111 11111010，因此需要对101求得对应位数的全1数mask-111，然后令num=101与111进行异或，得到010
class Solution {
public:
    int findComplement(int num) {
        int digit = static_cast<int>(log2(num)) + 1;
        //int digit = (num == 0 ? 0 : static_cast<int>(log2(num))) + 1; // 对1009题需要增加对0的处理
        int mask = digit >= 31 ? INT_MAX : (1 << digit) - 1;
        return num ^ mask;
    }
};

// 评论解法：位运算
// 时间 O(log log num)，由于log num < 32，所以可近似为O(log 32) = O(1)，0 ms 100%
// 空间 O(1) 5.7 MB 95.81%
// 原理：对一个数  00010000 00000000 00000000 00000000
// t | (t >> 1) = 00011000 00000000 00000000 00000000
// t | (t >> 2) = 00011110 00000000 00000000 00000000
// t | (t >> 4) = 00011111 11100000 00000000 00000000
// t | (t >> 8) = 00011111 11111111 11100000 00000000
// t | (t >> 16) = 00011111 11111111 11111111 11111111
// 相当于提供了一个对应位数的全1掩模
class Solution {
public:
    int findComplement(int num) {
        //if (num == 0) return 1; // 1009题输入有0，需要增加这个判断
        int t = num;
        t |= t >> 1;
        t |= t >> 2;
        t |= t >> 4;
        t |= t >> 8;
        t |= t >> 16;
        return ~num & t;
        //return num ^ t; // 效果与上相同
    }
};