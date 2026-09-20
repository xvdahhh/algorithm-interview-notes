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

bool validBSTIterative(TreeNode* root) {
    vector<TreeNode*> pending;
    TreeNode* current = root;
    optional<int> previous;
    while (current || !pending.empty()) {
        while (current) { pending.push_back(current); current = current->left; }
        current = pending.back(); pending.pop_back();
        if (previous && current->val <= *previous) return false;
        previous = current->val;
        current = current->right;
    }
    return true;
}
TreeNode* searchBST(TreeNode* root, int key) {
    while (root && root->val != key)
        root = key < root->val ? root->left : root->right;
    return root;
}
optional<int> kthSmallestBST(TreeNode* root, int k) {
    if (k <= 0) return nullopt;
    vector<TreeNode*> pending;
    TreeNode* current = root;
    while (current || !pending.empty()) {
        while (current) { pending.push_back(current); current = current->left; }
        current = pending.back(); pending.pop_back();
        if (--k == 0) return current->val;
        current = current->right;
    }
    return nullopt;
}
