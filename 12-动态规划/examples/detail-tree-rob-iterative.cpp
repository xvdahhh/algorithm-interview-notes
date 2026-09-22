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

struct RobNode {
    int value;
    RobNode *left = nullptr, *right = nullptr;
    explicit RobNode(int v): value(v) {}
};
long long robTreeIterative(RobNode* root) {
    if (!root) return 0;
    unordered_map<RobNode*,pair<long long,long long>> state;
    vector<pair<RobNode*,bool>> stack{{root,false}};
    while (!stack.empty()) {
        auto [node,expanded] = stack.back(); stack.pop_back();
        if (!expanded) {
            stack.push_back({node,true});
            if (node->right) stack.push_back({node->right,false});
            if (node->left) stack.push_back({node->left,false});
        } else {
            auto left = node->left ? state.at(node->left) : make_pair(0LL,0LL);
            auto right = node->right ? state.at(node->right) : make_pair(0LL,0LL);
            long long skip = max(left.first,left.second)+max(right.first,right.second);
            long long take = node->value+left.first+right.first;
            state[node] = {skip,take};
        }
    }
    auto [skip,take] = state.at(root);
    return max(skip,take);
}
