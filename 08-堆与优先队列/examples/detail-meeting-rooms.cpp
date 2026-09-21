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

int minimumMeetingRooms(vector<pair<int, int>> meetings) {
    for (auto [start, end] : meetings)
        if (start >= end) throw invalid_argument("require start < end");
    sort(meetings.begin(), meetings.end());
    priority_queue<int, vector<int>, greater<int>> occupied;
    int best = 0;
    for (auto [start, end] : meetings) {
        while (!occupied.empty() && occupied.top() <= start) occupied.pop();
        occupied.push(end);
        best = max(best, (int)occupied.size());
    }
    return best;
}
