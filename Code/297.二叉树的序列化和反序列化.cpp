#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<list>
using namespace std;

// 二叉树结构
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// 我的解法一：层序遍历并将结果解码，失败
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

// 我的解法二：先序遍历然后再解码，时间36 ms，空间 30.2 MB
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


// 官方解法一：DFS+先序化，时间O(n) 36 ms，空间O(n) 39 MB
// TODO: 重点在学习如何不用TreeNode*&，只用TreeNode*构建二叉树
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


// 官方解法二：括号表示编码+递归下降编码，时间O(n) 32 ms，空间O(n) 49.3 MB
// 可以这么表示一棵二叉树：
// 1.若当前树为空，则表示为X
// 2.若当前树不为空，则表示为(<LEFT_SUB_TREE>)CUR_NUM(RIGHT_SUB_TREE)，其中：
//	2.1 <LEFT_SUB_TREE>是左子树序列化后的结果
//	2.2 <RIGHT_SUB_TREE>是右子树序列化后的结果
//	2.3 <CUR_NUM>是当前节点的值
// 根据该定义，后序遍历这棵二叉树即可，反序列化方法是根据定义，推导出巴科斯范式(BNF): T -> (T) num (T) | X
// 其意义是：用T代表一颗树序列化后的结果，|表示T的构成为(T) num (T) 或者 X，|左边是对T的递归定义，右边规定了递归终止的边界条件
// 因为1.T的定义中，序列中的第一个字符要么是X，要么是(，所以这个定义是不含左递归的
// 2.当我们开始解析一个字符串时，如果开头是X，我们就知道这一定是解析一个空树的结构，如果开头是(，我们就知道需要解析(T) num (T)的结构，因此这里两种开头和两种解析方法一一对应，无二义性
// 所以该文法是LL(1)型文法，它定义了一种递归的方法来反序列化，也保证了这个方法的正确性，我们可以设计一个递归函数：
// 1. 这个递归函数传入两个参数，待解析的字符串和当前待解析的位置ptr，ptr之前的位置是已经解析的，ptr和ptr后面的字符串是待解析的
// 2. 如果当前位置是X说明解析到了一棵空树，直接返回
// 3. 否则当前位置一定是(，对括号内部按照(T) num (T)的模式解析
class Codec {
private:
	inline TreeNode* parseSubtree(const string& data, size_t& ptr) {
		++ptr;	// 跳过左括号
		TreeNode* subtree = parse(data, ptr);
		++ptr;	// 跳过右括号
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