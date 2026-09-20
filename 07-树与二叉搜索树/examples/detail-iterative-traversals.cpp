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

vector<int> preorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    vector<TreeNode*> pending{root};
    while (!pending.empty()) {
        TreeNode* node = pending.back(); pending.pop_back();
        result.push_back(node->val);
        if (node->right) pending.push_back(node->right);
        if (node->left) pending.push_back(node->left);
    }
    return result;
}
vector<int> postorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    vector<pair<TreeNode*, bool>> pending{{root, false}};
    while (!pending.empty()) {
        auto [node, expanded] = pending.back(); pending.pop_back();
        if (expanded) { result.push_back(node->val); continue; }
        pending.push_back({node, true});
        if (node->right) pending.push_back({node->right, false});
        if (node->left) pending.push_back({node->left, false});
    }
    return result;
}
