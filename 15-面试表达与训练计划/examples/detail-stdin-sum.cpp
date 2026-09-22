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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    long long n;
    if (!(cin >> n) || n < 0 || n > 1000000) {
        cerr << "invalid n\n";
        return 1;
    }
    long long total = 0;
    for (long long i = 0; i < n; ++i) {
        int value;
        if (!(cin >> value)) {
            cerr << "missing or invalid integer\n";
            return 1;
        }
        total += value;
    }
    cout << total << '\n';
}
