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
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};
struct ListEntry { ListNode* node; size_t row; };
struct LaterListEntry {
    bool operator()(const ListEntry& a, const ListEntry& b) const {
        if (a.node->val != b.node->val) return a.node->val > b.node->val;
        return a.row > b.row;
    }
};
ListNode* mergeSortedLists(const vector<ListNode*>& heads) {
    priority_queue<ListEntry, vector<ListEntry>, LaterListEntry> pending;
    for (size_t row = 0; row < heads.size(); ++row)
        if (heads[row]) pending.push({heads[row], row});
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!pending.empty()) {
        auto [node, row] = pending.top(); pending.pop();
        ListNode* successor = node->next;
        if (successor) pending.push({successor, row});
        tail->next = node;
        tail = node;
        tail->next = nullptr;
    }
    return dummy.next;
}
