#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;


// 我的解法一：排序+贪心，时间O(m log m + n log n) 28 ms，空间 O(1) 17.1 MB
class Solution {
public:
	int findContentChildren(vector<int>& g, vector<int>& s) {
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());
		size_t childrenPtr = 0, cookiesPtr = 0;
		size_t childrenNum = g.size(), cookiesNum = s.size();
		while (childrenPtr < childrenNum && cookiesPtr < cookiesNum) {
			if (g[childrenPtr] <= s[cookiesPtr]) {
				++childrenPtr;
			}
			++cookiesPtr;
		}
		return childrenPtr;
	}
};