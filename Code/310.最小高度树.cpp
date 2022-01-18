#include<iostream>
#include<vector>
#include<queue>
#include<unordered_set>
#include<unordered_map>

using std::vector;
using std::queue;
using std::unordered_set;
using std::unordered_map;

// �ҵĽⷨ�����������������ʱ
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


// �����ⷨ��ʱ�� 124 ms 32%���ռ� 50.9 MB 19%
// ˼·�����������ӱ�Ե��Ҷ�ӽڵ㿪ʼ�����ҵ����г���Ϊ1�Ľڵ㣬Ȼ������г���Ϊ1�Ľڵ�����У�Ȼ�󲻶ϵ�bfs������ҵ��ľ�������ͬʱ���м俿���Ľڵ㣬��ô����м�ڵ���൱�ڰ�������������ˣ���ô����Ȼ���ǵ����߾�����С�ĵ�����Ҳ���ǵ�����Ҷ�ӽڵ�����Ľڵ��ˡ�
// ����˼·������������
class Solution {
public:
	vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
		// ��ֻ��һ���ڵ㣬��������С�߶���
		if (n == 1) return { 0 };
		// ���������ڵ�Ķȱ�(���������ڵ�ĸ���)
		vector<int> degrees(n);
		// ���������ڵ���ڽӱ�
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
		//�����ж�Ϊ1�Ľڵ����
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
				// �ѵ�ǰ�ڵ���������ϣ�����ÿ�α�����ͼ���ͻ�Ѹò�����нڵ�Ӷ������Ƴ����൱�ڰ�ԭ����ͼ����һȦҶ�ӽڵ㣬�γ���С��ͼ
				ret.emplace_back(curr);
				for (int next : adjList[curr]) {
					// ��ǰ�ڵ���������ڽڵ��-1��������ڽڵ���Ҷ�ӽڵ㣬�Ǿ�Ҳ�ŵ�������
					if (--degrees[next] == 1) {
						q.emplace(next);
					}
				}
			}
		}
		return ret;
	}
};