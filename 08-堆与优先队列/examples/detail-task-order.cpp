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

struct ScheduledTask {
    int priority;
    uint64_t sequence;
    string label;
};
struct LaterTask {
    bool operator()(const ScheduledTask& a, const ScheduledTask& b) const {
        return tie(a.priority, a.sequence) > tie(b.priority, b.sequence);
    }
};
vector<string> orderedTasks(const vector<ScheduledTask>& tasks) {
    priority_queue<ScheduledTask, vector<ScheduledTask>, LaterTask> pending;
    for (const auto& task : tasks) pending.push(task);
    vector<string> result;
    while (!pending.empty()) {
        result.push_back(pending.top().label);
        pending.pop();
    }
    return result;
}
