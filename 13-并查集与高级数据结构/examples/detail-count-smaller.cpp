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

vector<int> countSmallerRight(const vector<int>& a) {
    if (a.size() > 1000000) throw invalid_argument("size limit");
    vector<int> values = a;
    sort(values.begin(),values.end());
    values.erase(unique(values.begin(),values.end()),values.end());
    vector<int> bit(values.size()+1), answer(a.size());
    for (int i = (int)a.size()-1; i >= 0; --i) {
        int rank = (int)(lower_bound(values.begin(),values.end(),a[i])-values.begin())+1;
        int count = 0;
        for (int j = rank-1; j > 0; j -= j&-j) count += bit[j];
        answer[i] = count;
        for (int j = rank; j < (int)bit.size(); j += j&-j) ++bit[j];
    }
    return answer;
}
