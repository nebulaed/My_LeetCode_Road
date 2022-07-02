struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

// 我的解法参考官方解法一：时间 O(n^2) 36 ms 22.83%，空间 O(n) 15.5 MB 51.17%
// 对每个节点，都考虑所有从该节点开始向下求和的结果，关键点在于辅助函数向下传递(目标和-当前节点值)，当发现当前节点值等于上一层传下来的sum时，说明找到一条路径满足要求
class Solution {
private:
    int dfs(TreeNode* T, long long sum){
        if (!T) return 0;
        int cnt = 0, curr = T->val;
        if (curr == sum) ++cnt;
        cnt += dfs(T->left, sum - curr);
        cnt += dfs(T->right, sum - curr);
        return cnt;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        return root ? dfs(root, targetSum) + pathSum(root->left, targetSum) + pathSum(root->right, targetSum) : 0;
    }
};

// 官方解法二：前缀和，时间 O(n) 8 ms 97.93%，空间 O(n) 18.7 MB 23.55%
class Solution {
private:
    unordered_map<long long, int> prefixFreq;
    int targetSum;
    int dfs(TreeNode* T, long long prefix){
        if (!T) return 0;
        int cnt = 0;
        // 前缀和更新为加上当前节点值
        prefix += T->val;
        // 检查该前缀和减去目标和的结果是否在prefixFreq中出现过，若出现过，满足要求的路径数目增加对应频次
        auto it = prefixFreq.find(prefix - targetSum);
        if (it != prefixFreq.end()){
            cnt += it->second;
        }
        // 该前缀和出现次数+1
        ++prefixFreq[prefix];
        cnt += dfs(T->left, prefix);
        cnt += dfs(T->right, prefix);
        // 该前缀和出现次数-1
        --prefixFreq[prefix];   //不用检查是否为0进行擦除，否则时间空间会更差
        return cnt;
    }
public:
    int pathSum(TreeNode* root, int targetSum) {
        // 预先存下路径和为0的情况出现1次
        prefixFreq.emplace(0, 1);
        this->targetSum = targetSum;
        return dfs(root, 0);
    }
};