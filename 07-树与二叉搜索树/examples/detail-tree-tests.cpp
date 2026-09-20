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

vector<int> preorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    vector<TreeNode*> pending{root};
    while (!pending.empty()) {
        TreeNode* node = pending.back(); pending.pop_back();
        result.push_back(node->val);
        if (node->right) pending.push_back(node->right);
        if (node->left) pending.push_back(node->left);
    }
    return result;
}
vector<int> postorderIterative(TreeNode* root) {
    vector<int> result;
    if (!root) return result;
    vector<pair<TreeNode*, bool>> pending{{root, false}};
    while (!pending.empty()) {
        auto [node, expanded] = pending.back(); pending.pop_back();
        if (expanded) { result.push_back(node->val); continue; }
        pending.push_back({node, true});
        if (node->right) pending.push_back({node->right, false});
        if (node->left) pending.push_back({node->left, false});
    }
    return result;
}

vector<vector<int>> levelOrder(TreeNode* root) {
    vector<vector<int>> result;
    if (!root) return result;
    queue<TreeNode*> pending;
    pending.push(root);
    while (!pending.empty()) {
        size_t width = pending.size();
        vector<int> level;
        for (size_t i = 0; i < width; ++i) {
            TreeNode* node = pending.front(); pending.pop();
            level.push_back(node->val);
            if (node->left) pending.push(node->left);
            if (node->right) pending.push(node->right);
        }
        result.push_back(move(level));
    }
    return result;
}
vector<int> rightSideView(TreeNode* root) {
    vector<int> result;
    for (const auto& level : levelOrder(root)) result.push_back(level.back());
    return result;
}
int minimumDepth(TreeNode* root) {
    if (!root) return 0;
    queue<TreeNode*> pending;
    pending.push(root);
    int depth = 1;
    while (!pending.empty()) {
        size_t width = pending.size();
        for (size_t i = 0; i < width; ++i) {
            TreeNode* node = pending.front(); pending.pop();
            if (!node->left && !node->right) return depth;
            if (node->left) pending.push(node->left);
            if (node->right) pending.push(node->right);
        }
        ++depth;
    }
    return 0;
}

struct TreeSummary {
    int height = 0;
    int nodes = 0;
    int diameter = 0;
    bool balanced = true;
};
TreeSummary summarizeTree(TreeNode* root) {
    if (!root) return {};
    TreeSummary left = summarizeTree(root->left);
    TreeSummary right = summarizeTree(root->right);
    TreeSummary result;
    result.height = 1 + max(left.height, right.height);
    result.nodes = 1 + left.nodes + right.nodes;
    result.balanced = left.balanced && right.balanced &&
                      abs(left.height - right.height) <= 1;
    result.diameter = max({left.diameter, right.diameter, left.height + right.height});
    return result;
}

optional<long long> maximumPathSum(TreeNode* root) {
    if (!root) return nullopt;
    long long best = LLONG_MIN;
    function<long long(TreeNode*)> gain = [&](TreeNode* node) -> long long {
        if (!node) return 0;
        long long left = max(0LL, gain(node->left));
        long long right = max(0LL, gain(node->right));
        best = max(best, (long long)node->val + left + right);
        return (long long)node->val + max(left, right);
    };
    gain(root);
    return best;
}

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

long long countDownwardPaths(TreeNode* root, long long target) {
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    function<long long(TreeNode*, long long)> dfs =
        [&](TreeNode* node, long long prefix) -> long long {
            if (!node) return 0;
            prefix += node->val;
            long long result = 0;
            auto found = frequency.find(prefix - target);
            if (found != frequency.end()) result += found->second;
            ++frequency[prefix];
            result += dfs(node->left, prefix);
            result += dfs(node->right, prefix);
            auto current = frequency.find(prefix);
            if (--current->second == 0) frequency.erase(current);
            return result;
        };
    return dfs(root, 0);
}

bool validBSTIterative(TreeNode* root) {
    vector<TreeNode*> pending;
    TreeNode* current = root;
    optional<int> previous;
    while (current || !pending.empty()) {
        while (current) { pending.push_back(current); current = current->left; }
        current = pending.back(); pending.pop_back();
        if (previous && current->val <= *previous) return false;
        previous = current->val;
        current = current->right;
    }
    return true;
}
TreeNode* searchBST(TreeNode* root, int key) {
    while (root && root->val != key)
        root = key < root->val ? root->left : root->right;
    return root;
}
optional<int> kthSmallestBST(TreeNode* root, int k) {
    if (k <= 0) return nullopt;
    vector<TreeNode*> pending;
    TreeNode* current = root;
    while (current || !pending.empty()) {
        while (current) { pending.push_back(current); current = current->left; }
        current = pending.back(); pending.pop_back();
        if (--k == 0) return current->val;
        current = current->right;
    }
    return nullopt;
}

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

class BSTIterator {
    vector<TreeNode*> pending;
    void pushLeft(TreeNode* node) {
        while (node) { pending.push_back(node); node = node->left; }
    }
public:
    explicit BSTIterator(TreeNode* root) { pushLeft(root); }
    bool hasNext() const { return !pending.empty(); }
    int next() {
        if (pending.empty()) throw out_of_range("iterator exhausted");
        TreeNode* node = pending.back(); pending.pop_back();
        pushLeft(node->right);
        return node->val;
    }
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

struct LcaReport {
    unsigned mask = 0; // bit 0: p found, bit 1: q found
    TreeNode* ancestor = nullptr;
};
LcaReport reportLca(TreeNode* node, TreeNode* p, TreeNode* q) {
    if (!node) return {};
    LcaReport left = reportLca(node->left, p, q);
    LcaReport right = reportLca(node->right, p, q);
    unsigned own = (node == p ? 1U : 0U) | (node == q ? 2U : 0U);
    unsigned mask = left.mask | right.mask | own;
    TreeNode* ancestor = left.ancestor ? left.ancestor : right.ancestor;
    if (!ancestor && mask == 3U) ancestor = node;
    return {mask, ancestor};
}
TreeNode* lcaChecked(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!p || !q) return nullptr;
    LcaReport result = reportLca(root, p, q);
    return result.mask == 3U ? result.ancestor : nullptr;
}
TreeNode* lcaBSTChecked(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!p || !q) return nullptr;
    auto containsIdentity = [&](TreeNode* target) {
        TreeNode* node = root;
        while (node && node->val != target->val)
            node = target->val < node->val ? node->left : node->right;
        return node == target;
    };
    if (!containsIdentity(p) || !containsIdentity(q)) return nullptr;
    int low = min(p->val, q->val), high = max(p->val, q->val);
    while (root) {
        if (root->val < low) root = root->right;
        else if (root->val > high) root = root->left;
        else return root;
    }
    return nullptr;
}

TreeNode* rebuildPreIn(const vector<int>& preorder, const vector<int>& inorder,
                       TreeArena& arena) {
    if (preorder.size() != inorder.size() || preorder.size() > 100000)
        throw invalid_argument("size mismatch or input too large");
    int n = (int)preorder.size();
    unordered_map<int, int> position;
    for (int i = 0; i < n; ++i)
        if (!position.emplace(inorder[i], i).second)
            throw invalid_argument("duplicate inorder key");
    unordered_set<int> seen;
    for (int value : preorder)
        if (!position.count(value) || !seen.insert(value).second)
            throw invalid_argument("different keys or duplicate preorder key");
    int cursor = 0;
    function<TreeNode*(int, int)> build = [&](int l, int r) -> TreeNode* {
        if (l == r) return nullptr;
        if (cursor == n) throw invalid_argument("preorder exhausted");
        int value = preorder[cursor++];
        int middle = position.at(value);
        if (middle < l || middle >= r) throw invalid_argument("inconsistent traversals");
        TreeNode* root = arena.make(value);
        root->left = build(l, middle);
        root->right = build(middle + 1, r);
        return root;
    };
    TreeNode* root = build(0, n);
    if (cursor != n) throw invalid_argument("unused preorder entries");
    return root;
}

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

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
vector<TreeNode*> checkedNodes(TreeNode* root) {
    vector<TreeNode*> result;
    if (!root) return result;
    unordered_set<TreeNode*> seen;
    vector<TreeNode*> pending{root};
    while (!pending.empty()) {
        TreeNode* node = pending.back(); pending.pop_back();
        require(seen.insert(node).second, "cycle or shared child");
        result.push_back(node);
        if (node->right) pending.push_back(node->right);
        if (node->left) pending.push_back(node->left);
    }
    return result;
}
int bruteMinimumDepth(TreeNode* node) {
    if (!node) return 0;
    if (!node->left) return 1 + bruteMinimumDepth(node->right);
    if (!node->right) return 1 + bruteMinimumDepth(node->left);
    return 1 + min(bruteMinimumDepth(node->left), bruteMinimumDepth(node->right));
}
long long bruteDownward(TreeNode* root, long long target) {
    function<long long(TreeNode*, long long)> from =
        [&](TreeNode* node, long long sum) -> long long {
            if (!node) return 0;
            sum += node->val;
            return (sum == target) + from(node->left, sum) + from(node->right, sum);
        };
    long long count = 0;
    for (TreeNode* node : checkedNodes(root)) count += from(node, 0);
    return count;
}
pair<int, optional<long long>> bruteAllPaths(TreeNode* root) {
    auto nodes = checkedNodes(root);
    if (nodes.empty()) return {0, nullopt};
    unordered_map<TreeNode*, int> id;
    for (int i = 0; i < (int)nodes.size(); ++i) id[nodes[i]] = i;
    vector<vector<int>> edges(nodes.size());
    for (int i = 0; i < (int)nodes.size(); ++i) {
        for (TreeNode* child : {nodes[i]->left, nodes[i]->right}) {
            if (!child) continue;
            int j = id.at(child);
            edges[i].push_back(j); edges[j].push_back(i);
        }
    }
    int diameter = 0;
    long long best = LLONG_MIN;
    for (int start = 0; start < (int)nodes.size(); ++start) {
        vector<int> distance(nodes.size(), -1);
        vector<long long> sum(nodes.size());
        queue<int> pending;
        distance[start] = 0; sum[start] = nodes[start]->val; pending.push(start);
        while (!pending.empty()) {
            int u = pending.front(); pending.pop();
            diameter = max(diameter, distance[u]);
            best = max(best, sum[u]);
            for (int v : edges[u]) if (distance[v] == -1) {
                distance[v] = distance[u] + 1;
                sum[v] = sum[u] + nodes[v]->val;
                pending.push(v);
            }
        }
    }
    return {diameter, best};
}
TreeNode* bruteLca(TreeNode* root, TreeNode* p, TreeNode* q) {
    if (!root || !p || !q) return nullptr;
    unordered_map<TreeNode*, TreeNode*> parent;
    parent[root] = nullptr;
    for (TreeNode* node : checkedNodes(root)) {
        if (node->left) parent[node->left] = node;
        if (node->right) parent[node->right] = node;
    }
    if (!parent.count(p) || !parent.count(q)) return nullptr;
    unordered_set<TreeNode*> ancestors;
    for (; p; p = parent.at(p)) ancestors.insert(p);
    for (; q; q = parent.at(q)) if (ancestors.count(q)) return q;
    return nullptr;
}
int main() {
    require(serializeTree(nullptr) == vector<string>{"#"}, "empty serialization");
    require(!maximumPathSum(nullptr), "empty path");
    require(countDownwardPaths(nullptr, 0) == 0, "empty path count");
    TreeNode one(1), a(-1), b(-1);
    one.left = &a; one.right = &b;
    require(countDownwardPaths(&one, 0) == 2, "branch rollback");
    require(countDownwardPaths(&one, 0) == 2, "repeated call reset");
    TreeNode negative(-7);
    require(maximumPathSum(&negative) == optional<long long>{-7}, "negative path");
    TreeNode boundary(INT_MIN);
    require(validBSTIterative(&boundary), "minimum int BST key");
    for (const auto& bad : vector<vector<string>>{{}, {"1","#"}, {"#","#"}, {"x","#","#"}}) {
        TreeArena owner;
        bool rejected = false;
        try { (void)deserializeTree(bad, owner); }
        catch (const exception&) { rejected = true; }
        require(rejected, "invalid serialization");
    }
    {
        TreeArena owner;
        bool rejected = false;
        try { (void)rebuildPreIn({1,2,3}, {3,1,2}, owner); }
        catch (const invalid_argument&) { rejected = true; }
        require(rejected, "inconsistent traversal ranges");
    }
    mt19937 rng(20260920);
    uniform_int_distribution<int> length(0, 12), value(-5, 5);
    for (int run = 0; run < 500; ++run) {
        TreeArena owner;
        TreeNode* root = nullptr;
        int n = length(rng);
        vector<pair<TreeNode*, bool>> slots;
        for (int i = 0; i < n; ++i) {
            TreeNode* fresh = owner.make(value(rng));
            if (!root) root = fresh;
            else {
                size_t pick = rng() % slots.size();
                auto [parent, right] = slots[pick];
                if (right) parent->right = fresh; else parent->left = fresh;
                slots[pick] = slots.back(); slots.pop_back();
            }
            slots.push_back({fresh, false});
            slots.push_back({fresh, true});
        }
        auto nodes = checkedNodes(root);
        auto orders = recursiveOrders(root);
        require(preorderIterative(root) == orders.preorder, "preorder");
        require(postorderIterative(root) == orders.postorder, "postorder");
        auto levels = levelOrder(root);
        TreeSummary summary = summarizeTree(root);
        require(summary.nodes == n && summary.height == (int)levels.size(), "summary");
        auto allPaths = bruteAllPaths(root);
        require(summary.diameter == allPaths.first, "diameter");
        require(maximumPathSum(root) == allPaths.second, "maximum path");
        require(minimumDepth(root) == bruteMinimumDepth(root), "minimum depth");
        long long target = value(rng);
        require(countDownwardPaths(root, target) == bruteDownward(root, target), "path count");
        vector<vector<int>> expectedPaths;
        vector<int> path;
        function<void(TreeNode*)> enumerate = [&](TreeNode* node) {
            if (!node) return;
            path.push_back(node->val);
            if (!node->left && !node->right &&
                accumulate(path.begin(), path.end(), 0LL) == target)
                expectedPaths.push_back(path);
            enumerate(node->left); enumerate(node->right);
            path.pop_back();
        };
        enumerate(root);
        require(rootLeafPaths(root, target) == expectedPaths, "root leaf paths");
        TreeArena cloneOwner;
        auto tokens = serializeTree(root);
        TreeNode* clone = deserializeTree(tokens, cloneOwner);
        require(serializeTree(clone) == tokens, "serialization round trip");
        unordered_set<TreeNode*> original(nodes.begin(), nodes.end());
        for (TreeNode* copy : checkedNodes(clone))
            require(!original.count(copy), "clone identity must differ");
        TreeNode outsider(root ? root->val : 0);
        require(lcaChecked(root, root, &outsider) == nullptr, "missing target identity");
        if (!nodes.empty()) {
            TreeNode* p = nodes[rng() % nodes.size()];
            TreeNode* q = nodes[rng() % nodes.size()];
            require(lcaChecked(root, p, q) == bruteLca(root, p, q), "LCA");
            require(lcaChecked(root, p, p) == p, "same LCA target");
        }
        TreeArena bstOwner;
        TreeNode* bst = nullptr;
        vector<int> keys(n);
        iota(keys.begin(), keys.end(), -6);
        shuffle(keys.begin(), keys.end(), rng);
        for (int key : keys) require(insertBST(bst, bstOwner.make(key)), "insert");
        require(validBSTIterative(bst), "inserted BST valid");
        sort(keys.begin(), keys.end());
        BSTIterator iterator(bst);
        vector<int> iterated;
        while (iterator.hasNext()) iterated.push_back(iterator.next());
        require(iterated == keys, "iterator order");
        require(!kthSmallestBST(bst, 0) && !kthSmallestBST(bst, n + 1), "invalid rank");
        for (int k = 1; k <= n; ++k)
            require(kthSmallestBST(bst, k) == optional<int>{keys[k - 1]}, "kth rank");
        auto bstOrders = recursiveOrders(bst);
        TreeArena rebuiltOwner;
        TreeNode* rebuilt = rebuildPreIn(bstOrders.preorder, bstOrders.inorder, rebuiltOwner);
        require(serializeTree(rebuilt) == serializeTree(bst), "reconstruction");
        if (n >= 2) {
            TreeNode* p = searchBST(bst, keys.front());
            TreeNode* q = searchBST(bst, keys.back());
            require(lcaBSTChecked(bst, p, q) == bruteLca(bst, p, q), "BST LCA");
            swap(p->val, q->val);
            require(recoverSwappedBST(bst) && validBSTIterative(bst), "recover");
        }
        shuffle(keys.begin(), keys.end(), rng);
        for (int key : keys) {
            TreeNode* expected = searchBST(bst, key);
            TreeNode* detached = detachBST(bst, key);
            require(detached == expected && detached &&
                    !detached->left && !detached->right, "detach identity");
            (void)checkedNodes(bst);
            require(validBSTIterative(bst) && !searchBST(bst, key), "delete structure");
        }
        require(bst == nullptr, "delete all");
    }
    cout << "All chapter 7 checks passed" << endl;
}
