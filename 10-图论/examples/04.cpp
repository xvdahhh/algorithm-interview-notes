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

void floyd(vector<vector<long long>>& d) {
    const long long INF=LLONG_MAX/4;
    int n=(int)d.size();
    for (int k=0;k<n;++k)
        for (int i=0;i<n;++i) {
            if (d[i][k]==INF) continue;
            for (int j=0;j<n;++j) {
                if (d[k][j]==INF) continue;
                d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
            }
        }
    // 如有 d[i][i] < 0，则存在负环。
}
