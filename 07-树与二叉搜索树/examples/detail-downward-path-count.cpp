#include <algorithm>
#include <array>
#include <cassert>
#include <climits>
#include <cstdint>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <list>
#include <numeric>
#include <optional>
#include <queue>
#include <random>
#include <stack>
#include <stdexcept>
#include <string>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode *left = nullptr, *right = nullptr;
    explicit TreeNode(int value) : val(value) {}
};

long long countDownwardPaths(TreeNode* root, long long target) {
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    function<long long(TreeNode*, long long)> dfs =
        [&](TreeNode* node, long long prefix) -> long long {
            if (!node) return 0;
            prefix += node->val;
            long long result = 0;
            auto found = frequency.find(prefix - target);
            if (found != frequency.end()) result += found->second;
            ++frequency[prefix];
            result += dfs(node->left, prefix);
            result += dfs(node->right, prefix);
            auto current = frequency.find(prefix);
            if (--current->second == 0) frequency.erase(current);
            return result;
        };
    return dfs(root, 0);
}
