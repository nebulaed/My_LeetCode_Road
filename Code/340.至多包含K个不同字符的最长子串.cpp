#include<iostream>
#include<string>
#include<algorithm>
#include<unordered_map>
using namespace std;

// �ҵĽⷨ��˫ָ��(��������)��ʱ�� 4 ms 98.72%���ռ� 6.7 MB 98.72%
class Solution {
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		// ��kΪ0���κγ��ȴ���0���ַ����������ַ����඼����0����˷���0
		if (k == 0) return k;
		// �ַ���ϣ����ʾ���ַ��Ƿ�����ڻ���������
		bool flag[128]{};
		// �ַ����ִ�����ϣ����ʾ���ַ��ڻ��������ڳ��ֵĴ���
		int charFreq[128]{};
		// cnt��ʾ�����������ַ�����������left��ʾ����������˵㣬maxSize��ʾ��󴰿ڳ���
		int cnt = 0, left = 0, maxSize = 0;
		for (int right = 0; right < s.size(); ++right) {
			// ���������Ҷ˵���ַ��ĳ��ִ���+1
			++charFreq[s[right]];
			// ���Ҷ˵��ַ��ڻ���������֮ǰû���ֹ�
			if (!flag[s[right]]) {
				// �����������ַ�������+1
				++cnt;
				// ���������ַ�������Ϊ��
				flag[s[right]] = true;
			}
			// ���Ҷ˵���s���һ��λ�û�s��һ���ַ�δ�ڻ��������г���
			if (right == s.size() - 1 || !flag[s[right + 1]]) {
				while (cnt == k) {
					// ����ǰ�������ڴ�С����maxSize������maxSize
					maxSize = max(maxSize, right - left + 1);
					// ����˵����ƺ�ԭ��˵��ַ����ٳ����ڻ��������ڣ������������ַ�������-1�������������ַ�������Ϊ��
					if (--charFreq[s[left]] == 0) {
						--cnt;
						flag[s[left]] = false;
					}
					++left;
				}
			}
		}
		// ��maxSizeΪ0��˵��s�ڵ��ַ�����С��k������sȫ��
		return maxSize == 0 ? s.size() : maxSize;
	}
};

// �ҵĽⷨ���Ż���ʱ�� 0 ms 100%���ռ� 6.9 MB 85.29%
class Solution {
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		// ��kΪ0���κγ��ȴ���0���ַ����������ַ����඼����0����˷���0
		if (k == 0) return k;
		// �ַ����ִ�����ϣ����ʾ���ַ��ڻ��������ڳ��ֵĴ���
		int charFreq[128]{};
		// cnt��ʾ�����������ַ�����������left��ʾ����������˵㣬maxSize��ʾ��󴰿ڳ���
		int cnt = 0, left = 0, maxSize = 0;
		for (int right = 0; right < s.size(); ++right) {
			// ���������Ҷ˵���ַ��ĳ��ִ���+1
			if (charFreq[s[right]]++ == 0) {
				// ���Ҷ˵��ַ��ڻ���������֮ǰû���ֹ��������������ַ�������+1
				++cnt;
			}
			// ���Ҷ˵���s���һ��λ�û�s��һ���ַ�δ�ڻ��������г���
			if (right == s.size() - 1 || charFreq[s[right + 1]] == 0) {
				while (cnt == k) {
					// ����ǰ�������ڴ�С����maxSize������maxSize
					maxSize = max(maxSize, right - left + 1);
					// ����˵����ƺ�ԭ��˵��ַ����ٳ����ڻ��������ڣ������������ַ�������-1�������������ַ�������Ϊ��
					if (--charFreq[s[left]] == 0) {
						--cnt;
					}
					++left;
				}
			}
		}
		// ��maxSizeΪ0��˵��s�ڵ��ַ�����С��k������sȫ��
		return maxSize == 0 ? s.size() : maxSize;
	}
};

// �ٷ��ⷨһ����������+��ϣ��ʱ��O(nk) 12 ms 67.40%���ռ�O(k) 8 MB 36.81%��kΪ�����ַ���s���ַ�������
class Solution {
public:
	int lengthOfLongestSubstringKDistinct(string s, int k) {
		int n = s.size();
		// ��s����Ϊ0��kΪ0������0
		if (n * k == 0) return 0;

		int left = 0, right = 0;
		// �����ַ��ڻ������������һ�γ��ֵ�λ��
		unordered_map<char, int> hashMap;
		int maxLen = 1;
		while (right < n) {
			// ��s[right]�����ڻ��������ڵ����һ��λ�ø���Ϊright��Ȼ��right�Լ�1
			hashMap[s[right++]] = right;
			// �������������ַ������Ѿ�����k
			if (hashMap.size() == k + 1) {
				// �ҳ�hashMap���ڻ������������һ�γ����ǰ���ַ���λ��
				int del_idx = min_element(hashMap.begin(), hashMap.end(), [](const auto& lhs, const auto& rhs) {
					return lhs.second < rhs.second;
					})->second;
				// ɾ��hashMap�ڶ�Ӧ�ַ�
				hashMap.erase(s[del_idx]);
				left = del_idx + 1;
			}
			maxLen = max(maxLen, right - left);
		}
		return maxLen;
	}
};