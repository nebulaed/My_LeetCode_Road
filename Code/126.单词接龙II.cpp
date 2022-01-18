#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<unordered_set>
#include<unordered_map>

using std::string;
using std::vector;
using std::set;
using std::unordered_map;
using std::unordered_set;


// LeetCode 101�ⷨ��ʱ�� 4 ms 98.29%���ռ� 8.4 MB 86.18%
// ˼·������ʼ�ַ�������ֹ�ַ������Լ����ʱ������е��ַ�������ɽڵ㡣�������ַ���ֻ��һ���ַ���ͬ����ô������ʹ�ù�����������������ʼ�ڵ㵽��ֹ�ڵ����̾��롣
// Сtrick: ����ʼ�ڵ����ֹ�ڵ�ֱ���й������������ÿ��ֻ��չ��ǰ��ڵ������ٵ���һ�ˣ��������Լ����������ܽ������
// ����������ͨ���������ؽ����п��ܵ�·��
class Solution {
private:
	void dfs(const string& src, const string& dst, unordered_map<string, vector<string>>& next, vector<string>& path, vector<vector<string>>& ret) {
		if (src == dst) {
			ret.emplace_back(path);
			return;
		}
		for (const auto& s : next[src]) {
			path.emplace_back(s);
			dfs(s, dst, next, path, ret);
			path.pop_back();
		}
	}
public:
	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
		// �޸�;���������ַ���
		vector<vector<string>> ret;
		// ��wordList������string�ŵ���ϣ������ȥ�ز��������
		unordered_set<string> dict(wordList.begin(), wordList.end());
		auto it = dict.find(endWord);
		// ��wordList��û���յ㣬�϶�������Ҫ��
		if (it == dict.end()) return ret;
		// ��dict��ɾȥ�����յ�
		else dict.erase(it);
		dict.erase(beginWord);
		// �����������ʹ�õĶ���q1��q2��Ϊ�������ʹ�ù�ϣ����
		unordered_set<string> q1{ beginWord }, q2{ endWord }, q;
		// ��ǰ�ַ����ĸı�һ���ַ�����dict�ڵ������ַ���
		unordered_map<string, vector<string>> next;
		// reversedΪfalseʱ�Ǵ���㿪ʼ��������Ϊtrueʱ�Ǵ��յ㿪ʼ������
		bool reversed = false, found = false;
		string s;
		while (!q1.empty()) {
			// Ϊ����ֱ�Ӹ�q1��q2����ֵ��Ҳ���ù�ϣ����
			q.clear();
			for (const auto& word : q1) {
				// Ϊ��̽�ı�һ���ַ�����ַ�����Ҫ�´���һ���ַ���
				s = word;
				// ���ַ���������ַ��������ı�
				for (size_t i = 0; i < s.size(); ++i) {
					// ����ԭ�ַ�
					char ch = s[i];
					//���Խ�s[i]��Ϊ�����ַ�
					for (int j = 0; j < 26; ++j) {
						s[i] = j + 'a';
						// ������һ�˳�����·���������s��˵��������������·��������
						if (q2.count(s)) {
							// reversedΪ��˵����ǰq2Ϊ���������Ķ��У�����Ӧ���޸ĺ��sΪkey���޸�ǰ��wordΪval����Ϊ������·����key->val
							// ��֮��q1Ϊ���������Ķ��У�����Ӧ���޸�ǰwordΪkey���޸ĺ�sΪval����Ϊ������·����key->val
							reversed ? next[s].emplace_back(word) : next[word].emplace_back(s);
							found = true;
						}
						// ��dict����s��·��q�з��뵱ǰ�ַ���s
						if (dict.count(s)) {
							// reversedΪ��˵����ǰq2Ϊ���������Ķ��У�����Ӧ���޸ĺ��sΪkey���޸�ǰ��wordΪval����Ϊ������·����key->val
							// ��֮��q1Ϊ���������Ķ��У�����Ӧ���޸�ǰwordΪkey���޸ĺ�sΪval����Ϊ������·����key->val
							reversed ? next[s].emplace_back(word) : next[word].emplace_back(s);
							q.emplace(s);
						}
					}
					// ��s[i]��Ϊԭ�ַ�
					s[i] = ch;
				}
			}
			if (found) break;
			for (const auto& word : q) {
				dict.erase(word);
			}
			// ����ǰ��ڵ���q.size()С�ڵ�����һ�������ĵ�ǰ�ڵ���q2.size()�������ӵ�ǰ������
			if (q.size() <= q2.size()) {
				q1 = q;
			}
			// �������һ�˿�ʼ����
			else {
				reversed = !reversed;
				q1 = q2;
				q2 = q;
			}
		}
		// ͨ��DFS+���ݹ������п���·��
		if (found) {
			vector<string> path = { beginWord };
			dfs(beginWord, endWord, next, path, ret);
		}
		return ret;
	}
};

// �ҵĽⷨ�������������+�������������ʧ��
//class Solution {
//private:
//	void dfs(const string& src, const string& dst, unordered_map<string, vector<string>>& nextWord, vector<string>& path, set<vector<string>>& ret) {
//		if (src == dst) {
//			ret.emplace(path);
//			return;
//		}
//		for (const auto& word : nextWord[src]) {
//			path.emplace_back(word);
//			dfs(word, dst, nextWord, path, ret);
//			path.pop_back();
//		}
//	}
//public:
//	vector<vector<string>> findLadders(string beginWord, string endWord, vector<string>& wordList) {
//		set<vector<string>> ret;
//		unordered_set<string> wordDict(wordList.begin(), wordList.end());
//		auto it = wordDict.find(endWord);
//		if (it == wordDict.end()) return {};
//		else wordDict.erase(it);
//		wordDict.erase(beginWord);
//		unordered_set<string> curQ{ beginWord }, bakQ{ endWord };
//		unordered_map<string, vector<string>> nextWord;
//		bool found = false, reversed = false;
//		while (!curQ.empty()) {
//			unordered_set<string> nextQ;
//			for (const auto& word : curQ) {
//				string str = word;
//				for (size_t i = 0; i < str.size(); ++i) {
//					char ch = str[i];
//					for (const auto& contrast : wordDict) {
//						if (str[i] == contrast[i]) continue;
//						str[i] = contrast[i];
//						if (wordDict.count(str) && !nextQ.count(str)) {
//							reversed ? nextWord[str].emplace_back(word) : nextWord[word].emplace_back(str);
//							nextQ.emplace(str);
//						}
//					}
//					bool start = true;
//					for (const auto& contrast : bakQ) {
//						if (str[i] == contrast[i] && !start) continue;
//						start = false;
//						str[i] = contrast[i];
//						if (bakQ.count(str)) {
//							reversed ? nextWord[str].emplace_back(word) : nextWord[word].emplace_back(str);
//							found = true;
//						}
//					}
//					str[i] = ch;
//				}
//			}
//			if (found) break;
//			for (const auto& word : nextQ) {
//				wordDict.erase(word);
//			}
//			if (nextQ.size() <= bakQ.size()) {
//				curQ = nextQ;
//			}
//			else {
//				reversed = !reversed;
//				curQ = bakQ;
//				bakQ = nextQ;
//			}
//		}
//		if (found) {
//			vector<string> path = { beginWord };
//			dfs(beginWord, endWord, nextWord, path, ret);
//		}
//		return vector<vector<string>>(ret.begin(), ret.end());
//	}
//};


int main() {

	using std::cout;

	string beginWord = "qa", endWord = "sq";
	vector<string> wordList = { "si","go","se","cm","so","ph","mt","db","mb","sb","kr","ln","tm","le","av","sm","ar","ci","ca","br","ti","ba","to","ra","fa","yo","ow","sn","ya","cr","po","fe","ho","ma","re","or","rn","au","ur","rh","sr","tc","lt","lo","as","fr","nb","yb","if","pb","ge","th","pm","rb","sh","co","ga","li","ha","hz","no","bi","di","hi","qa","pi","os","uh","wm","an","me","mo","na","la","st","er","sc","ne","mn","mi","am","ex","pt","io","be","fm","ta","tb","ni","mr","pa","he","lr","sq","ye" };


	Solution s;
	vector<vector<string>> ret = s.findLadders(beginWord, endWord, wordList);

	for (const auto& path : ret) {
		cout << "[";
		for (const auto& word : path) {
			cout << word << ",";
		}
		cout << "]\n";
	}

	system("pause");
	return 0;
}