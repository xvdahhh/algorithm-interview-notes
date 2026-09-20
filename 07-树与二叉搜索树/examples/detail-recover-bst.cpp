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

bool recoverSwappedBST(TreeNode* root) {
    vector<TreeNode*> pending;
    TreeNode *current = root, *previous = nullptr;
    TreeNode *first = nullptr, *second = nullptr;
    while (current || !pending.empty()) {
        while (current) { pending.push_back(current); current = current->left; }
        current = pending.back(); pending.pop_back();
        if (previous && previous->val > current->val) {
            if (!first) first = previous;
            second = current;
        }
        previous = current;
        current = current->right;
    }
    if (!first) return false;
    swap(first->val, second->val);
    return true;
}
