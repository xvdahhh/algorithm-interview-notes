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

vector<int> islandCountsAfterAdds(int rows, int cols,
                                 const vector<pair<int,int>>& positions) {
    if (rows < 0 || cols < 0 || (long long)rows*cols > 1000000)
        throw invalid_argument("grid size");
    for (auto [r,c] : positions)
        if (r < 0 || r >= rows || c < 0 || c >= cols) throw out_of_range("cell");
    int n = rows*cols;
    vector<int> parent(n,-1), size(n,1), answer;
    auto find = [&](int x) {
        while (parent[x] != x) {
            parent[x] = parent[parent[x]]; x = parent[x];
        }
        return x;
    };
    int count = 0;
    const int dr[] = {-1,1,0,0}, dc[] = {0,0,-1,1};
    for (auto [r,c] : positions) {
        int id = r*cols+c;
        if (parent[id] == -1) {
            parent[id] = id; ++count;
            for (int k = 0; k < 4; ++k) {
                int nr = r+dr[k], nc = c+dc[k];
                if (nr < 0 || nr >= rows || nc < 0 || nc >= cols) continue;
                int other = nr*cols+nc;
                if (parent[other] == -1) continue;
                int a = find(id), b = find(other);
                if (a == b) continue;
                if (size[a] < size[b]) swap(a,b);
                parent[b] = a; size[a] += size[b]; --count;
            }
        }
        answer.push_back(count);
    }
    return answer;
}
