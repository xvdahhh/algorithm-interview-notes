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

struct TreeSummary {
    int height = 0;
    int nodes = 0;
    int diameter = 0;
    bool balanced = true;
};
TreeSummary summarizeTree(TreeNode* root) {
    if (!root) return {};
    TreeSummary left = summarizeTree(root->left);
    TreeSummary right = summarizeTree(root->right);
    TreeSummary result;
    result.height = 1 + max(left.height, right.height);
    result.nodes = 1 + left.nodes + right.nodes;
    result.balanced = left.balanced && right.balanced &&
                      abs(left.height - right.height) <= 1;
    result.diameter = max({left.diameter, right.diameter, left.height + right.height});
    return result;
}
