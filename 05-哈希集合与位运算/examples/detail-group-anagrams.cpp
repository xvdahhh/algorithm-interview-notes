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

struct LetterCountsHash {
    size_t operator()(const array<int, 26>& key) const noexcept {
        size_t hash = 0;
        for (int count : key)
            hash = hash * size_t{131} + static_cast<size_t>(count);
        return hash; // unsigned overflow is defined; collisions are allowed
    }
};
vector<vector<string>> groupAnagrams(const vector<string>& words) {
    unordered_map<array<int, 26>, size_t, LetterCountsHash> groups;
    groups.reserve(words.size());
    vector<vector<string>> result;
    for (const string& word : words) {
        array<int, 26> key{};
        for (char ch : word) {
            if (ch < 'a' || ch > 'z')
                throw invalid_argument("lowercase a-z required");
            ++key[ch - 'a'];
        }
        auto [it, inserted] = groups.emplace(key, result.size());
        if (inserted) result.push_back({});
        result[it->second].push_back(word);
    }
    return result;
}
