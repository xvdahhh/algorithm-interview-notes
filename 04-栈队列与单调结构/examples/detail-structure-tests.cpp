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

long long largestRectangle(const vector<int>& h) {
    int n = (int)h.size();
    vector<int> st;
    long long best = 0;
    for (int i = 0; i <= n; ++i) {
        int current = i == n ? 0 : h[i];
        while (!st.empty() && h[st.back()] > current) {
            int j = st.back(); st.pop_back();
            int left = st.empty() ? -1 : st.back();
            best = max(best, 1LL * h[j] * (i - left - 1));
        }
        if (i < n) st.push_back(i);
    }
    return best;
}

long long trapRain(const vector<int>& h) {
    vector<int> st;
    long long water = 0;
    for (int i = 0; i < (int)h.size(); ++i) {
        while (!st.empty() && h[i] > h[st.back()]) {
            int bottom = st.back(); st.pop_back();
            if (st.empty()) break;
            int left = st.back();
            long long depth = (long long)min(h[left], h[i]) - h[bottom];
            water += depth * (i - left - 1);
        }
        st.push_back(i);
    }
    return water;
}

int sumSubarrayMins(const vector<int>& a) {
    const long long MOD = 1000000007;
    int n = (int)a.size();
    vector<int> left(n), right(n), st;
    for (int i = 0; i < n; ++i) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        left[i] = st.empty() ? -1 : st.back();
        st.push_back(i);
    }
    st.clear();
    for (int i = n - 1; i >= 0; --i) {
        while (!st.empty() && a[st.back()] > a[i]) st.pop_back();
        right[i] = st.empty() ? n : st.back();
        st.push_back(i);
    }
    long long result = 0;
    for (int i = 0; i < n; ++i) {
        long long contribution = (long long)a[i] * (i - left[i]) % MOD;
        contribution = contribution * (right[i] - i) % MOD;
        result = (result + contribution) % MOD;
    }
    return (int)result;
}

int shortestSubarray(const vector<int>& a, long long k) {
    int n = (int)a.size();
    vector<long long> prefix(n + 1, 0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i];
    deque<int> candidates;
    int best = INT_MAX;
    for (int i = 0; i <= n; ++i) {
        while (!candidates.empty() &&
               prefix[i] - prefix[candidates.front()] >= k) {
            best = min(best, i - candidates.front());
            candidates.pop_front();
        }
        while (!candidates.empty() &&
               prefix[candidates.back()] >= prefix[i])
            candidates.pop_back();
        candidates.push_back(i);
    }
    return best == INT_MAX ? -1 : best;
}

int longestBoundedWindow(const vector<int>& a, long long limit) {
    if (limit < 0) return 0;
    deque<int> maximum, minimum;
    int left = 0, best = 0;
    for (int right = 0; right < (int)a.size(); ++right) {
        while (!maximum.empty() && a[maximum.back()] <= a[right])
            maximum.pop_back();
        while (!minimum.empty() && a[minimum.back()] >= a[right])
            minimum.pop_back();
        maximum.push_back(right);
        minimum.push_back(right);
        while ((long long)a[maximum.front()] - a[minimum.front()] > limit) {
            if (maximum.front() == left) maximum.pop_front();
            if (minimum.front() == left) minimum.pop_front();
            ++left;
        }
        best = max(best, right - left + 1);
    }
    return best;
}

class RingQueue {
    vector<int> data;
    size_t head = 0, used = 0;
public:
    explicit RingQueue(int capacity) {
        if (capacity <= 0) throw invalid_argument("capacity must be positive");
        data.resize((size_t)capacity);
    }
    bool empty() const { return used == 0; }
    bool full() const { return used == data.size(); }
    bool push(int value) {
        if (full()) return false;
        data[(head + used) % data.size()] = value;
        ++used;
        return true;
    }
    optional<int> pop() {
        if (empty()) return nullopt;
        int value = data[head];
        head = (head + 1) % data.size();
        --used;
        return value;
    }
    optional<int> front() const {
        if (empty()) return nullopt;
        return data[head];
    }
};

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
long long bruteRectangle(const vector<int>& a) {
    long long best = 0;
    for (int l = 0; l < (int)a.size(); ++l) {
        int mn = INT_MAX;
        for (int r = l; r < (int)a.size(); ++r) {
            mn = min(mn, a[r]);
            best = max(best, 1LL * mn * (r - l + 1));
        }
    }
    return best;
}
long long bruteRain(const vector<int>& a) {
    long long sum = 0;
    for (int i = 0; i < (int)a.size(); ++i) {
        int left = a[i], right = a[i];
        for (int j = 0; j < i; ++j) left = max(left, a[j]);
        for (int j = i + 1; j < (int)a.size(); ++j) right = max(right, a[j]);
        sum += min(left, right) - a[i];
    }
    return sum;
}
int bruteMins(const vector<int>& a) {
    long long total = 0;
    for (int l = 0; l < (int)a.size(); ++l) {
        int mn = INT_MAX;
        for (int r = l; r < (int)a.size(); ++r) {
            mn = min(mn, a[r]);
            total += mn;
        }
    }
    return (int)(total % 1000000007);
}
int bruteShortest(const vector<int>& a, long long k) {
    int best = INT_MAX;
    for (int l = 0; l < (int)a.size(); ++l) {
        long long sum = 0;
        for (int r = l; r < (int)a.size(); ++r) {
            sum += a[r];
            if (sum >= k) best = min(best, r - l + 1);
        }
    }
    return best == INT_MAX ? -1 : best;
}
int bruteBounded(const vector<int>& a, long long limit) {
    int best = 0;
    for (int l = 0; l < (int)a.size(); ++l) {
        int mn = INT_MAX, mx = INT_MIN;
        for (int r = l; r < (int)a.size(); ++r) {
            mn = min(mn, a[r]); mx = max(mx, a[r]);
            if ((long long)mx - mn <= limit) best = max(best, r - l + 1);
        }
    }
    return best;
}
int main() {
    require(largestRectangle({2,1,5,6,2,3}) == 10, "histogram example");
    require(largestRectangle({2,2}) == 4, "equal heights");
    require(trapRain({3,0,1,3}) == 5, "layered rain");
    require(sumSubarrayMins({2,2}) == 6, "equal minimum ownership");
    require(shortestSubarray({1,-1,3}, 3) == 1, "negative counterexample");
    require(shortestSubarray({}, 0) == -1, "nonempty interval contract");
    require(longestBoundedWindow({INT_MIN, INT_MAX}, 4294967295LL) == 2,
            "wide integer subtraction");
    mt19937 rng(20260920);
    uniform_int_distribution<int> length(0, 12), value(-5, 5), target(-8, 16);
    for (int run = 0; run < 1000; ++run) {
        vector<int> a(length(rng));
        for (int& x : a) x = value(rng);
        int k = target(rng);
        require(shortestSubarray(a, k) == bruteShortest(a, k), "shortest mismatch");
        int limit = target(rng);
        require(longestBoundedWindow(a, limit) == bruteBounded(a, limit),
                "bounded mismatch");
        vector<int> heights, positive;
        for (int x : a) {
            heights.push_back(abs(x));
            positive.push_back(abs(x) + 1);
        }
        require(largestRectangle(heights) == bruteRectangle(heights),
                "rectangle mismatch");
        require(trapRain(heights) == bruteRain(heights), "rain mismatch");
        require(sumSubarrayMins(positive) == bruteMins(positive), "minimum mismatch");
    }
    for (int capacity : {1, 2, 7}) {
        RingQueue actual(capacity);
        deque<int> reference;
        for (int step = 0; step < 1000; ++step) {
            if (rng() % 2 == 0) {
                int x = value(rng);
                bool expected = reference.size() < (size_t)capacity;
                require(actual.push(x) == expected, "ring push");
                if (expected) reference.push_back(x);
            } else {
                optional<int> expected;
                if (!reference.empty()) {
                    expected = reference.front(); reference.pop_front();
                }
                require(actual.pop() == expected, "ring pop");
            }
            optional<int> expectedFront;
            if (!reference.empty()) expectedFront = reference.front();
            require(actual.front() == expectedFront, "ring front");
            require(actual.empty() == reference.empty(), "ring empty");
            require(actual.full() == (reference.size() == (size_t)capacity), "ring full");
        }
    }
    cout << "All chapter 4 checks passed" << endl;
}
