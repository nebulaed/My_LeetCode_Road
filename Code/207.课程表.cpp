#include<iostream>
#include<vector>
#include<stack>
using namespace std;

// �ҵĽⷨ���ڽӱ�+��������ʱ�� 12 ms���ռ� 12.8 MB
// �߱�ڵ�
struct EdgeNode {
	int adjvex;
	EdgeNode* next;
	EdgeNode(int a, EdgeNode* ptr) : adjvex(a), next(ptr) { }
};

// �����ڵ�
struct VertexNode {
	int in;
	EdgeNode* firstedge;
	VertexNode() : in(0), firstedge(nullptr) { }
};

class Solution {
public:
	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		vector<VertexNode*> graphAdjList;
		for (int i = 0; i < numCourses; ++i) {
			VertexNode* node = new VertexNode();
			graphAdjList.emplace_back(node);
		}
		for (const auto& line : prerequisites) {
			EdgeNode* node = new EdgeNode(line[0], graphAdjList[line[1]]->firstedge);
			graphAdjList[line[1]]->firstedge = node;
			++graphAdjList[line[0]]->in;
		}
		int count = 0;
		stack<int> stk;
		for (int i = 0; i < numCourses; ++i) {
			if (0 == graphAdjList[i]->in) {
				stk.emplace(i);
			}
		}
		while (!stk.empty()) {
			int start = stk.top();
			stk.pop();
			++count;
			for (EdgeNode* ptr = graphAdjList[start]->firstedge; ptr != nullptr; ptr = ptr->next) {
				int k = ptr->adjvex;
				if (--graphAdjList[k]->in == 0) {
					stk.emplace(k);
				}
			}
		}
		if (count < numCourses) return false;
		else return true;
	}
};