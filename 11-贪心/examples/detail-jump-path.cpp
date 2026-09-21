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

optional<vector<int>> shortestJumpPath(const vector<int>& a) {
    for (int x : a) if (x < 0) throw invalid_argument("jump");
    int n = (int)a.size();
    if (!n) return nullopt;
    vector<int> parent(n,-1);
    int far = 0;
    for (int i = 0; i < n && i <= far; ++i) {
        int next = (int)min((long long)n-1,(long long)i+a[i]);
        for (int j = far+1; j <= next; ++j) parent[j] = i;
        far = max(far,next);
        if (far == n-1) break;
    }
    if (far < n-1) return nullopt;
    vector<int> path;
    for (int v = n-1; v != -1; v = parent[v]) path.push_back(v);
    reverse(path.begin(),path.end());
    return path;
}
