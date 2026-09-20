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

bool insertBST(TreeNode*& root, TreeNode* fresh) {
    if (!fresh || fresh->left || fresh->right)
        throw invalid_argument("detached leaf required");
    TreeNode** link = &root;
    while (*link) {
        if ((*link)->val == fresh->val) return false;
        link = fresh->val < (*link)->val ? &(*link)->left : &(*link)->right;
    }
    *link = fresh;
    return true;
}
TreeNode* detachBST(TreeNode*& root, int key) {
    TreeNode** link = &root;
    while (*link && (*link)->val != key)
        link = key < (*link)->val ? &(*link)->left : &(*link)->right;
    if (!*link) return nullptr;
    TreeNode* victim = *link;
    if (!victim->left) *link = victim->right;
    else if (!victim->right) *link = victim->left;
    else {
        TreeNode** nextLink = &victim->right;
        while ((*nextLink)->left) nextLink = &(*nextLink)->left;
        TreeNode* successor = *nextLink;
        *nextLink = successor->right;
        successor->left = victim->left;
        successor->right = victim->right;
        *link = successor;
    }
    victim->left = victim->right = nullptr;
    return victim;
}
