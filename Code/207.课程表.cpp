#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

// 我的解法：邻接表+拓扑排序，时间 12 ms，空间 12.8 MB
// 边表节点
struct EdgeNode {
    int adjvex;
    EdgeNode* next;
    EdgeNode(int a, EdgeNode* ptr) : adjvex(a), next(ptr) { }
};

// 顶点表节点
struct VertexNode {
    int in;
    EdgeNode* firstedge;
    VertexNode() : in(0), firstedge(nullptr) { }
};

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<VertexNode*> graphAdjList(numCourses);
        for (auto& vertex : graphAdjList) {
            VertexNode* node = new VertexNode();
            vertex = node;
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
        return count == numCourses;
    }
};

// 官方解法一：DFS，时间O(n+m) 8 ms，空间O(n+m) 13.5 MB
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> visited;
    bool valid = true;

    void dfs(int u) {
        visited[u] = 1;
        for (int v : edges[u]) {
            if (visited[v] == 0) {
                dfs(v);
                if (!valid) return;
            }
            else if (visited[v] == 1) {
                valid = false;
                return;
            }
        }
        visited[u] = 2;
    }

public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        visited.resize(numCourses);
        for (const auto& info : prerequisites) {
            edges[info[1]].emplace_back(info[0]);
        }
        for (int i = 0; i < numCourses && valid; ++i) {
            if (!visited[i]) {
                dfs(i);
            }
        }
        return valid;
    }
};


// 官方解法二：广度优先搜索，时间O(n+m) 20 ms，空间O(n+m) 13.1 MB
class Solution {
private:
    vector<vector<int>> edges;
    vector<int> indeg;
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        edges.resize(numCourses);
        indeg.resize(numCourses);
        for (const auto& info : prerequisites) {
            edges[info[1]].emplace_back(info[0]);
            ++indeg[info[0]];
        }
        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indeg[i] == 0) {
                q.emplace(i);
            }
        }
        int visited = 0;
        while (!q.empty()) {
            ++visited;
            int u = q.front();
            q.pop();
            for (int v : edges[u]) {
                --indeg[v];
                if (indeg[v] == 0) {
                    q.emplace(v);
                }
            }
        }
        return visited == numCourses;
    }
};