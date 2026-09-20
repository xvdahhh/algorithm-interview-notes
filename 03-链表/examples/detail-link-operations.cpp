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

struct ListNode {
    int val;
    ListNode* next;
    explicit ListNode(int value = 0, ListNode* link = nullptr)
        : val(value), next(link) {}
};
void insertAfter(ListNode* predecessor, ListNode* node) {
    if (!predecessor || !node)
        throw invalid_argument("non-null nodes required");
    // 前提：node 是不在当前链中的独立节点。
    node->next = predecessor->next;
    predecessor->next = node;
}
ListNode* detachAfter(ListNode* predecessor) {
    if (!predecessor || !predecessor->next) return nullptr;
    ListNode* removed = predecessor->next;
    predecessor->next = removed->next;
    removed->next = nullptr;
    return removed; // 交给拥有者决定是否销毁
}
