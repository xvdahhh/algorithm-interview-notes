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
ListNode* reverseKGroup(ListNode* head, int k) {
    if (k <= 0) throw invalid_argument("k must be positive");
    if (k == 1 || !head) return head;
    ListNode dummy(0, head);
    ListNode* groupBefore = &dummy;
    while (true) {
        ListNode* kth = groupBefore;
        for (int i = 0; i < k && kth; ++i) kth = kth->next;
        if (!kth) break;
        ListNode* groupAfter = kth->next;
        ListNode* oldHead = groupBefore->next;
        ListNode* previous = groupAfter;
        ListNode* current = oldHead;
        while (current != groupAfter) {
            ListNode* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        groupBefore->next = kth;
        groupBefore = oldHead;
    }
    return dummy.next;
}
