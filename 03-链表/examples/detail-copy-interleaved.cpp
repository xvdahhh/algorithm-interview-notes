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
    int val;
    Node* next = nullptr;
    Node* random = nullptr;
    explicit Node(int value) : val(value) {}
};
Node* copyInterleaved(Node* head) {
    if (!head) return nullptr;
    // 前提：next 无环，random 为空或指向链内；所有 new 均成功。
    for (Node* current = head; current;) {
        Node* nextOriginal = current->next;
        Node* copy = new Node(current->val);
        current->next = copy;
        copy->next = nextOriginal;
        current = nextOriginal;
    }
    for (Node* current = head; current; current = current->next->next) {
        Node* copy = current->next;
        copy->random = current->random ? current->random->next : nullptr;
    }
    Node* copyHead = head->next;
    for (Node* current = head; current;) {
        Node* copy = current->next;
        Node* nextOriginal = copy->next;
        current->next = nextOriginal;
        copy->next = nextOriginal ? nextOriginal->next : nullptr;
        current = nextOriginal;
    }
    return copyHead;
}
