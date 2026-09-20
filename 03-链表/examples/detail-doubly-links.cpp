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

struct DoubleNode {
    int key;
    DoubleNode* prev = nullptr;
    DoubleNode* next = nullptr;
    explicit DoubleNode(int value) : key(value) {}
};
void unlinkNode(DoubleNode* node) {
    // 前提：node 为已挂接的非哨兵节点，prev/next 均有效。
    DoubleNode* before = node->prev;
    DoubleNode* after = node->next;
    before->next = after;
    after->prev = before;
    node->prev = nullptr;
    node->next = nullptr;
}
void insertAfter(DoubleNode* before, DoubleNode* node) {
    // 前提：before->next 有效；node 是不在链中的独立节点。
    DoubleNode* after = before->next;
    node->prev = before;
    node->next = after;
    before->next = node;
    after->prev = node;
}
