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
ListNode* detectCycleForTest(ListNode* head) {
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
        if (slow == fast) {
            ListNode* current = head;
            while (current != slow) {
                current = current->next;
                slow = slow->next;
            }
            return current;
        }
    }
    return nullptr;
}
struct Fixture {
    vector<ListNode> nodes;
    ListNode* head;
    explicit Fixture(const vector<int>& values) : nodes(values.size()), head(nullptr) {
        for (size_t i = 0; i < nodes.size(); ++i) {
            nodes[i].val = values[i];
            nodes[i].next = i + 1 < nodes.size() ? &nodes[i + 1] : nullptr;
        }
        if (!nodes.empty()) head = &nodes[0];
    }
    Fixture(const Fixture&) = delete;
    Fixture& operator=(const Fixture&) = delete;
};
vector<ListNode*> snapshot(ListNode* head) {
    vector<ListNode*> order;
    unordered_set<ListNode*> seen;
    for (ListNode* p = head; p; p = p->next) {
        if (!seen.insert(p).second) throw runtime_error("unexpected cycle");
        order.push_back(p);
    }
    return order;
}
void require(bool ok, const char* message) {
    if (!ok) throw runtime_error(message);
}
void checkCase(const vector<int>& values, int k) {
    Fixture fixture(values);
    auto original = snapshot(fixture.head);
    auto expected = original;
    int n = (int)expected.size();
    for (int start = 0; start + k <= n; start += k)
        reverse(expected.begin() + start, expected.begin() + start + k);

    ListNode* grouped = reverseKGroup(fixture.head, k);
    require(snapshot(grouped) == expected, "K-group identity/order mismatch");
    ListNode* restored = reverseKGroup(grouped, k);
    require(snapshot(restored) == original, "double reversal failed");

    bool expectedPalindrome = equal(values.begin(), values.begin() + n / 2,
                                    values.rbegin());
    require(isPalindromeRestoring(restored) == expectedPalindrome,
            "palindrome result mismatch");
    require(snapshot(restored) == original, "palindrome did not restore links");
    require(detectCycleForTest(restored) == nullptr, "false cycle detected");
}
int main() {
    try {
        checkCase({}, 2);
        checkCase({7}, 1);
        checkCase({1, 2, 3, 4, 5}, 2);
        checkCase({1, 2, 2, 1}, 3);
        checkCase({1, 2, 3}, 5);

        mt19937 generator(20260920);
        uniform_int_distribution<int> length(0, 14), value(-2, 2), group(1, 7);
        for (int trial = 0; trial < 1000; ++trial) {
            vector<int> values(length(generator));
            for (int& x : values) x = value(generator);
            checkCase(values, group(generator));
        }

        Fixture cyclic({1, 2, 3, 4});
        cyclic.nodes.back().next = &cyclic.nodes[1];
        require(detectCycleForTest(cyclic.head) == &cyclic.nodes[1], "wrong entry");

        Fixture selfLoop({9});
        selfLoop.head->next = selfLoop.head;
        require(detectCycleForTest(selfLoop.head) == selfLoop.head, "self-loop failed");

        Fixture invalid({1, 2});
        auto unchanged = snapshot(invalid.head);
        bool rejected = false;
        try { reverseKGroup(invalid.head, 0); }
        catch (const invalid_argument&) { rejected = true; }
        require(rejected && snapshot(invalid.head) == unchanged, "invalid k changed list");
        cout << "structural checks passed\n";
    } catch (const exception& error) {
        cerr << error.what() << '\n';
        return 1;
    }
}
