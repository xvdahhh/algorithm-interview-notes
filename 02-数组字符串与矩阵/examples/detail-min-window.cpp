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

string minWindow(const string& s, const string& t) {
    if (t.empty()) return "";
    array<int, 256> need{}, have{};
    for (unsigned char c : t) ++need[c];
    int missing = (int)t.size();
    int left = 0, bestStart = 0, bestLength = INT_MAX;
    for (int right = 0; right < (int)s.size(); ++right) {
        unsigned char c = static_cast<unsigned char>(s[right]);
        if (have[c] < need[c]) --missing;
        ++have[c];
        while (missing == 0) {
            if (right - left + 1 < bestLength) {
                bestStart = left;
                bestLength = right - left + 1;
            }
            unsigned char old = static_cast<unsigned char>(s[left++]);
            --have[old];
            if (have[old] < need[old]) ++missing;
        }
    }
    return bestLength == INT_MAX ? "" : s.substr(bestStart, bestLength);
}
