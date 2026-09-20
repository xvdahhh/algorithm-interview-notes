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
ListNode* removeNthFromEnd(ListNode* head, int k) {
    if (k <= 0) throw invalid_argument("k must be positive");
    ListNode dummy(0, head);
    ListNode* fast = &dummy;
    for (int i = 0; i < k; ++i) {
        if (!fast->next) throw out_of_range("k exceeds list length");
        fast = fast->next;
    }
    ListNode* slow = &dummy;
    while (fast->next) {
        fast = fast->next;
        slow = slow->next;
    }
    ListNode* removed = slow->next;
    slow->next = removed->next;
    removed->next = nullptr; // 不擅自释放由调用方拥有的节点
    return dummy.next;
}
