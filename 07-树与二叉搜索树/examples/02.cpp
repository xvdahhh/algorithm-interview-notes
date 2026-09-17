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
int balancedHeight(TreeNode* node) {
    if (!node) return 0;
    int l=balancedHeight(node->left);
    if (l==-1) return -1;
    int r=balancedHeight(node->right);
    if (r==-1 || abs(l-r)>1) return -1;
    return 1+max(l,r);
}
bool isBalanced(TreeNode* root) {
    return balancedHeight(root)!=-1;
}
