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

vector<vector<int>> rootLeafPaths(TreeNode* root, long long target) {
    vector<vector<int>> answer;
    vector<int> path;
    function<void(TreeNode*, long long)> dfs = [&](TreeNode* node, long long sum) {
        if (!node) return;
        path.push_back(node->val);
        sum += node->val;
        if (!node->left && !node->right) {
            if (sum == target) answer.push_back(path);
        } else {
            dfs(node->left, sum);
            dfs(node->right, sum);
        }
        path.pop_back();
    };
    dfs(root, 0);
    return answer;
}
