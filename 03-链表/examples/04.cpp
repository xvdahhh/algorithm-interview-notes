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

struct Node {
    int val; Node *next = nullptr, *random = nullptr;
    explicit Node(int v) : val(v) {}
};
Node* copyRandomList(Node* head) {
    unordered_map<Node*, Node*> copied;
    for (Node* p = head; p; p = p->next) copied[p] = new Node(p->val);
    for (Node* p = head; p; p = p->next) {
        copied[p]->next = p->next ? copied.at(p->next) : nullptr;
        copied[p]->random = p->random ? copied.at(p->random) : nullptr;
    }
    return head ? copied.at(head) : nullptr;
}
