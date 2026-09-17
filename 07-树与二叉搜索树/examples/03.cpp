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
bool validRange(TreeNode* p, long long lo, long long hi) {
    if (!p) return true;
    if (p->val<=lo || p->val>=hi) return false;
    return validRange(p->left,lo,p->val)
        && validRange(p->right,p->val,hi);
}
bool isValidBST(TreeNode* root) {
    return validRange(root,LLONG_MIN,LLONG_MAX);
}
