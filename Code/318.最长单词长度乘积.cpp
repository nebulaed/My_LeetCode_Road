#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<algorithm>

using std::vector;
using std::string;
using std::unordered_map;
using std::max;
using std::cout;
using std::endl;

// LeetCode 101�ⷨ��ʱ�� 28 ms 96.95%���ռ� 15.9 MB 52.19%
// ˼·����һ������Ϊ26�Ķ��������ִ����ַ����д��ڵ���ĸ��ÿ��λ��Ϊ1��ʾ���ڸ���ĸ��Ϊ0��ʾ�����ڣ�������ַ�������ͬ��ĸ�������ǵĶ��������ְ�λ�벻Ϊ0.
class Solution {
public:
	int maxProduct(vector<string>& words) {
		// ��ϣ���ʾ�Ӷ����Ʊ�ʾ���ֵ�����ʳ��ȵ�ӳ��
		unordered_map<int, int> hashMap;
		int ret = 0;
		for (const auto& word : words) {
			int mask = 0, length = word.size();
			// ��mask���и���ĸ���򽫸���ĸ��Ӧλ����Ϊ1
			for (char ch : word) {
				mask |= 1 << (ch - 'a');
			}
			// �������Ʊ�ʾ���ֶ�Ӧ�ĵ��ʳ���ȡ���ֵ
			hashMap[mask] = max(hashMap[mask], length);
			// ���ڹ�ϣ�������еĵ��ʵĴ�����������֣���鵱ǰ�����������Ƿ����ظ���ĸ����������������ͬ��ĸ�ַ������ȳ˻�
			for (const auto& [wordMask, wordLen] : hashMap) {
				if (!(mask & wordMask)) {
					ret = max(ret, length * wordLen);
				}
			}
		}
		return ret;
	}
};

int main() {

	vector<string> input = { "abcw","baz","foo","bar","xtfn","abcdef" };

	Solution s;
	int ret = s.maxProduct(input);

	cout << ret << endl;

	system("pause");
	return 0;
}