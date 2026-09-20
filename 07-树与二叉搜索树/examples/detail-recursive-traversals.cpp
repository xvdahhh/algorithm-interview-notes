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

struct Traversals {
    vector<int> preorder, inorder, postorder;
};
void visitOrders(TreeNode* node, Traversals& result) {
    if (!node) return;
    result.preorder.push_back(node->val);
    visitOrders(node->left, result);
    result.inorder.push_back(node->val);
    visitOrders(node->right, result);
    result.postorder.push_back(node->val);
}
Traversals recursiveOrders(TreeNode* root) {
    Traversals result;
    visitOrders(root, result);
    return result;
}
