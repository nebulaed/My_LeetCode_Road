#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<numeric>
using namespace std;

// �ҵĽⷨ��ʱ�� 44 ms���ռ� 21.9 MB
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		vector<string> duplication = strs;
		unordered_map<string, vector<int>> hashmap;
		vector<vector<string>> ret;


		for (int i = 0; i < strs.size(); ++i) {
			sort(strs[i].begin(), strs[i].end());
			if (hashmap.count(strs[i])) {
				hashmap[strs[i]].emplace_back(i);
			}
			else {
				pair<string, vector<int>> temp(strs[i], { i });
				hashmap.insert(temp);
			}
		}
		for (auto it = hashmap.begin(); it != hashmap.end(); ++it) {
			vector<string> cur;
			for (int i = 0; i < it->second.size(); ++i) {
				cur.emplace_back(duplication[it->second[i]]);
			}
			ret.emplace_back(cur);
		}
		return ret;
	}
};

// �ٷ��ⷨ1������ ʱ��O(nk log k) 32 ms, �ռ�O(nk) 19.1 MB
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, vector<string>> mp;
		vector<vector<string>> ret;

		for (int i = 0; i < strs.size(); ++i) {
			string key = strs[i];
			sort(key.begin(), key.end());
			mp[key].emplace_back(strs[i]);
		}
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			ret.emplace_back(it->second);
		}
		return ret;
	}
};

// �ٷ��ⷨ2����������ÿ����ĸ���ֵô�����Ϊkey��ƹ�ϣ��
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		// �Զ���� array<int, 26> ���͵Ĺ�ϣ����
		auto arrayHash = [fn = hash<int>{}](const array<int, 26>& arr)->size_t {
			return accumulate(arr.begin(), arr.end(), 0u, [&](size_t acc, int num) {
				return (acc << 1) ^ fn(num);
				});
		};

		unordered_map<array<int, 26>, vector<string>, decltype(arrayHash)> mp(0, arrayHash);
		for (string& str : strs) {
			array<int, 26> counts{};
			int length = str.length();
			for (int i = 0; i < length; ++i) {
				counts[str[i] - 'a'] ++;
			}
			mp[counts].emplace_back(str);
		}
		vector<vector<string>> ans;
		for (auto it = mp.begin(); it != mp.end(); ++it) {
			ans.emplace_back(it->second);
		}
		return ans;
	}
};

// ���ƹٷ��ⷨ2�����۽ⷨ
class Solution {
public:
	vector<vector<string>> groupAnagrams(vector<string>& strs) {
		unordered_map<string, vector<string>> mp;
		vector<vector<string>> ret;

		for (auto& str : strs) {
			string count = string(26, '0');
			for (auto& c : str) {
				++count[c - 'a'];
			}
			mp[count].emplace_back(str);
		}
		for (auto& it : mp) {
			ret.emplace_back(it.second);
		}
		return ret;
	}
};

int main() {

	vector<string> strs = { "eat","tea","tan","ate","nat","bat" };

	Solution s;
	vector<vector<string>> ret = s.groupAnagrams(strs);


	cout << "[";
	for (int i = 0; i < ret.size(); ++i) {
		cout << "[";
		for (int j = 0; j < ret[i].size(); ++j) {
			cout << ret[i][j];
			if (j != ret[i].size() - 1) cout << ",";
		}
		cout << "]";
		if (i != ret.size() - 1) cout << ",";
	}
	cout << "]" << endl;

	system("pause");
	return 0;
}