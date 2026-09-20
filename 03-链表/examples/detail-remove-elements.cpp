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
ListNode* removeElements(ListNode* head, int target) {
    ListNode dummy(0, head);
    ListNode* predecessor = &dummy;
    while (predecessor->next) {
        ListNode* candidate = predecessor->next;
        if (candidate->val == target) {
            predecessor->next = candidate->next;
            candidate->next = nullptr; // 仅摘除，由节点拥有者管理生命周期
        } else {
            predecessor = candidate;
        }
    }
    return dummy.next;
}
