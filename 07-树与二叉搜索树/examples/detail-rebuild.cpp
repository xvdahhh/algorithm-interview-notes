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

struct TreeArena {
private:
    deque<TreeNode> nodes;
public:
    TreeArena() = default;
    TreeArena(const TreeArena&) = delete;
    TreeArena& operator=(const TreeArena&) = delete;
    TreeNode* make(int value) {
        nodes.emplace_back(value);
        return &nodes.back();
    }
};

TreeNode* rebuildPreIn(const vector<int>& preorder, const vector<int>& inorder,
                       TreeArena& arena) {
    if (preorder.size() != inorder.size() || preorder.size() > 100000)
        throw invalid_argument("size mismatch or input too large");
    int n = (int)preorder.size();
    unordered_map<int, int> position;
    for (int i = 0; i < n; ++i)
        if (!position.emplace(inorder[i], i).second)
            throw invalid_argument("duplicate inorder key");
    unordered_set<int> seen;
    for (int value : preorder)
        if (!position.count(value) || !seen.insert(value).second)
            throw invalid_argument("different keys or duplicate preorder key");
    int cursor = 0;
    function<TreeNode*(int, int)> build = [&](int l, int r) -> TreeNode* {
        if (l == r) return nullptr;
        if (cursor == n) throw invalid_argument("preorder exhausted");
        int value = preorder[cursor++];
        int middle = position.at(value);
        if (middle < l || middle >= r) throw invalid_argument("inconsistent traversals");
        TreeNode* root = arena.make(value);
        root->left = build(l, middle);
        root->right = build(middle + 1, r);
        return root;
    };
    TreeNode* root = build(0, n);
    if (cursor != n) throw invalid_argument("unused preorder entries");
    return root;
}
