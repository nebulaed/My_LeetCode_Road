#include<iostream>
#include<vector>
using namespace std;

// �ҵĽⷨ��̰���㷨��ʱ�� 12 ms���ռ� 19.8 MB
class Solution {
public:
	bool canPlaceFlowers(vector<int>& flowerbed, int n) {
		size_t length = flowerbed.size();
		int count = 0;
		for (size_t i = 0; i < length; ++i) {
			// ����ǰλ��Ϊ0��ǰ��λ��Ϊ0�Һ���λ��Ϊ0�����ֻ�
			if ((i == 0 || !flowerbed[i - 1]) && (i == length - 1 || !flowerbed[i + 1]) && !flowerbed[i]) {
				++count;
				++flowerbed[i];
			}
			if (count >= n) return true;
		}
		return false;
	}
};