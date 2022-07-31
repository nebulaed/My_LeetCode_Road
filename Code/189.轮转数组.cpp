#include<vector>
#include<numeric>
using namespace std;

// 我的解法1：超时
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        for (int i = 0; i < k; ++i) {
            int curr = nums.back();
            nums.pop_back();
            nums.insert(nums.begin(), curr);
        }
    }
};

// 我的解法2：另建一个数组，时间 24 ms 71.87%，空间 25 MB 20.07%
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        vector<int> newNums(n);
        for (int i = 0; i < n; ++i) {
            newNums[(i + k) % n] = nums[i];
        }
        nums = move(newNums);
    }
};

// 我的解法3：原地向后挪，超时
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        for (int i = 0; i < k; ++i) {
            int curr = nums[n - 1];
            for (int j = n - 1; j > 0; --j) {
                nums[j] = nums[j - 1];
            }
            nums[0] = curr;
        }
    }
};

// 官方解法一：环状替换，时间 O(n) 28 ms 43.34%，空间 O(1) 24.2 MB 97.52%
// 使用额外数组的原因在于如果我们直接将每个数字放至它最后的位置，这样被放置位置的元素会被覆盖从而丢失。因此，从另一个角度，我们可以将被替换的元素保存在变量temp 中，从而避免了额外数组的开销。
// 我们从位置 0 开始，最初令 temp=nums[0]。根据规则，位置 0 的元素会放至(0+k) % n 的位置，令 x = (0+k) % n，此时交换 temp 和 nums[x]，完成位置 x 的更新。然后，我们考察位置 x，并交换 temp 和 nums[(x+k) % n]，从而完成下一个位置的更新。不断进行上述过程，直至回到初始位置 0。
// 容易发现，当回到初始位置 0 时，有些数字可能还没有遍历到，此时我们应该从下一个数字开始重复的过程，可是这个时候怎么才算遍历结束呢？我们不妨先考虑这样一个问题：从 0 开始不断遍历，最终回到起点 0 的过程中，我们遍历了多少个元素？
// 由于最终回到了起点，故该过程恰好走了整数数量的圈，不妨设为 a 圈；再设该过程总共遍历了 b 个元素。因此，我们有 an=bk，即 an 一定为 n,k 的公倍数。又因为我们在第一次回到起点时就结束，因此 a 要尽可能小，故 an 就是 n,k 的最小公倍数 lcm(n,k)，因此 b 就为 lcm(n,k)/k。
// 这说明单次遍历会访问到 lcm(n,k)/k 个元素。为了访问到所有的元素，我们需要进行遍历的次数为 n/(lcm(n,k)/k) = nk/lcm(n, k) = gcd(n, k)，gcd是最大公约数
// 也可以使用另外一种方式完成代码：使用单独的变量 count 跟踪当前已经访问的元素数量，当 count=n 时，结束遍历过程。
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        int count = gcd(k, n);
        for (int start = 0; start < count; ++start) {
            int curr = start;
            int prev = nums[start];
            do {
                int next = (curr + k) % n;
                swap(nums[next], prev);
                curr = next;
            } while (start != curr);
        }
    }
};

// 官方解法三：数组翻转，时间 O(n) 28 ms 43.34%，空间 O(1) 24.3 MB 81.56%
// k %= n, 先翻转整个数组，再翻转[0, k)，然后翻转[k, n)
class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int n = nums.size();
        k %= n;
        reverse(nums.begin(), nums.end());
        reverse(nums.begin(), nums.begin() + k);
        reverse(nums.begin() + k, nums.end());
    }
};