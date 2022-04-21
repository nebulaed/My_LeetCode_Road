#include<iostream>
#include<vector>
#include<numeric>
#include<unordered_map>
#include<queue>
using namespace std;

// 官方题解一：并查集，时间O((N+Q) logA) 0 ms，空间O(A) 7.9 MB，其中N为输入方程equations长度，Q为查询方程queries的长度，A是equations里不同字符的个数，logA表示每一次执行合并操作的和每一次查询时执行路径压缩的时间复杂度
class UnionFind {
private:
    vector<int> parent;	// 存放父节点
    vector<double> weight;	// 指向父节点的权值
public:
    // 权重初始化为1.0，每个节点的父节点初始化为自己
    UnionFind(size_t n) : weight(n, 1.0) {
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
    }
    // 路径压缩，返回根节点id
    int findRoot(int x) {
        // 递归寻找根节点，更新该点到根的权重
        if (x != parent[x]) {
            int x_parent = parent[x];
            parent[x] = findRoot(parent[x]);
            weight[x] *= weight[x_parent];
        }
        return parent[x];
    }
    // 返回除法结果。若两个值不存在则-1
    double isConnected(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        // 若两个值有共同的根也就是可以计算，则算结果。否则不在同一个并查集，返回-1
        if (rootX == rootY) {
            return weight[x] / weight[y];
        }
        else return -1.0;
    }
    void unite(int x, int y, double val) {
        // 分别找到两者的根节点
        int rootX = findRoot(x), rootY = findRoot(y);
        // 两者已经指向同一个根节点
        if (rootX == rootY) return;
        // 令分子指向分母的根节点，权重为[分母到根的权重]*[分母除分子的值]/[分子到根的权重]，一开始都是1
        parent[rootX] = rootY;
        weight[rootX] = weight[y] * val / weight[x];
    }
};

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        // 初始化并查集
        size_t equationSize = equations.size();
        UnionFind uf(2 * equationSize);
        // 第一步：预处理，将变量的值和id进行映射
        unordered_map<string, int> hashMap;
        int id = 0;
        for (size_t i = 0; i < equationSize; ++i) {
            // 存分子，分母，值为id
            const string& var1 = equations[i][0];
            const string& var2 = equations[i][1];
            if (!hashMap.count(var1)) {
                hashMap[var1] = id++;
            }
            if (!hashMap.count(var2)) {
                hashMap[var2] = id++;
            }
            // 把分子分母用有向边连接起来
            uf.unite(hashMap[var1], hashMap[var2], values[i]);
        }
        // 第二步：查询
        size_t queriesSize = queries.size();
        vector<double> ret(queriesSize, -1.0);
        for (size_t i = 0; i < queriesSize; ++i) {
            const string& var1 = queries[i][0];
            const string& var2 = queries[i][1];
            // 若两个值至少一个不在equations中，结果为-1，否则返回除法结果
            if (hashMap.count(var1) && hashMap.count(var2)) {
                ret[i] = uf.isConnected(hashMap[var1], hashMap[var2]);
            }
        }
        return ret;
    }
};

// 官方题解二：BFS，时间O(ML+Q·(L+M)) 4 ms，空间O(NL+M) 8.1 MB，其中N为点的数量，M为边数量，Q为查询方程queries的长度，L为字符串平均长度。
// 可以将整个问题建模成一张图：给定图中一些点(变量)，以及某些边的权值(两个变量的比值)，试对任意两点(两个变量)求出其路径长(两个变量的比值)。
// 因此，首先需要遍历euqations数组，找出其中所有不同的字符串，并通过哈希表将每个不同的字符串映射成整数。
// 在构建完图后，对于任何一个查询，就可以从起点出发，通过BFS，不断更新起点与当前点之间的路径长度，直到搜索到终点为止。
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int nvars = 0;
        unordered_map<string, int> variables;
        size_t n = equations.size();
        for (size_t i = 0; i < n; ++i) {
            if (variables.find(equations[i][0]) == variables.end()) {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.end()) {
                variables[equations[i][1]] = nvars++;
            }
        }

        // 对于每个点，存储其直接连接到的所有点及对应权值
        vector<vector<pair<int, double>>> edges(nvars);
        for (size_t i = 0; i < n; ++i) {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            edges[va].emplace_back(vb, values[i]);
            edges[vb].emplace_back(va, 1.0 / values[i]);
        }

        vector<double> ret;
        for (const auto& query : queries) {
            double result = -1.0;
            if (variables.find(query[0]) != variables.end() && variables.find(query[1]) != variables.end()) {
                int ia = variables[query[0]], ib = variables[query[1]];
                if (ia == ib) result = 1.0;
                else {
                    queue<int> points;
                    points.emplace(ia);
                    vector<double> ratios(nvars, -1.0);
                    ratios[ia] = 1.0;

                    while (!points.empty() && ratios[ib] < 0) {
                        int x = points.front();
                        points.pop();
                        // edge.first为点y，edge.second为权重val
                        for (const auto edge : edges[x]) {
                            if (ratios[edge.first] < 0) {
                                ratios[edge.first] = ratios[x] * edge.second;
                                points.emplace(edge.first);
                            }
                        }
                    }
                    result = ratios[ib];
                }
            }
            ret.emplace_back(result);
        }
        return ret;
    }
};


// 官方解法二：图的Floyd算法，查询最短路径，时间O(ML+N^3+QL)，空间O(NL+N^2)
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int nvars = 0;
        unordered_map<string, int> variables;

        size_t n = equations.size();
        for (size_t i = 0; i < n; i++) {
            if (variables.find(equations[i][0]) == variables.end()) {
                variables[equations[i][0]] = nvars++;
            }
            if (variables.find(equations[i][1]) == variables.end()) {
                variables[equations[i][1]] = nvars++;
            }
        }
        vector<vector<double>> graph(nvars, vector<double>(nvars, -1.0));
        for (size_t i = 0; i < n; i++) {
            int va = variables[equations[i][0]], vb = variables[equations[i][1]];
            graph[va][vb] = values[i];
            graph[vb][va] = 1.0 / values[i];
        }

        for (size_t k = 0; k < nvars; k++) {
            for (size_t i = 0; i < nvars; i++) {
                for (size_t j = 0; j < nvars; j++) {
                    if (graph[i][k] > 0 && graph[k][j] > 0) {
                        graph[i][j] = graph[i][k] * graph[k][j];
                    }
                }
            }
        }

        vector<double> ret;
        for (const auto& q : queries) {
            double result = -1.0;
            if (variables.find(q[0]) != variables.end() && variables.find(q[1]) != variables.end()) {
                int ia = variables[q[0]], ib = variables[q[1]];
                if (graph[ia][ib] > 0) {
                    result = graph[ia][ib];
                }
            }
            ret.emplace_back(result);
        }
        return ret;
    }
};