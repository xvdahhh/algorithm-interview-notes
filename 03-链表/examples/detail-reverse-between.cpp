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
ListNode* reverseBetween(ListNode* head, int left, int right) {
    if (left < 1 || right < left)
        throw invalid_argument("invalid positions");
    ListNode* probe = head;
    for (int i = 0; i < right; ++i) {
        if (!probe) throw out_of_range("position exceeds list length");
        probe = probe->next;
    }
    ListNode dummy(0, head);
    ListNode* before = &dummy;
    for (int i = 1; i < left; ++i) before = before->next;
    ListNode* start = before->next;
    for (int i = 0; i < right - left; ++i) {
        ListNode* moved = start->next;
        start->next = moved->next;
        moved->next = before->next;
        before->next = moved;
    }
    return dummy.next;
}
