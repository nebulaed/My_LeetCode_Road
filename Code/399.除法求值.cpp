#include<iostream>
#include<vector>
#include<numeric>
#include<unordered_map>
#include<queue>
using namespace std;

// �ٷ����һ�����鼯��ʱ��O((N+Q) logA) 0 ms���ռ�O(A) 7.9 MB������NΪ���뷽��equations���ȣ�QΪ��ѯ����queries�ĳ��ȣ�A��equations�ﲻͬ�ַ��ĸ�����logA��ʾÿһ��ִ�кϲ������ĺ�ÿһ�β�ѯʱִ��·��ѹ����ʱ�临�Ӷ�
class UnionFind {
private:
	vector<int> parent;	// ��Ÿ��ڵ�
	vector<double> weight;	// ָ�򸸽ڵ��Ȩֵ
public:
	// Ȩ�س�ʼ��Ϊ1.0��ÿ���ڵ�ĸ��ڵ��ʼ��Ϊ�Լ�
	UnionFind(size_t n) : weight(n, 1.0) {
		parent.resize(n);
		iota(parent.begin(), parent.end(), 0);
	}
	// ·��ѹ�������ظ��ڵ�id
	int findRoot(int x) {
		// �ݹ�Ѱ�Ҹ��ڵ㣬���¸õ㵽����Ȩ��
		if (x != parent[x]) {
			int x_parent = parent[x];
			parent[x] = findRoot(parent[x]);
			weight[x] *= weight[x_parent];
		}
		return parent[x];
	}
	// ���س��������������ֵ��������-1
	double isConnected(int x, int y) {
		int rootX = findRoot(x);
		int rootY = findRoot(y);
		// ������ֵ�й�ͬ�ĸ�Ҳ���ǿ��Լ��㣬��������������ͬһ�����鼯������-1
		if (rootX == rootY) {
			return weight[x] / weight[y];
		}
		else return -1.0;
	}
	void unite(int x, int y, double val) {
		// �ֱ��ҵ����ߵĸ��ڵ�
		int rootX = findRoot(x), rootY = findRoot(y);
		// �����Ѿ�ָ��ͬһ�����ڵ�
		if (rootX == rootY) return;
		// �����ָ���ĸ�ĸ��ڵ㣬Ȩ��Ϊ[��ĸ������Ȩ��]*[��ĸ�����ӵ�ֵ]/[���ӵ�����Ȩ��]��һ��ʼ����1
		parent[rootX] = rootY;
		weight[rootX] = weight[y] * val / weight[x];
	}
};

class Solution {
public:
	vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
		// ��ʼ�����鼯
		size_t equationSize = equations.size();
		UnionFind uf(2 * equationSize);
		// ��һ����Ԥ������������ֵ��id����ӳ��
		unordered_map<string, int> hashMap;
		int id = 0;
		for (size_t i = 0; i < equationSize; ++i) {
			// ����ӣ���ĸ��ֵΪid
			const string& var1 = equations[i][0];
			const string& var2 = equations[i][1];
			if (!hashMap.count(var1)) {
				hashMap[var1] = id++;
			}
			if (!hashMap.count(var2)) {
				hashMap[var2] = id++;
			}
			// �ѷ��ӷ�ĸ���������������
			uf.unite(hashMap[var1], hashMap[var2], values[i]);
		}
		// �ڶ�������ѯ
		size_t queriesSize = queries.size();
		vector<double> ret(queriesSize, -1.0);
		for (size_t i = 0; i < queriesSize; ++i) {
			const string& var1 = queries[i][0];
			const string& var2 = queries[i][1];
			// ������ֵ����һ������equations�У����Ϊ-1�����򷵻س������
			if (hashMap.count(var1) && hashMap.count(var2)) {
				ret[i] = uf.isConnected(hashMap[var1], hashMap[var2]);
			}
		}
		return ret;
	}
};

// �ٷ�������BFS��ʱ��O(ML+Q��(L+M)) 4 ms���ռ�O(NL+M) 8.1 MB������NΪ���������MΪ��������QΪ��ѯ����queries�ĳ��ȣ�LΪ�ַ���ƽ�����ȡ�
// ���Խ��������⽨ģ��һ��ͼ������ͼ��һЩ��(����)���Լ�ĳЩ�ߵ�Ȩֵ(���������ı�ֵ)���Զ���������(��������)�����·����(���������ı�ֵ)��
// ��ˣ�������Ҫ����euqations���飬�ҳ��������в�ͬ���ַ�������ͨ����ϣ��ÿ����ͬ���ַ���ӳ���������
// �ڹ�����ͼ�󣬶����κ�һ����ѯ���Ϳ��Դ���������ͨ��BFS�����ϸ�������뵱ǰ��֮���·�����ȣ�ֱ���������յ�Ϊֹ��
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

		// ����ÿ���㣬�洢��ֱ�����ӵ������е㼰��ӦȨֵ
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
						// edge.firstΪ��y��edge.secondΪȨ��val
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


// �ٷ��ⷨ����ͼ��Floyd�㷨����ѯ���·����ʱ��O(ML+N^3+QL)���ռ�O(NL+N^2)
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