#include<iostream>
#include<vector>
using std::vector;
using std::cout;
using std::swap;

// ��������
// ����˼���ǣ�ͨ��һ�����򽫴���Ԫ�طָ�ɶ����������֣�����һ����Ԫ�ؾ�����һ����Ԫ��С����ɷֱ���������ּ�¼�������������Դﵽ�������������Ŀ�ġ�
void quickSort(vector<int>& nums, int left, int right) {
	if (left + 1 >= right) return;
	int first = left, last = right - 1, key = nums[first];
	// ��key����������С����������ߣ���������������ұߵ�λ��
	// ����������˽������м�ɨ��
	while (first < last) {
		while (first < last && key <= nums[last]) {
			--last;
		}
		// ����keyС��Ԫ�ظ��Ƶ���ߣ�ԭnums[first]�ѱ�key��¼
		nums[first] = nums[last];
		while (first < last && nums[first] <= key) {
			++first;
		}
		// ����key���Ԫ�ظ��Ƶ��ұߣ�ԭnums[last]����ѭ����ʼǰ��firstλ��
		nums[last] = nums[first];
	}
	// ��key����nums[first]��λ��
	nums[first] = key;
	// ��key��߲��ֽ�������
	quickSort(nums, left, first);
	// ��key�ұ߲��ֽ�������
	quickSort(nums, first + 1, right);
}

// �鲢����
// ����˼���ǣ������ʼ���к���n��Ԫ�أ�����Կ�����n������������У�ÿ�������еĳ���Ϊ1��Ȼ�������鲢
// �õ�n/2������Ϊ2��1�����������У��������鲢������ظ���ֱ���õ�һ������Ϊn����������Ϊֹ���������򷽷���Ϊ2·�鲢����
void mergeSort(vector<int>& nums, int left, int right, vector<int>& temp) {
	if (left + 1 >= right) return;
	int mid = (left + right) >> 1;
	mergeSort(nums, left, mid, temp);
	mergeSort(nums, mid, right, temp);
	int p = left, q = mid, i = left;
	while (p < mid || q < right) {
		// ��nums��Ԫ����С����ز���temp
		if (q >= right || (p < mid && nums[p] <= nums[q])) {
			temp[i++] = nums[p++];
		}
		else {
			temp[i++] = nums[q++];
		}
	}
	// ��temp���鸴�ƻ�nums
	for (i = left; i < right; ++i) {
		nums[i] = temp[i];
	}
}

// ������
// ����˼���ǣ����������й����һ���󶥶ѡ���ʱ���������е����ֵ���ǶѶ��ĸ��ڵ㡣��������(��ʵ���ǺͶ������ĩβԪ�ؽ���)��Ȼ��ʣ���n-1��Ԫ�����¹����һ���ѣ������ͻ�õ�n��Ԫ���еĴδ�ֵ����˷���ִ�У����ܵõ�һ�����������ˡ�
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

// ��������
// ����˼���ǣ���һ��Ԫ�ز��뵽�Ѿ�����������У��Ӷ��õ�һ���µġ�Ԫ����+1����������
void insertionSort(vector<int>& nums, int n) {
	for (int i = 1; i < n; ++i) {
		for (int j = i; nums[j] < nums[j - 1]; --j) {
			swap(nums[j], nums[j - 1]);
		}
	}
}

// ѡ������
// ����˼���ǣ�ͨ��n-i�˹ؼ��ּ�ıȽϣ���n-i+1����¼��ѡ���ؼ�����С�ļ�¼�����͵�i(1<=i<=n)����¼������
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

// ð������
// ����˼���ǣ������Ƚ����ڼ�¼�Ĺؼ��֣��������򽻻���ֱ��û�з���ļ�¼Ϊֹ��
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

// ð����������棺�򵥽�������
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