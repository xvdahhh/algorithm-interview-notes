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

vector<int> findAnagrams(const string& s, const string& pattern) {
    if (pattern.empty()) return {}; // 本接口不枚举空模式的位置
    int k = (int)pattern.size();
    array<int, 256> need{}, have{};
    for (unsigned char c : pattern) ++need[c];
    vector<int> answer;
    for (int right = 0; right < (int)s.size(); ++right) {
        ++have[static_cast<unsigned char>(s[right])];
        if (right >= k)
            --have[static_cast<unsigned char>(s[right - k])];
        if (right >= k - 1 && have == need)
            answer.push_back(right - k + 1);
    }
    return answer;
}
