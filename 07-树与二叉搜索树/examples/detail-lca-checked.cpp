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

struct LcaReport {
    unsigned mask = 0; // bit 0: p found, bit 1: q found
    TreeNode* ancestor = nullptr;
};
LcaReport reportLca(TreeNode* node, TreeNode* p, TreeNode* q) {
    if (!node) return {};
    LcaReport left = reportLca(node->left, p, q);
    LcaReport right = reportLca(node->right, p, q);
    unsigned own = (node == p ? 1U : 0U) | (node == q ? 2U : 0U);
    unsigned mask = left.mask | right.mask | own;
    TreeNode* ancestor = left.ancestor ? left.ancestor : right.ancestor;
    if (!ancestor && mask == 3U) ancestor = node;
    return {mask, ancestor};
}
TreeNode* lcaChecked(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!p || !q) return nullptr;
    LcaReport result = reportLca(root, p, q);
    return result.mask == 3U ? result.ancestor : nullptr;
}
TreeNode* lcaBSTChecked(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!p || !q) return nullptr;
    auto containsIdentity = [&](TreeNode* target) {
        TreeNode* node = root;
        while (node && node->val != target->val)
            node = target->val < node->val ? node->left : node->right;
        return node == target;
    };
    if (!containsIdentity(p) || !containsIdentity(q)) return nullptr;
    int low = min(p->val, q->val), high = max(p->val, q->val);
    while (root) {
        if (root->val < low) root = root->right;
        else if (root->val > high) root = root->left;
        else return root;
    }
    return nullptr;
}
