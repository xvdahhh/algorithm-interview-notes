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

int assignResources(vector<int> needs, vector<int> sizes) {
    for (int x : needs) if (x < 0) throw invalid_argument("need");
    for (int x : sizes) if (x < 0) throw invalid_argument("size");
    sort(needs.begin(),needs.end()); sort(sizes.begin(),sizes.end());
    size_t child = 0;
    for (int size : sizes)
        if (child < needs.size() && size >= needs[child]) ++child;
    return (int)child;
}
