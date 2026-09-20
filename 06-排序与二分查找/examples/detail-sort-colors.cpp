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

void sortColors(vector<int>& a) {
    for (int value : a)
        if (value < 0 || value > 2) throw invalid_argument("only 0,1,2 allowed");
    int zero = 0, i = 0, two = (int)a.size() - 1;
    while (i <= two) {
        if (a[i] == 0) swap(a[zero++], a[i++]);
        else if (a[i] == 2) swap(a[i], a[two--]);
        else ++i;
    }
}
