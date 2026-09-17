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

bool validBrackets(const string& s) {
    vector<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push_back(c);
        else {
            char need = c == ')' ? '(' : c == ']' ? '[' : c == '}' ? '{' : 0;
            if (!need || st.empty() || st.back() != need) return false;
            st.pop_back();
        }
    }
    return st.empty();
}
