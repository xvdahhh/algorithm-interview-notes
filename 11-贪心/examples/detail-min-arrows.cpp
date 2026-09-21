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

vector<int> minimumArrowPositions(vector<pair<int,int>> balloons) {
    for (auto [l,r] : balloons) if (l > r) throw invalid_argument("interval");
    sort(balloons.begin(),balloons.end(),[](auto a,auto b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });
    vector<int> arrows;
    for (auto [l,r] : balloons)
        if (arrows.empty() || l > arrows.back()) arrows.push_back(r);
    return arrows;
}
