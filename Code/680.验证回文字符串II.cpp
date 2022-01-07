#include<iostream>
#include<string>
using namespace std;

// �ҵĽⷨ��˫ָ�룬ʱ�� 44 ms���ռ� 19.3 MB
class Solution {
public:
	bool validPalindrome(string s) {
		bool skip = false, flag = false;
		size_t left = 0, right = s.size() - 1;
		while (left < right) {
			if (s[left] != s[right]) {
				if (skip) return false;
				skip = true;
				if (s[right - 1] == s[left] && s[left + 1] == s[right]) {
					flag = true;
					break;
				}
				else if (s[right - 1] == s[left]) --right;
				else if (s[left + 1] == s[right]) ++left;
				else return false;
			}
			else {
				++left;
				--right;
			}
		}
		if (!flag) return true;
		size_t lPtr = left + 1, rPtr = right;
		while (lPtr < rPtr) {
			if (s[lPtr] != s[rPtr]) {
				flag = false;
				break;
			}
			++lPtr;
			--rPtr;
		}
		if (flag) return true;
		--right;
		while (left < right) {
			if (s[left] != s[right]) {
				return false;
			}
			++left;
			--right;
		}
		return true;
	}
};

// �ٷ��ⷨһ��˫ָ�룬ʱ�䣬�ռ�
class Solution {
public:
	bool validPalindrome(string s) {

	}
};