#include<iostream>
#include<unordered_map>
#include<unordered_set>
using namespace std;

// �������ṹ
struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

// �ҵĽⷨ���ο��ٷ��ⷨһ˼·��ʱ��O(n) 16 ms���ռ�O(n) 14 MB
// ˼·���ݹ��������������������ǰ����鵱ǰ�ڵ��Ƿ�Ϊp��q����֪��T == p��T == q
// Ȼ��ʼ�ݹ飬�����ں�������ڵݹ���鵱ǰ�ڵ���������Ƿ����p��q����ʾΪf_left����ǰ�ڵ���������Ƿ����p��q����ʾΪf_right����ǰ�ڵ��������
// (f_left && f_right) || ((T == p || T == q) && (f_left || f_right))
// ��ǰ�ڵ�Ϊ��Ѱ�ҵ������������
// Ȼ���ٷ��ص�ǰ�ڵ���ߵ�ǰ�ڵ�������������������Ƿ����p��q���Թ��ϲ�ڵ��֪
class Solution {
private:
	TreeNode* ptr = nullptr;

	bool check(TreeNode* T, TreeNode* p, TreeNode* q) {
		if (T == nullptr || ptr != nullptr) return false;
		bool ret = false;
		if (T == p || T == q) ret = true;
		bool leftSon = check(T->left, p, q);
		bool rightSon = check(T->right, p, q);
		if (leftSon && rightSon || (ret && (leftSon || rightSon))) {
			ptr = T;
		}
		return ret || leftSon || rightSon;
	}
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		check(root, p, q);
		return ptr;
	}
};

// �ٷ���������ϣ��洢���ڵ㣬ʱ��O(n) 16 ms���ռ�O(n) 17.2 MB
// ˼·��1.�Ӹ��ڵ㿪ʼ�������Ŷ��������ù�ϣ���¼ÿ���ڵ�ĸ��ڵ�ָ�룬��keyΪleft��right�ڵ�ֵ��value�ŵ�ǰ�ڵ�ָ��
// 2.��p�ڵ��������洢�Ĺ�ϣ���Ͽ�ʼ�����ڵ��ƶ�ֱ��root���ù�ϣ���¼���ѷ��ʵĽڵ㣬key�Ÿýڵ�ֵ��value��true
// Ҳ���Խ��ѷ��ʵĽڵ�����ϣ����
// 3.�ٴ�q�ڵ��������Ĺ�ϣ���������ڵ��ƶ�ֱ��root��������һ����������������ķ��ʹ�ϣ��Ķ�Ӧ��value��Ϊtrue��˵������p��q�������������
// Ҳ������������һ������������Ĺ�ϣ������
class Solution {
private:
	unordered_map<int, TreeNode*> parent;
	unordered_set<int> visited;

	void dfs(TreeNode* T) {
		if (T->left != nullptr) {
			parent[T->left->val] = T;
			dfs(T->left);
		}
		if (T->right != nullptr) {
			parent[T->right->val] = T;
			dfs(T->right);
		}
	}
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		parent[root->val] = nullptr;
		dfs(root);
		while (p != nullptr) {
			visited.emplace(p->val);
			p = parent[p->val];
		}
		while (q != nullptr) {
			if (visited.count(q->val)) return q;
			q = parent[q->val];
		}
		return nullptr;
	}
};



// ���ݹٷ�˼·��д���룬ʱ��O(n) 28 ms,�ռ�O(n) 16.9 MB
class Solution {
private:
	unordered_map<int, TreeNode*> parent;
	unordered_set<int> visited;

	void dfs(TreeNode* T) {
		if (T->left != nullptr) {
			parent[T->left->val] = T;
			dfs(T->left);
		}
		if (T->right != nullptr) {
			parent[T->right->val] = T;
			dfs(T->right);
		}
	}
public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		dfs(root);
		while (true) {
			visited.emplace(p->val);
			if (p != root) {
				p = parent[p->val];
			}
			else break;
		}
		while (true) {
			if (visited.count(q->val)) return q;
			if (q != root) {
				q = parent[q->val];
			}
			else break;
		}
		return nullptr;
	}
};