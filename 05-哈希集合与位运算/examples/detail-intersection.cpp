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

vector<int> uniqueIntersection(const vector<int>& a, const vector<int>& b) {
    unordered_set<int> remaining(a.begin(), a.end());
    vector<int> answer;
    for (int value : b) {
        if (remaining.erase(value) != 0) answer.push_back(value);
    }
    return answer;
}
