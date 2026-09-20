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
ListNode* reverseHalf(ListNode* head) {
    ListNode* previous = nullptr;
    while (head) {
        ListNode* next = head->next;
        head->next = previous;
        previous = head;
        head = next;
    }
    return previous;
}
bool isPalindromeRestoring(ListNode* head) {
    if (!head || !head->next) return true;
    ListNode* middle = head;
    ListNode* fast = head;
    while (fast->next && fast->next->next) {
        middle = middle->next;
        fast = fast->next->next;
    }
    ListNode* second = reverseHalf(middle->next);
    middle->next = second;
    ListNode* first = head;
    ListNode* current = second;
    bool equal = true;
    while (current) {
        if (first->val != current->val) equal = false;
        first = first->next;
        current = current->next;
    }
    middle->next = reverseHalf(second);
    return equal;
}
