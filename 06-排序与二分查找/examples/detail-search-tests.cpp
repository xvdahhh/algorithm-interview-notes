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

struct Record {
    int key;
    int id; // original identity, not part of the sorting key
};
void stableMergeRange(vector<Record>& a, vector<Record>& tmp, int l, int r) {
    if (r - l <= 1) return;
    int m = l + (r - l) / 2;
    stableMergeRange(a, tmp, l, m);
    stableMergeRange(a, tmp, m, r);
    int i = l, j = m, out = l;
    while (i < m && j < r)
        tmp[out++] = a[i].key <= a[j].key ? a[i++] : a[j++];
    while (i < m) tmp[out++] = a[i++];
    while (j < r) tmp[out++] = a[j++];
    for (int k = l; k < r; ++k) a[k] = tmp[k];
}
void stableMergeSort(vector<Record>& a) {
    vector<Record> tmp(a.size());
    stableMergeRange(a, tmp, 0, (int)a.size());
}

long long inversionRange(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (r - l <= 1) return 0;
    int m = l + (r - l) / 2;
    long long answer = inversionRange(a, tmp, l, m);
    answer += inversionRange(a, tmp, m, r);
    int i = l, j = m, out = l;
    while (i < m && j < r) {
        if (a[i] <= a[j]) tmp[out++] = a[i++];
        else { answer += m - i; tmp[out++] = a[j++]; }
    }
    while (i < m) tmp[out++] = a[i++];
    while (j < r) tmp[out++] = a[j++];
    for (int k = l; k < r; ++k) a[k] = tmp[k];
    return answer;
}
long long countInversions(vector<int>& a) {
    vector<int> tmp(a.size());
    return inversionRange(a, tmp, 0, (int)a.size());
}

void siftDown(vector<int>& a, int root, int size) {
    while (root < size / 2) {
        int child = root * 2 + 1;
        if (child + 1 < size && a[child] < a[child + 1]) ++child;
        if (a[root] >= a[child]) break;
        swap(a[root], a[child]);
        root = child;
    }
}
void heapSort(vector<int>& a) {
    int n = (int)a.size();
    for (int root = n / 2 - 1; root >= 0; --root) siftDown(a, root, n);
    for (int end = n - 1; end > 0; --end) {
        swap(a[0], a[end]);
        siftDown(a, 0, end);
    }
}

struct CountItem { int key; int id; };
vector<CountItem> stableCountingSort(const vector<CountItem>& a, int keyCount) {
    if (keyCount <= 0 || keyCount > 1000000)
        throw invalid_argument("require 1 <= keyCount <= 1000000");
    vector<size_t> end(keyCount, 0);
    for (const auto& item : a) {
        if (item.key < 0 || item.key >= keyCount)
            throw invalid_argument("key outside [0, keyCount)");
        ++end[item.key];
    }
    for (int key = 1; key < keyCount; ++key) end[key] += end[key - 1];
    vector<CountItem> answer(a.size());
    for (size_t i = a.size(); i > 0; --i) {
        const auto& item = a[i - 1];
        answer[--end[item.key]] = item;
    }
    return answer;
}

void randomQuickRange(vector<int>& a, int l, int r, mt19937& rng) {
    while (l < r) {
        uniform_int_distribution<int> pick(l, r);
        int pivot = a[pick(rng)];
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else ++i;
        }
        if (lt - l < r - gt) {
            randomQuickRange(a, l, lt - 1, rng);
            l = gt + 1;
        } else {
            randomQuickRange(a, gt + 1, r, rng);
            r = lt - 1;
        }
    }
}
void randomizedQuickSort(vector<int>& a, uint32_t seed) {
    mt19937 rng(seed);
    if (!a.empty()) randomQuickRange(a, 0, (int)a.size() - 1, rng);
}

int kthSmallest(vector<int>& a, int k, uint32_t seed) {
    int n = (int)a.size();
    if (k < 1 || k > n) throw out_of_range("k outside [1,n]");
    int target = k - 1, l = 0, r = n - 1;
    mt19937 rng(seed);
    while (l <= r) {
        uniform_int_distribution<int> pick(l, r);
        int pivot = a[pick(rng)];
        int lt = l, i = l, gt = r;
        while (i <= gt) {
            if (a[i] < pivot) swap(a[lt++], a[i++]);
            else if (a[i] > pivot) swap(a[i], a[gt--]);
            else ++i;
        }
        if (target < lt) r = lt - 1;
        else if (target > gt) l = gt + 1;
        else return pivot;
    }
    throw logic_error("unreachable for valid input");
}

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

int lowerBoundIndex(const vector<int>& a, int x) {
    int l = 0, r = (int)a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] >= x) r = mid;
        else l = mid + 1;
    }
    return l;
}
int upperBoundIndex(const vector<int>& a, int x) {
    int l = 0, r = (int)a.size();
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] > x) r = mid;
        else l = mid + 1;
    }
    return l;
}
int lastAtMost(const vector<int>& a, int x) {
    return upperBoundIndex(a, x) - 1;
}

int searchRotatedDistinct(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return mid;
        if (a[l] <= a[mid]) {
            if (a[l] <= target && target < a[mid]) r = mid - 1;
            else l = mid + 1;
        } else {
            if (a[mid] < target && target <= a[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return -1;
}
bool searchRotatedWithDuplicates(const vector<int>& a, int target) {
    int l = 0, r = (int)a.size() - 1;
    while (l <= r) {
        int mid = l + (r - l) / 2;
        if (a[mid] == target) return true;
        if (a[l] == a[mid] && a[mid] == a[r]) { ++l; --r; continue; }
        if (a[l] <= a[mid]) {
            if (a[l] <= target && target < a[mid]) r = mid - 1;
            else l = mid + 1;
        } else {
            if (a[mid] < target && target <= a[r]) l = mid + 1;
            else r = mid - 1;
        }
    }
    return false;
}

int minimumInRotated(const vector<int>& a) {
    if (a.empty()) throw invalid_argument("empty array");
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < a[r]) r = mid;
        else if (a[mid] > a[r]) l = mid + 1;
        else --r;
    }
    return a[l];
}

int findPeak(const vector<int>& a) {
    if (a.empty()) return -1;
    int l = 0, r = (int)a.size() - 1;
    while (l < r) {
        int mid = l + (r - l) / 2;
        if (a[mid] < a[mid + 1]) l = mid + 1;
        else r = mid;
    }
    return l;
}

double medianOfSorted(const vector<int>& a, const vector<int>& b) {
    if (a.size() > b.size()) return medianOfSorted(b, a);
    int m = (int)a.size(), n = (int)b.size();
    if (m == 0 && n == 0) throw invalid_argument("both arrays empty");
    int half = (int)(((long long)m + n + 1) / 2);
    int l = 0, r = m;
    while (l <= r) {
        int i = l + (r - l) / 2, j = half - i;
        long long al = i == 0 ? LLONG_MIN : a[i - 1];
        long long ar = i == m ? LLONG_MAX : a[i];
        long long bl = j == 0 ? LLONG_MIN : b[j - 1];
        long long br = j == n ? LLONG_MAX : b[j];
        if (al <= br && bl <= ar) {
            if (((long long)m + n) % 2 != 0) return (double)max(al, bl);
            return (max(al, bl) + min(ar, br)) / 2.0;
        }
        if (al > br) r = i - 1;
        else l = i + 1;
    }
    throw invalid_argument("sorted input required");
}

int minimumEatingSpeed(const vector<int>& piles, long long hours) {
    if (piles.empty()) return 0;
    if (hours <= 0) throw invalid_argument("hours must be positive");
    int hi = 0;
    for (int value : piles) {
        if (value <= 0) throw invalid_argument("piles must be positive");
        hi = max(hi, value);
    }
    if (hours < (long long)piles.size()) return -1;
    auto feasible = [&](int speed) {
        long long used = 0;
        for (int value : piles) {
            used += value / speed + (value % speed != 0);
            if (used > hours) return false;
        }
        return true;
    };
    int lo = 1;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }
    return lo;
}

long long maximumMinimumDistance(vector<int> positions, int count) {
    int n = (int)positions.size();
    if (count < 2 || count > n) throw invalid_argument("require 2 <= count <= n");
    sort(positions.begin(), positions.end());
    auto feasible = [&](long long distance) {
        int placed = 1;
        long long last = positions[0];
        for (int i = 1; i < n; ++i) {
            if ((long long)positions[i] - last >= distance) {
                last = positions[i];
                if (++placed == count) return true;
            }
        }
        return false;
    };
    long long lo = 0, hi = (long long)positions.back() - positions.front();
    while (lo < hi) {
        long long mid = lo + (hi - lo + 1) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

uint64_t floorSquareRoot(uint64_t x) {
    uint64_t lo = 0, hi = min(x, uint64_t{UINT32_MAX});
    while (lo < hi) {
        uint64_t mid = lo + (hi - lo + 1) / 2;
        if (mid <= x / mid) lo = mid;
        else hi = mid - 1;
    }
    return lo;
}

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
long long bruteInversions(const vector<int>& a) {
    long long answer = 0;
    for (int i = 0; i < (int)a.size(); ++i)
        for (int j = i + 1; j < (int)a.size(); ++j)
            answer += a[i] > a[j];
    return answer;
}
int bruteSpeed(const vector<int>& piles, long long hours) {
    if (piles.empty()) return 0;
    if (hours < (long long)piles.size()) return -1;
    int maximum = *max_element(piles.begin(), piles.end());
    for (int speed = 1; speed <= maximum; ++speed) {
        long long used = 0;
        for (int value : piles) used += (value + speed - 1) / speed;
        if (used <= hours) return speed;
    }
    return -1;
}
long long bruteDistance(vector<int> positions, int count) {
    sort(positions.begin(), positions.end());
    int n = (int)positions.size();
    long long best = 0;
    for (unsigned mask = 0; mask < (1U << n); ++mask) {
        int selected = 0;
        for (unsigned bits = mask; bits != 0; bits &= bits - 1) ++selected;
        if (selected != count) continue;
        long long distance = LLONG_MAX;
        int previous = -1;
        for (int i = 0; i < n; ++i) {
            if ((mask & (1U << i)) == 0) continue;
            if (previous != -1)
                distance = min(distance, (long long)positions[i] - positions[previous]);
            previous = i;
        }
        best = max(best, distance);
    }
    return best;
}
int main() {
    require(lowerBoundIndex({}, 1) == 0, "empty lower bound");
    require(lastAtMost({2,3}, 1) == -1, "no last element");
    require(minimumInRotated({1,1,0,1}) == 0, "duplicate rotation");
    require(searchRotatedWithDuplicates({1,0,1,1,1}, 0), "hidden pivot");
    require(medianOfSorted({INT_MAX}, {INT_MAX}) == (double)INT_MAX, "median overflow");
    require(medianOfSorted({INT_MIN}, {INT_MAX}) == -0.5, "median extremes");
    require(minimumEatingSpeed({3,6,7,11}, 8) == 4, "banana example");
    require(minimumEatingSpeed({1,1}, 1) == -1, "banana infeasible");
    require(maximumMinimumDistance({INT_MIN,INT_MAX}, 2) == 4294967295LL,
            "distance overflow");
    require(floorSquareRoot(UINT64_MAX) == UINT32_MAX, "sqrt maximum");
    uint64_t expectedRoot = 0;
    for (uint64_t x = 0; x <= 10000; ++x) {
        while ((expectedRoot + 1) * (expectedRoot + 1) <= x) ++expectedRoot;
        require(floorSquareRoot(x) == expectedRoot, "sqrt small range");
    }
    mt19937 rng(20260920);
    uniform_int_distribution<int> length(0, 12), value(-5, 5);
    for (int run = 0; run < 1000; ++run) {
        vector<int> a(length(rng));
        for (int& x : a) x = value(rng);
        vector<int> sorted = a;
        sort(sorted.begin(), sorted.end());
        vector<int> working = a;
        require(countInversions(working) == bruteInversions(a), "inverse count");
        require(working == sorted, "inverse merge ordering");
        working = a; heapSort(working);
        require(working == sorted, "heap sort");
        working = a; randomizedQuickSort(working, (uint32_t)rng());
        require(working == sorted, "quick sort");
        for (int k = 1; k <= (int)a.size(); ++k) {
            working = a;
            require(kthSmallest(working, k, (uint32_t)rng()) == sorted[k - 1],
                    "quickselect");
        }
        vector<Record> records;
        vector<CountItem> counted;
        for (int i = 0; i < (int)a.size(); ++i) {
            records.push_back({a[i], i});
            counted.push_back({a[i] + 5, i});
        }
        auto reference = records;
        stable_sort(reference.begin(), reference.end(),
                    [](const Record& x, const Record& y) { return x.key < y.key; });
        stableMergeSort(records);
        auto byCount = stableCountingSort(counted, 11);
        for (int i = 0; i < (int)a.size(); ++i) {
            require(records[i].key == reference[i].key &&
                    records[i].id == reference[i].id, "merge stability");
            require(byCount[i].key == reference[i].key + 5 &&
                    byCount[i].id == reference[i].id, "count stability");
        }
        working = a;
        for (int& x : working) x = (x + 6) % 3;
        auto colors = working;
        sort(colors.begin(), colors.end());
        sortColors(working);
        require(working == colors, "colors");
        for (int x = -6; x <= 6; ++x) {
            int lo = 0, hi = 0;
            while (lo < (int)sorted.size() && sorted[lo] < x) ++lo;
            while (hi < (int)sorted.size() && sorted[hi] <= x) ++hi;
            require(lowerBoundIndex(sorted, x) == lo, "lower bound");
            require(upperBoundIndex(sorted, x) == hi, "upper bound");
            require(lastAtMost(sorted, x) == hi - 1, "last at most");
        }
        if (!a.empty()) {
            auto rotated = sorted;
            rotate(rotated.begin(), rotated.begin() + rng() % rotated.size(), rotated.end());
            require(minimumInRotated(rotated) == sorted.front(), "rotated minimum");
            for (int x = -6; x <= 6; ++x)
                require(searchRotatedWithDuplicates(rotated, x) ==
                        (find(a.begin(), a.end(), x) != a.end()), "rotated duplicate search");
            auto distinct = sorted;
            distinct.erase(unique(distinct.begin(), distinct.end()), distinct.end());
            rotate(distinct.begin(), distinct.begin() + rng() % distinct.size(), distinct.end());
            for (int x = -6; x <= 6; ++x) {
                int found = searchRotatedDistinct(distinct, x);
                bool exists = find(distinct.begin(), distinct.end(), x) != distinct.end();
                require((found >= 0) == exists, "rotated distinct presence");
                if (found >= 0) require(distinct[found] == x, "rotated distinct index");
            }
            auto peaks = a;
            peaks.erase(unique(peaks.begin(), peaks.end()), peaks.end());
            int p = findPeak(peaks);
            require(p >= 0 && p < (int)peaks.size(), "peak range");
            require((p == 0 || peaks[p] > peaks[p - 1]) &&
                    (p + 1 == (int)peaks.size() || peaks[p] > peaks[p + 1]), "peak property");
            size_t split = rng() % (a.size() + 1);
            vector<int> left(a.begin(), a.begin() + split), right(a.begin() + split, a.end());
            sort(left.begin(), left.end()); sort(right.begin(), right.end());
            double middle = sorted.size() % 2 ? sorted[sorted.size() / 2] :
                ((long long)sorted[sorted.size() / 2 - 1] + sorted[sorted.size() / 2]) / 2.0;
            require(medianOfSorted(left, right) == middle, "median split");
        } else {
            require(findPeak(a) == -1, "empty peak");
        }
        vector<int> piles;
        for (int x : a) piles.push_back(abs(x) + 1);
        long long hours = (long long)piles.size() + rng() % 20;
        require(minimumEatingSpeed(piles, hours) == bruteSpeed(piles, hours), "banana brute");
        if (run < 100 && a.size() >= 2) {
            int count = 2 + (int)(rng() % (a.size() - 1));
            require(maximumMinimumDistance(a, count) == bruteDistance(a, count),
                    "distance brute");
        }
    }
    bool rejected = false;
    vector<int> empty;
    try { (void)kthSmallest(empty, 1, 0); }
    catch (const out_of_range&) { rejected = true; }
    require(rejected, "invalid rank");
    cout << "All chapter 6 checks passed" << endl;
}
