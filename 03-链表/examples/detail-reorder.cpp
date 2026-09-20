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
ListNode* reverseForReorder(ListNode* head) {
    ListNode* previous = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}
void reorderList(ListNode* head) {
    if (!head || !head->next) return;
    ListNode* middle = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    ListNode* second = middle->next;
    middle->next = nullptr;
    second = reverseForReorder(second);
    ListNode* first = head;
    while (second) {
        ListNode* nextFirst = first->next;
        ListNode* nextSecond = second->next;
        first->next = second;
        second->next = nextFirst;
        first = nextFirst;
        second = nextSecond;
    }
}
