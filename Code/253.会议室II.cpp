#include<iostream>
#include<array>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

// 我的解法：有序化，遇到左界+1，遇到右界-1，记下过程中的最大数量，时间O(n log n) 12 ms，空间O(n) 11.7 MB
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        size_t length = intervals.size();
        vector<array<int, 2>> nums(2 * length);
        for (size_t i = 0; i < length; ++i) {
            nums[2 * i][0] = intervals[i][0];
            nums[2 * i][1] = 1;
            nums[2 * i + 1][0] = intervals[i][1];
            nums[2 * i + 1][1] = 0;
        }
        sort(nums.begin(), nums.end());
        int maxNum = 0, count = 0;
        for (size_t i = 0; i < 2 * length; ++i) {
            if (nums[i][1] == 1) {
                ++count;
                maxNum = max(count, maxNum);
            }
            else --count;
        }
        return maxNum;
    }
};

// 官方解法一：优先队列，时间O(n log n) 16 ms，空间O(n) 11.5 MB
// 1.先将所有区间按照左端点单调递增的顺序排序。
// 2.初始化一个新的最小堆，将第一个会议结束时间加入到堆中。
// 3.对每个会议，检查堆顶元素是否空闲。
// 3.1 若房间空闲，则从堆顶拿出该元素，将其改为新的结束时间，放回堆中。
// 3.2 若房间不空闲。则开新房间，并加入堆中。
// 4. 处理完所有会议后，堆的大小即为开的房间数量，也就是容纳这些会议需要的最小房间数。
class Solution {
public:
    int minMeetingRooms(vector<vector<int>>& intervals) {
        sort(intervals.begin(), intervals.end());
        priority_queue<int, vector<int>, greater<int>> rooms;
        for (const auto& interval : intervals) {
            if (!rooms.empty() && rooms.top() <= interval[0]) {
                rooms.pop();
            }
            rooms.emplace(interval[1]);
        }
        return rooms.size();
    }
};
