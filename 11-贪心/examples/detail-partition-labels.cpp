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

vector<int> partitionByteLabels(const string& s) {
    array<int,256> last; last.fill(-1);
    for (int i = 0; i < (int)s.size(); ++i) last[(unsigned char)s[i]] = i;
    vector<int> lengths;
    int start = 0, end = 0;
    for (int i = 0; i < (int)s.size(); ++i) {
        end = max(end,last[(unsigned char)s[i]]);
        if (i == end) { lengths.push_back(i-start+1); start = i+1; }
    }
    return lengths;
}
