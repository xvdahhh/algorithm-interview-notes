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

long long countSubarraysWithSum(const vector<int>& a, long long k) {
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    long long prefix = 0, answer = 0;
    for (int value : a) {
        prefix += value;
        auto it = frequency.find(prefix - k);
        if (it != frequency.end()) answer += it->second;
        ++frequency[prefix];
    }
    return answer;
}
