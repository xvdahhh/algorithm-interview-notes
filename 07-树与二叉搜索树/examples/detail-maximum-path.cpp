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

optional<long long> maximumPathSum(TreeNode* root) {
    if (!root) return nullopt;
    long long best = LLONG_MIN;
    function<long long(TreeNode*)> gain = [&](TreeNode* node) -> long long {
        if (!node) return 0;
        long long left = max(0LL, gain(node->left));
        long long right = max(0LL, gain(node->right));
        best = max(best, (long long)node->val + left + right);
        return (long long)node->val + max(left, right);
    };
    gain(root);
    return best;
}
