#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<list>
using namespace std;

// �������ṹ
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// �ҵĽⷨһ�������������������룬ʧ��
class Codec {
private:
	void createBiTree(const string& data, size_t pos, TreeNode*& T) {
		while (data[pos] == '[' || data[pos] == ']' || data[pos] == ',') {
			++pos;
		}
		if (pos > data.size()) return;
		if (data[pos] == 'n') {
			T = nullptr;
		}
		else {
			size_t pos_end = pos;
			while (data[pos_end] >= '0' && data[pos_end] <= '9') {
				++pos_end;
			}
			int val = stoi(data.substr(pos, pos_end - pos));
			T = new TreeNode(val);
			createBiTree(data, pos_end, T->left);
			createBiTree(data, pos_end, T->right);
		}
	}
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string ret = "[";
		if (root != nullptr) {
			vector<vector<int>> levelOrder;
			vector<int> postOrder, depth;
			stack<pair<TreeNode*, int>> stk;
			int curDepth = 1;
			stk.emplace(root, curDepth);
			while (!stk.empty()) {
				root = stk.top().first;
				curDepth = stk.top().second;
				stk.pop();
				if (root == nullptr) {
					postOrder.emplace_back(-1e4);
					depth.emplace_back(curDepth);
				}
				else {
					postOrder.emplace_back(root->val);
					depth.emplace_back(curDepth);
					stk.emplace(root->left, curDepth + 1);
					stk.emplace(root->right, curDepth + 1);
				}
			}
			int nums = postOrder.size();
			for (int i = nums - 1; i >= 0; --i) {
				if (levelOrder.size() < depth[i]) levelOrder.resize(depth[i]);
				levelOrder[depth[i] - 1].emplace_back(postOrder[i]);
			}
			for (const auto& level : levelOrder) {
				for (int val : level) {
					if (val == -1e4) {
						ret += "null,";
					}
					else {
						ret += to_string(val);
						ret += ',';
					}
				}
			}
			ret.erase(ret.size() - 1);
			while (ret.substr(ret.size() - 5, 5) == ",null") {
				ret.erase(ret.size() - 5, 5);
			}
		}
		ret += "]";
		return ret;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.size() <= 2) return nullptr;
		TreeNode* root;
		createBiTree(data, 0, root);
		return root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

// �ҵĽⷨ�����������Ȼ���ٽ��룬ʱ��36 ms���ռ� 30.2 MB
class Codec {
private:
	size_t pos = 0;
	void createBiTree(const string& data, TreeNode*& T) {
		if (data[pos] == ',') ++pos;
		if (pos > data.size()) return;
		if (data[pos] == '#') {
			T = nullptr;
			++pos;
			return;
		}
		size_t pos_end = pos;
		while ((data[pos_end] >= '0' && data[pos_end] <= '9') || data[pos_end] == '-') {
			++pos_end;
		}
		int val = stoi(data.substr(pos, pos_end - pos));
		T = new TreeNode(val);
		pos = pos_end;
		createBiTree(data, T->left);
		createBiTree(data, T->right);
	}
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string ret;
		if (root != nullptr) {
			stack<TreeNode*> stk;
			TreeNode* node = root;
			while (node != nullptr || !stk.empty()) {
				while (node != nullptr) {
					ret += to_string(node->val) + ",";
					stk.emplace(node);
					node = node->left;
				}
				ret += "#,";
				node = stk.top();
				stk.pop();
				node = node->right;
			}
			ret += '#';
		}
		return ret;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		if (data.empty()) return nullptr;
		TreeNode* root = nullptr;
		createBiTree(data, root);
		return root;
	}
};


// �ٷ��ⷨһ��DFS+���򻯣�ʱ��O(n) 36 ms���ռ�O(n) 39 MB
// TODO: �ص���ѧϰ��β���TreeNode*&��ֻ��TreeNode*����������
class Codec {
private:
	void rserialize(TreeNode* root, string& str) {
		if (root == nullptr) {
			str += "null,";
		}
		else {
			str += to_string(root->val) + ",";
			rserialize(root->left, str);
			rserialize(root->right, str);
		}
	}

	TreeNode* rdeserialize(list<string>& dataArray) {
		if (dataArray.front() == "null") {
			dataArray.erase(dataArray.begin());
			return nullptr;
		}
		TreeNode* root = new TreeNode(stoi(dataArray.front()));
		dataArray.erase(dataArray.begin());
		root->left = rdeserialize(dataArray);
		root->right = rdeserialize(dataArray);
		return root;
	}
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string ret;
		rserialize(root, ret);
		return ret;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		list<string> dataArray;
		string str;
		for (const auto& ch : data) {
			if (ch == ',') {
				dataArray.emplace_back(str);
				str.clear();
			}
			else {
				str += ch;
			}
		}
		if (!str.empty()) {
			dataArray.emplace_back(str);
		}
		return rdeserialize(dataArray);
	}
};


// �ٷ��ⷨ�������ű�ʾ����+�ݹ��½����룬ʱ��O(n) 32 ms���ռ�O(n) 49.3 MB
// ������ô��ʾһ�ö�������
// 1.����ǰ��Ϊ�գ����ʾΪX
// 2.����ǰ����Ϊ�գ����ʾΪ(<LEFT_SUB_TREE>)CUR_NUM(RIGHT_SUB_TREE)�����У�
//	2.1 <LEFT_SUB_TREE>�����������л���Ľ��
//	2.2 <RIGHT_SUB_TREE>�����������л���Ľ��
//	2.3 <CUR_NUM>�ǵ�ǰ�ڵ��ֵ
// ���ݸö��壬���������ö��������ɣ������л������Ǹ��ݶ��壬�Ƶ����Ϳ�˹��ʽ(BNF): T -> (T) num (T) | X
// �������ǣ���T����һ�������л���Ľ����|��ʾT�Ĺ���Ϊ(T) num (T) ���� X��|����Ƕ�T�ĵݹ鶨�壬�ұ߹涨�˵ݹ���ֹ�ı߽�����
// ��Ϊ1.T�Ķ����У������еĵ�һ���ַ�Ҫô��X��Ҫô��(��������������ǲ�����ݹ��
// 2.�����ǿ�ʼ����һ���ַ���ʱ�������ͷ��X�����Ǿ�֪����һ���ǽ���һ�������Ľṹ�������ͷ��(�����Ǿ�֪����Ҫ����(T) num (T)�Ľṹ������������ֿ�ͷ�����ֽ�������һһ��Ӧ���޶�����
// ���Ը��ķ���LL(1)���ķ�����������һ�ֵݹ�ķ����������л���Ҳ��֤�������������ȷ�ԣ����ǿ������һ���ݹ麯����
// 1. ����ݹ麯�������������������������ַ����͵�ǰ��������λ��ptr��ptr֮ǰ��λ�����Ѿ������ģ�ptr��ptr������ַ����Ǵ�������
// 2. �����ǰλ����X˵����������һ�ÿ�����ֱ�ӷ���
// 3. ����ǰλ��һ����(���������ڲ�����(T) num (T)��ģʽ����
class Codec {
private:
	inline TreeNode* parseSubtree(const string& data, size_t& ptr) {
		++ptr;	// ����������
		TreeNode* subtree = parse(data, ptr);
		++ptr;	// ����������
		return subtree;
	}

	inline int parseInt(const string& data, size_t& ptr) {
		int x = 0, sgn = 1;
		if (!isdigit(data[ptr])) {
			sgn = -1;
			++ptr;
		}
		while (isdigit(data[ptr])) {
			x = x * 10 + data[ptr++] - '0';
		}
		return x * sgn;
	}

	TreeNode* parse(const string& data, size_t& ptr) {
		if (data[ptr] == 'X') {
			++ptr;
			return nullptr;
		}
		TreeNode* cur = new TreeNode(0);
		cur->left = parseSubtree(data, ptr);
		cur->val = parseInt(data, ptr);
		cur->right = parseSubtree(data, ptr);
		return cur;
	}
public:
	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		if (root == nullptr) return "X";
		string left = "(" + serialize(root->left) + ")";
		string right = "(" + serialize(root->right) + ")";
		return left + to_string(root->val) + right;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		size_t ptr = 0;
		return parse(data, ptr);
	}
};