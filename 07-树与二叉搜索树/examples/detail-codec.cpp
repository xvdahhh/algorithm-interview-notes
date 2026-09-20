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

struct TreeArena {
private:
    deque<TreeNode> nodes;
public:
    TreeArena() = default;
    TreeArena(const TreeArena&) = delete;
    TreeArena& operator=(const TreeArena&) = delete;
    TreeNode* make(int value) {
        nodes.emplace_back(value);
        return &nodes.back();
    }
};

vector<string> serializeTree(TreeNode* root) {
    vector<string> tokens;
    function<void(TreeNode*)> encode = [&](TreeNode* node) {
        if (!node) { tokens.push_back("#"); return; }
        tokens.push_back(to_string(node->val));
        encode(node->left);
        encode(node->right);
    };
    encode(root);
    return tokens;
}
TreeNode* deserializeTree(const vector<string>& tokens, TreeArena& arena) {
    if (tokens.empty() || tokens.size() > 200001)
        throw invalid_argument("invalid token count");
    vector<optional<int>> parsed;
    long long slots = 1;
    for (const string& token : tokens) {
        if (slots == 0) throw invalid_argument("trailing token");
        --slots;
        if (token == "#") parsed.push_back(nullopt);
        else {
            size_t used = 0;
            int value = stoi(token, &used);
            if (used != token.size()) throw invalid_argument("bad integer token");
            parsed.push_back(value);
            slots += 2;
        }
    }
    if (slots != 0) throw invalid_argument("missing child token");
    size_t cursor = 0;
    function<TreeNode*()> decode = [&]() -> TreeNode* {
        optional<int> value = parsed[cursor++];
        if (!value) return nullptr;
        TreeNode* node = arena.make(*value);
        node->left = decode();
        node->right = decode();
        return node;
    };
    return decode();
}
