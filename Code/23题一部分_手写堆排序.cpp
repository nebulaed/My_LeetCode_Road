#include<iostream>
using namespace std;

void swap(int L[], int i, int j){
    int temp = L[i];
    L[i] = L[j];
    L[j] = temp;
}

void HeapAdjust(int L[], int s, int m) {
	int temp = L[s];
	for (int j = 2 * s; j <= m; j *= 2) {
		if (j < m && L[j] < L[j + 1]) {
			++j;
		}
		if (temp >= L[j]) {
			break;
		}
		L[s] = L[j];
		s = j;
	}
	L[s] = temp;
}

void HeapSort(int L[], int length) {
	for (int i = length / 2 - 1; i >= 0; --i) {
		HeapAdjust(L, i, length);
	}
	for (int i = length - 1; i > 0; --i) {
		swap(L, 0, i);
		HeapAdjust(L, 0, i - 1);
	}
}

int main() {
	int n = 20;
	int* nums = new int[n];
	nums[0] = 234;
	nums[1] = 29;
	nums[2] = 3523;
	nums[3] = 45;
	nums[4] = 12;
	nums[5] = 657;
	nums[6] = 31;
	nums[7] = 7;
	nums[8] = 3;
	nums[9] = 7657;
	nums[10] = 12;
	nums[11] = 6546;
	nums[12] = 3453;
	nums[13] = 21;
	nums[14] = 54;
	nums[15] = 8;
	nums[16] = 234;
	nums[17] = 564;
	nums[18] = 5;
	nums[19] = 598;

	HeapSort(nums, n);

	for (int i = 0; i < n; ++i) {
		cout << nums[i] << endl;
	}

	system("pause");
	return 0;
}