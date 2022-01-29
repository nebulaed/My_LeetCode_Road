#include<iostream>
#include<unordered_set>

using std::unordered_set;

// �ҵĽⷨ1����ϣ���ϼ�¼������ѭ����Ϊ�٣�����Ϊ�棬ʱ�� 4 ms 49.39%���ռ� 6.1 MB 59.51%
class Solution {
public:
	bool isHappy(int n) {
		unordered_set<int> record;
		while (!record.count(n)) {
			record.emplace(n);
			int sum = 0;
			while (n != 0) {
				int cur = n % 10;
				sum += cur * cur;
				n /= 10;
			}
			if (sum == 1) return true;
			n = sum;
		}
		return false;
	}
};


// �ҵĽⷨ2��Floyd��Ȧ�㷨��ʱ�� 0 ms 100%���ռ� 5.9 MB 77.63%
class Solution {
private:
	int sumOfSquare(int n) {
		int sum = 0;
		while (n != 0) {
			int cur = n % 10;
			sum += cur * cur;
			n /= 10;
		}
		return sum;
	}
public:
	bool isHappy(int n) {
		int slow = n, fast = n;
		do {
			slow = sumOfSquare(slow);
			fast = sumOfSquare(sumOfSquare(fast));
			if (fast == 1) return true;
		} while (slow != fast);
		return false;
	}
};


// �ٷ��ⷨ����9����λƽ����Ϊ81��99����λƽ����Ϊ162��999����λƽ����Ϊ243�����Է��ִ���λ����ʼ����λƽ���ͱ�243С����999����������������λƽ���ͺ�ض�����243�ڣ�˵����λƽ����ֻ�����ֿ��ܣ�
// 1.���յõ�1
// 2.��243���µ�����ѭ��
// �����о����Է��֣�ֻ��һ��ѭ����4->16->37->58->89->145->42->20->4
// �����������ն��ᵽ��1
class Solution {
private:
	unordered_set<int> cycle{ 4, 16, 37, 58, 89, 145, 42, 20 };
	int sumOfSquare(int n) {
		int sum = 0;
		while (n != 0) {
			int cur = n % 10;
			sum += cur * cur;
			n /= 10;
		}
		return sum;
	}
public:
	bool isHappy(int n) {
		while (!cycle.count(n)) {
			n = sumOfSquare(n);
			if (n == 1) return true;
		}
		return false;
	}
};