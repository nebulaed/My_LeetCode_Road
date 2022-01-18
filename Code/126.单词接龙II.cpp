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


// LeetCode 101解法：时间 4 ms 98.29%，空间 8.4 MB 86.18%
// 思路：将起始字符串、终止字符串、以及单词表里所有的字符串想象成节点。若两个字符串只有一个字符不同，那么相连。使用广度优先搜索，求得起始节点到终止节点的最短距离。
// 小trick: 从起始节点和终止节点分别进行广度优先搜索，每次只延展当前层节点数最少的那一端，这样可以减少搜索的总结点数。
// 搜索结束后，通过回溯来重建所有可能的路径
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
		// 修改途径的所有字符串
		vector<vector<string>> ret;
		// 将wordList里所有string放到哈希集合中去重并方便查找
		unordered_set<string> dict(wordList.begin(), wordList.end());
		auto it = dict.find(endWord);
		// 若wordList中没有终点，肯定不符合要求
		if (it == dict.end()) return ret;
		// 从dict中删去起点和终点
		else dict.erase(it);
		dict.erase(beginWord);
		// 广度优先搜索使用的队列q1和q2，为方便查找使用哈希集合
		unordered_set<string> q1{ beginWord }, q2{ endWord }, q;
		// 当前字符串的改变一个字符后在dict内的所有字符串
		unordered_map<string, vector<string>> next;
		// reversed为false时是从起点开始的搜索，为true时是从终点开始的搜索
		bool reversed = false, found = false;
		string s;
		while (!q1.empty()) {
			// 为了能直接跟q1，q2交换值，也采用哈希集合
			q.clear();
			for (const auto& word : q1) {
				// 为试探改变一个字符后的字符串，要新创建一个字符串
				s = word;
				// 对字符串中逐个字符尝试做改变
				for (size_t i = 0; i < s.size(); ++i) {
					// 保存原字符
					char ch = s[i];
					//尝试将s[i]改为任意字符
					for (int j = 0; j < 26; ++j) {
						s[i] = j + 'a';
						// 若另外一端出发的路径里出现了s，说明从两端搜索的路径相遇了
						if (q2.count(s)) {
							// reversed为真说明当前q2为从起点出发的队列，所以应以修改后的s为key，修改前的word为val，因为起点出发路径是key->val
							// 反之则q1为从起点出发的队列，所以应以修改前word为key，修改后s为val，因为起点出发路径是key->val
							reversed ? next[s].emplace_back(word) : next[word].emplace_back(s);
							found = true;
						}
						// 若dict中有s，路径q中放入当前字符串s
						if (dict.count(s)) {
							// reversed为真说明当前q2为从起点出发的队列，所以应以修改后的s为key，修改前的word为val，因为起点出发路径是key->val
							// 反之则q1为从起点出发的队列，所以应以修改前word为key，修改后s为val，因为起点出发路径是key->val
							reversed ? next[s].emplace_back(word) : next[word].emplace_back(s);
							q.emplace(s);
						}
					}
					// 将s[i]改为原字符
					s[i] = ch;
				}
			}
			if (found) break;
			for (const auto& word : q) {
				dict.erase(word);
			}
			// 若当前层节点数q.size()小于等于另一端搜索的当前节点数q2.size()，继续从当前端搜索
			if (q.size() <= q2.size()) {
				q1 = q;
			}
			// 否则从另一端开始搜索
			else {
				reversed = !reversed;
				q1 = q2;
				q2 = q;
			}
		}
		// 通过DFS+回溯构建所有可行路径
		if (found) {
			vector<string> path = { beginWord };
			dfs(beginWord, endWord, next, path, ret);
		}
		return ret;
	}
};

// 我的解法：广度优先搜索+深度优先搜索，失败
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