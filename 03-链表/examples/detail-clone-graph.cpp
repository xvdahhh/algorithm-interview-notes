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

struct Node {
    int val;
    Node* next = nullptr;
    Node* random = nullptr;
    explicit Node(int value) : val(value) {}
};
Node* cloneReachable(Node* root) {
    // 复制从 root 沿 next/random 可达的全部节点；允许环与共享。
    // 每条非空边均需指向有效 Node；按内存分配成功模型处理。
    if (!root) return nullptr;
    unordered_map<Node*, Node*> copies;
    queue<Node*> pending;
    copies[root] = new Node(root->val);
    pending.push(root);
    auto ensureCopy = [&](Node* original) -> Node* {
        if (!original) return nullptr;
        auto it = copies.find(original);
        if (it != copies.end()) return it->second;
        Node* fresh = new Node(original->val);
        copies.emplace(original, fresh);
        pending.push(original);
        return fresh;
    };
    while (!pending.empty()) {
        Node* current = pending.front();
        pending.pop();
        Node* copy = copies.at(current);
        copy->next = ensureCopy(current->next);
        copy->random = ensureCopy(current->random);
    }
    return copies.at(root);
}
