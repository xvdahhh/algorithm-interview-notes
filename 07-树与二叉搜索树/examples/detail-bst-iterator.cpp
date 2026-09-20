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

class BSTIterator {
    vector<TreeNode*> pending;
    void pushLeft(TreeNode* node) {
        while (node) { pending.push_back(node); node = node->left; }
    }
public:
    explicit BSTIterator(TreeNode* root) { pushLeft(root); }
    bool hasNext() const { return !pending.empty(); }
    int next() {
        if (pending.empty()) throw out_of_range("iterator exhausted");
        TreeNode* node = pending.back(); pending.pop_back();
        pushLeft(node->right);
        return node->val;
    }
};
