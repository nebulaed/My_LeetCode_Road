#include<iostream>
#include<vector>
using std::vector;
using std::cout;
using std::swap;

// 快速排序
// 基本思想是：通过一趟排序将待排元素分割成独立的两部分，其中一部分元素均比另一部分元素小，则可分别对这两部分记录继续进行排序，以达到整个序列有序的目的。
void quickSort(vector<int>& nums, int left, int right) {
	if (left + 1 >= right) return;
	int first = left, last = right - 1, key = nums[first];
	// 将key调整到比它小的数都在左边，比它大的数都在右边的位置
	// 从数组的两端交替向中间扫描
	while (first < last) {
		while (first < last && key <= nums[last]) {
			--last;
		}
		// 将比key小的元素复制到左边，原nums[first]已被key记录
		nums[first] = nums[last];
		while (first < last && nums[first] <= key) {
			++first;
		}
		// 将比key大的元素复制到右边，原nums[last]已在循环开始前的first位置
		nums[last] = nums[first];
	}
	// 将key放在nums[first]的位置
	nums[first] = key;
	// 对key左边部分进行排序
	quickSort(nums, left, first);
	// 对key右边部分进行排序
	quickSort(nums, first + 1, right);
}

// 归并排序
// 基本思想是，假设初始序列含有n个元素，则可以看成是n个有序的自序列，每个子序列的长度为1，然后两两归并
// 得到n/2个长度为2或1的有序子序列；再两两归并，如此重复，直至得到一个长度为n的有序序列为止，这种排序方法称为2路归并排序。
void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
	if (left + 1 >= right) return;
	int mid = (left + right) >> 1;
	mergeSort(nums, left, mid, temp);
	mergeSort(nums, mid, right, temp);
	int p = left, q = mid, i = left;
	while (p < mid || q < right) {
		// 将nums中元素由小到大地并入temp
		if (q >= right || (p < mid && nums[p] <= nums[q])) {
			temp[i++] = nums[p++];
		}
		else {
			temp[i++] = nums[q++];
		}
	}
	// 把temp数组复制回nums
	for (i = left; i < right; ++i) {
		nums[i] = temp[i];
	}
}

// 堆排序
// 基本思想是，将待排序列构造成一个大顶堆。此时，整个序列的最大值就是堆顶的根节点。将它移走(其实就是和堆数组的末尾元素交换)，然后将剩余的n-1个元素重新构造成一个堆，这样就会得到n个元素中的次大值。如此反复执行，就能得到一个有序序列了。
void heapAdjust(vector<int>& nums, int s, int m) {
	int temp = nums[s];
	for (int j = 2 * s + 1; j < m; j = j * 2 + 1) {
		if (j < m - 1 && nums[j] < nums[j + 1]) {
			++j;
		}
		if (temp >= nums[j]) {
			break;
		}
		nums[s] = nums[j];
		s = j;
	}
	nums[s] = temp;
}


void heapSort(vector<int>& nums, int n) {
	for (int i = n / 2 - 1; i >= 0; --i) {
		heapAdjust(nums, i, n);
	}
	for (int i = n; i > 1; --i) {
		swap(nums[0], nums[i - 1]);
		heapAdjust(nums, 0, i - 1);
	}
}

// 插入排序
// 基本思想是，将一个元素插入到已经有序的序列中，从而得到一个新的、元素数+1的有序序列
void insertionSort(vector<int>& nums, int n) {
	for (int i = 1; i < n; ++i) {
		for (int j = i; nums[j] < nums[j - 1]; --j) {
			swap(nums[j], nums[j - 1]);
		}
	}
}

// 选择排序
// 基本思想是，通过n-i此关键字间的比较，从n-i+1个记录中选出关键字最小的记录，并和第i(1<=i<=n)个记录交换。
void selectionSort(vector<int>& nums, int n) {
	int min = 0;
	for (int i = 0; i < n - 1; ++i) {
		min = i;
		for (int j = i + 1; j < n; ++j) {
			if (nums[j] < nums[min]) {
				min = j;
			}
		}
		swap(nums[min], nums[i]);
	}
}

// 冒泡排序
// 基本思想是，两两比较相邻记录的关键字，若反序则交换，直到没有反序的记录为止。
void bubbleSort(vector<int>& nums, int n) {
	bool swapped = false;
	for (int i = 1; i < n; ++i) {
		swapped = false;
		for (int j = 1; j < n - i + 1; ++j) {
			if (nums[j] < nums[j - 1]) {
				swap(nums[j], nums[j - 1]);
				swapped = true;
			}
		}
		if (!swapped) break;
	}
}

// 冒泡排序初级版：简单交换排序
void simpleBubbleSort(vector<int>& nums, int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (nums[i] > nums[j]) {
				swap(nums[i], nums[j]);
			}
		}
	}
}

int main() {
	
	vector<int> nums = { 0,9,2,4,6,8,1,7,3,5 };
	//quickSort(nums, 0, nums.size());

	//vector<int> temp(nums.size());
	//mergeSort(nums, 0, nums.size(), temp);

	heapSort(nums, nums.size());

	//insertionSort(nums, nums.size());

	//selectionSort(nums, nums.size());

	//bubbleSort(nums, nums.size());

	//simpleBubbleSort(nums, nums.size());

	for (int num : nums) {
		cout << num << ",";
	}
	cout << "\n";
	
	system("pause");
	return 0;
}