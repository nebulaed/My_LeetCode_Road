#include<iostream>
#include<random>

// The rand7() API is already defined for you.
// int rand7();
// @return a random integer in the range 1 to 7

// �ҵĽⷨ��ʱ�� 4 ms 98.92%���ռ� 8.1 MB 35.94%
// rand() * rand()�õ�һ����num
// �˻���1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 24, 25, 28, 30, 35, 36, 42, 49
// Ȩ��Ϊ1, 2, 2, 3, 2, 4, 2, 2, 1, 2,  4,  2,  2,  1,  2,  2,  2,  2,  1,  2,  2,  2,  1,  2,  1
// ��ʱֻ�����������и��ʺ�Ϊ4/49����ϼ��ɣ�ʣ���9/40ֱ�Ӿܾ���
// rand()��ѭ����������Ϊ2.45
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


// �ҵĽⷨ�Ż���ʱ�� 4 ms 98.92%���ռ� 8.1 MB 35.94%
// �����ϻ����ϣ��������������[41,49]�ڣ��൱�ڵõ���һ��[1,9]����������ٵ���һ��rand7()���Ϳ�������[1,63]�������������[1,60]���ܾ�[61,63]���õ�[1,3]����������ٵ���rand7()������[1,21]����������ܾ�21������21���ͷ��ʼ����������[1,49]���������
// rand()ѭ����������Ϊ2.193


// �ٷ��ⷨһ���߽���+�ܾ�������ʱ�� 8 ms 78.48%���ռ� 8.1 MB 9.65%
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

// �ٷ��ⷨ�����߽���+�ܾ�������ʱ�� 4 ms 98.92%���ռ� 8 MB 53.14%
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