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

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> pending;
    pending.push(root);
    while (!pending.empty()) {
        size_t width = pending.size();
        vector<int> level;
        for (size_t i = 0; i < width; ++i) {
            TreeNode* node = pending.front(); pending.pop();
            level.push_back(node->val);
            if (node->left) pending.push(node->left);
            if (node->right) pending.push(node->right);
        }
        result.push_back(move(level));
    }
    return result;
}
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    for (const auto& level : levelOrder(root)) result.push_back(level.back());
    return result;
}
int minimumDepth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> pending;
    pending.push(root);
    int depth = 1;
    while (!pending.empty()) {
        size_t width = pending.size();
        for (size_t i = 0; i < width; ++i) {
            TreeNode* node = pending.front(); pending.pop();
            if (!node->left && !node->right) return depth;
            if (node->left) pending.push(node->left);
            if (node->right) pending.push(node->right);
        }
        ++depth;
    }
    return 0;
}
