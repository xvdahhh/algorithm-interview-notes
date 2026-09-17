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
    int val; TreeNode *left=nullptr,*right=nullptr;
    explicit TreeNode(int v):val(v){}
};
pair<long long,long long> robState(TreeNode* p) {
    if(!p) return {0,0}; // {skip,take}
    auto [ls,lt]=robState(p->left);
    auto [rs,rt]=robState(p->right);
    long long skip=max(ls,lt)+max(rs,rt);
    long long take=p->val+ls+rs;
    return {skip,take};
}
long long robTree(TreeNode* root) {
    auto [skip,take]=robState(root);
    return max(skip,take);
}
