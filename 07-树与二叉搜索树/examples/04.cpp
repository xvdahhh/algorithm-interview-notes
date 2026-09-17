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
    int val; TreeNode *left=nullptr, *right=nullptr;
    explicit TreeNode(int v):val(v){}
};
TreeNode* lca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || root==p || root==q) return root;
    TreeNode* a=lca(root->left,p,q);
    TreeNode* b=lca(root->right,p,q);
    if (a && b) return root;
    return a ? a : b;
}
