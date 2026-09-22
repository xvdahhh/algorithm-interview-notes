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

vector<int> strictLISIndices(const vector<int>& a) {
    vector<int> tails, indexAtLength, parent(a.size(),-1);
    for (int i = 0; i < (int)a.size(); ++i) {
        int pos = (int)(lower_bound(tails.begin(),tails.end(),a[i])-tails.begin());
        if (pos > 0) parent[i] = indexAtLength[pos-1];
        if (pos == (int)tails.size()) {
            tails.push_back(a[i]); indexAtLength.push_back(i);
        } else {
            tails[pos] = a[i]; indexAtLength[pos] = i;
        }
    }
    vector<int> result;
    if (tails.empty()) return result;
    for (int i = indexAtLength.back(); i != -1; i = parent[i]) result.push_back(i);
    reverse(result.begin(),result.end());
    return result;
}
