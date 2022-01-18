#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
#include<unordered_map>

using std::vector;
using std::queue;
using std::unordered_set;
using std::unordered_map;

// 我的解法：广度优先搜索，超时
class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		unordered_map<int, vector<int>> table;
		for (const auto& edge : edges) {
			int node1 = edge[0], node2 = edge[1];
			table[node1].emplace_back(node2);
			table[node2].emplace_back(node1);
		}
		unordered_set<int> path;
		vector<int> ret;
		int minDepth = INT_MAX;
		for (int i = 0; i < n; ++i) {
			queue<int> q;
			q.emplace(i);
			int depth = -1;
			while (!q.empty()) {
				size_t curSize = q.size();
				for (int j = 0; j < curSize; ++j) {
					int curr = q.front();
					path.emplace(curr);
					q.pop();
					for (int next : table[curr]) {
						if (!path.count(next)) {
							q.emplace(next);
						}
					}
				}
				++depth;
			}
			if (depth < minDepth) {
				minDepth = depth;
				ret.clear();
				ret.emplace_back(i);
			}
			else if (depth == minDepth) {
				ret.emplace_back(i);
			}
			path.clear();
		}
		return ret;
	}
};


// 看题解解法：时间 124 ms 32%，空间 50.9 MB 19%
// 思路：倒着来，从边缘的叶子节点开始，先找到所有出度为1的节点，然后把所有出度为1的节点进队列，然后不断地bfs，最后找到的就是两边同时向中间靠近的节点，那么这个中间节点就相当于把整个距离二分了，那么它当然就是到两边距离最小的点啦，也就是到其他叶子节点最近的节点了。
// 本题思路类似拓扑排序
class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		// 若只有一个节点，它就是最小高度树
		if (n == 1) return { 0 };
		// 建立各个节点的度表(连接其他节点的个数)
		vector<int> degrees(n);
		// 建立各个节点的邻接表
		vector<vector<int>> adjList(n);
		vector<int> ret;
		for (const auto& edge : edges) {
			int node1 = edge[0], node2 = edge[1];
			++degrees[node1];
			++degrees[node2];
			adjList[node1].emplace_back(node2);
			adjList[node2].emplace_back(node1);
		}
		queue<int> q;
		//把所有度为1的节点入队
		for (int i = 0; i < n; ++i) {
			if (degrees[i] == 1) {
				q.emplace(i);
			}
		}
		while (!q.empty()) {
			ret.clear();
			size_t curSize = q.size();
			while (curSize--) {
				int curr = q.front();
				q.pop();
				// 把当前节点加入结果集合，这是每次遍历完图，就会把该层的所有节点从队列中移除，相当于把原来的图剪掉一圈叶子节点，形成缩小的图
				ret.emplace_back(curr);
				for (int next : adjList[curr]) {
					// 当前节点的所有相邻节点度-1，如果相邻节点变成叶子节点，那就也放到队列里
					if (--degrees[next] == 1) {
						q.emplace(next);
					}
				}
			}
		}
		return ret;
	}
};