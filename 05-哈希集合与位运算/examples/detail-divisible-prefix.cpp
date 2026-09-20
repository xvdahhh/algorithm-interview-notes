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

long long countDivisibleSubarrays(const vector<int>& a, int k) {
    if (k <= 0) throw invalid_argument("k must be positive");
    unordered_map<long long, long long> frequency;
    frequency[0] = 1;
    long long remainder = 0, answer = 0;
    for (int value : a) {
        remainder = (remainder + value) % k;
        if (remainder < 0) remainder += k;
        auto it = frequency.find(remainder);
        if (it != frequency.end()) answer += it->second;
        ++frequency[remainder];
    }
    return answer;
}
