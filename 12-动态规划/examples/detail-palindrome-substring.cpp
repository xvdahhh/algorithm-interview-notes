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

string longestPalindromeSubstringDP(const string& s) {
    int n = (int)s.size();
    if (!n) return "";
    vector<vector<char>> palindrome(n,vector<char>(n,false));
    int start = 0, bestLength = 1;
    for (int len = 1; len <= n; ++len)
        for (int l = 0; l+len <= n; ++l) {
            int r = l+len-1;
            palindrome[l][r] = s[l] == s[r] &&
                (len <= 2 || palindrome[l+1][r-1]);
            if (palindrome[l][r] && len > bestLength) {
                start = l; bestLength = len;
            }
        }
    return s.substr(start,bestLength);
}
