#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
using namespace std;

// 我的解法
class Solution {
private:
    const unordered_map<char, string> hashtable = {
            {'2',"abc"},
            {'3',"def"},
            {'4',"ghi"},
            {'5',"jkl"},
            {'6',"mno"},
            {'7',"pqrs"},
            {'8',"tuv"},
            {'9',"wxyz"},
    };
public:
    vector<string> letterCombinations(string digits) {
        if (!digits.size()) return {};
        vector<string> ret = {};
        int possibility = 1;
        const int n = digits.size();
        for (int i = 0; i < n; ++i) {
            possibility *= hashtable.at(digits[i]).size();
        }
        int *index = new int[n + 1];
        index[0] = possibility;
        for (int i = 1; i < n + 1; ++i) {
            index[i] = index[i - 1] / hashtable.at(digits[i - 1]).size();
        }
        for (int i = 0; i < possibility; ++i) {
            ret.push_back("");
            for (int j = 0; j < n; ++j) {
                ret[i] += hashtable.at(digits[j])[i%index[j]/index[j+1]];
            }
        }
        delete[] index;
        return ret;
    }
};

// 官方解法
//class Solution {
//public:
//	vector<string> letterCombinations(string digits) {
//		vector<string> combinations;
//		if (digits.empty()) return combinations;
//		unordered_map<char, string> phoneMap{
//			{'2',"abc"},
//			{'3',"def"},
//			{'4',"ghi"},
//			{'5',"jkl"},
//			{'6',"mno"},
//			{'7',"pqrs"},
//			{'8',"tuv"},
//			{'9',"wxyz"}
//		};
//		string combination;
//		backtrack(combinations, phoneMap, digits, 0, combination);
//		return combinations;
//	}
//
//	// 采用递归调用来构建树的形式，在叶子结点上将combination放入combinations
//	void backtrack(vector<string>& combinations, const unordered_map<char, string>& phoneMap, const string& digits, int index, string& combination) {
//		if (index == digits.size()) {
//			combinations.push_back(combination);
//		}
//		else {
//			char digit = digits[index];
//			// 由于phoneMap是const变量，只能用.at调用
//			const string& letters = phoneMap.at(digit);
//			for (const char& letter : letters) {
//				combination.push_back(letter);
//				backtrack(combinations, phoneMap, digits, index + 1, combination);
//				combination.pop_back();
//			}
//		}
//	}
//};

int main() {
    string digits = "234";

    Solution s;
    vector<string> ret = s.letterCombinations(digits);

    cout << "[";
    for (int i = 0; i < ret.size(); ++i) {
        cout << ret[i] << ",";
    }
    cout << "]" << endl;

    return 0;
}