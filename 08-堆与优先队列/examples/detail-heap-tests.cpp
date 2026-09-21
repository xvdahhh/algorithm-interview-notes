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

class IntMinHeap {
    vector<int> data;
    void down(size_t root) {
        size_t n = data.size();
        while (root < n / 2) {
            size_t child = root * 2 + 1;
            if (child + 1 < n && data[child + 1] < data[child]) ++child;
            if (data[root] <= data[child]) break;
            swap(data[root], data[child]);
            root = child;
        }
    }
public:
    explicit IntMinHeap(vector<int> values = {}) : data(move(values)) {
        for (size_t i = data.size() / 2; i > 0; --i) down(i - 1);
    }
    bool empty() const { return data.empty(); }
    size_t size() const { return data.size(); }
    int top() const {
        if (empty()) throw out_of_range("empty heap");
        return data[0];
    }
    void push(int value) {
        data.push_back(value);
        size_t i = data.size() - 1;
        while (i > 0) {
            size_t parent = (i - 1) / 2;
            if (data[parent] <= data[i]) break;
            swap(data[parent], data[i]); i = parent;
        }
    }
    int pop() {
        if (empty()) throw out_of_range("empty heap");
        int answer = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!empty()) down(0);
        return answer;
    }
};

struct ScheduledTask {
    int priority;
    uint64_t sequence;
    string label;
};
struct LaterTask {
    bool operator()(const ScheduledTask& a, const ScheduledTask& b) const {
        return tie(a.priority, a.sequence) > tie(b.priority, b.sequence);
    }
};
vector<string> orderedTasks(const vector<ScheduledTask>& tasks) {
    priority_queue<ScheduledTask, vector<ScheduledTask>, LaterTask> pending;
    for (const auto& task : tasks) pending.push(task);
    vector<string> result;
    while (!pending.empty()) {
        result.push_back(pending.top().label);
        pending.pop();
    }
    return result;
}

class VersionedMinQueue {
    struct State { int priority; uint64_t version; };
    using Entry = tuple<int, int, uint64_t>; // priority, id, version
    priority_queue<Entry, vector<Entry>, greater<Entry>> heap;
    unordered_map<int, State> live;
    uint64_t nextVersion = 0;
    void prune() {
        while (!heap.empty()) {
            auto [priority, id, version] = heap.top();
            auto it = live.find(id);
            if (it != live.end() && it->second.version == version) break;
            heap.pop();
        }
    }
public:
    void put(int id, int priority) {
        if (nextVersion == UINT64_MAX) throw overflow_error("version exhausted");
        uint64_t version = ++nextVersion;
        heap.emplace(priority, id, version);
        live[id] = {priority, version};
    }
    void cancel(int id) { live.erase(id); }
    optional<pair<int, int>> pop() {
        prune();
        if (heap.empty()) return nullopt;
        auto [priority, id, version] = heap.top();
        heap.pop(); live.erase(id);
        return pair<int, int>{id, priority};
    }
};

class KthLargestStream {
    size_t k;
    priority_queue<int, vector<int>, greater<int>> selected;
public:
    explicit KthLargestStream(int rank) {
        if (rank <= 0) throw invalid_argument("k must be positive");
        k = (size_t)rank;
    }
    optional<int> add(int value) {
        if (selected.size() < k) selected.push(value);
        else if (value > selected.top()) {
            selected.pop(); selected.push(value);
        }
        if (selected.size() < k) return nullopt;
        return selected.top();
    }
};

struct FrequencyItem { int value; int count; };
struct BetterFrequency {
    bool operator()(const FrequencyItem& a, const FrequencyItem& b) const {
        if (a.count != b.count) return a.count > b.count;
        return a.value < b.value;
    }
};
vector<int> topFrequent(const vector<int>& a, int k) {
    if (k < 0) throw invalid_argument("negative k");
    if (k == 0) return {};
    unordered_map<int, int> count;
    for (int value : a) ++count[value];
    if ((size_t)k > count.size()) throw invalid_argument("k exceeds distinct values");
    priority_queue<FrequencyItem, vector<FrequencyItem>, BetterFrequency> selected;
    for (auto [value, frequency] : count) {
        selected.push({value, frequency});
        if (selected.size() > (size_t)k) selected.pop();
    }
    vector<int> answer;
    while (!selected.empty()) {
        answer.push_back(selected.top().value); selected.pop();
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

vector<pair<int, int>> closestPoints(const vector<pair<int, int>>& points, int k) {
    if (k < 0 || (size_t)k > points.size()) throw invalid_argument("invalid k");
    if (k == 0) return {};
    using Entry = pair<long long, size_t>; // squared distance, input index
    priority_queue<Entry> selected;
    for (size_t i = 0; i < points.size(); ++i) {
        auto [x, y] = points[i];
        if (x < -1000000000 || x > 1000000000 ||
            y < -1000000000 || y > 1000000000)
            throw invalid_argument("coordinate outside supported range");
        long long distance = 1LL * x * x + 1LL * y * y;
        selected.push({distance, i});
        if (selected.size() > (size_t)k) selected.pop();
    }
    vector<pair<int, int>> answer;
    while (!selected.empty()) {
        answer.push_back(points[selected.top().second]); selected.pop();
    }
    reverse(answer.begin(), answer.end());
    return answer;
}

struct ListNode {
    int val;
    ListNode* next = nullptr;
    explicit ListNode(int value) : val(value) {}
};
struct ListEntry { ListNode* node; size_t row; };
struct LaterListEntry {
    bool operator()(const ListEntry& a, const ListEntry& b) const {
        if (a.node->val != b.node->val) return a.node->val > b.node->val;
        return a.row > b.row;
    }
};
ListNode* mergeSortedLists(const vector<ListNode*>& heads) {
    priority_queue<ListEntry, vector<ListEntry>, LaterListEntry> pending;
    for (size_t row = 0; row < heads.size(); ++row)
        if (heads[row]) pending.push({heads[row], row});
    ListNode dummy(0);
    ListNode* tail = &dummy;
    while (!pending.empty()) {
        auto [node, row] = pending.top(); pending.pop();
        ListNode* successor = node->next;
        if (successor) pending.push({successor, row});
        tail->next = node;
        tail = node;
        tail->next = nullptr;
    }
    return dummy.next;
}

vector<pair<int, int>> smallestPairs(const vector<int>& a, const vector<int>& b, int k) {
    if (k < 0) throw invalid_argument("negative k");
    if (k == 0 || a.empty() || b.empty()) return {};
    using Entry = tuple<long long, size_t, size_t>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    size_t initial = min((size_t)k, a.size());
    for (size_t i = 0; i < initial; ++i) pending.emplace((long long)a[i] + b[0], i, 0);
    vector<pair<int, int>> result;
    while (!pending.empty() && result.size() < (size_t)k) {
        auto [sum, i, j] = pending.top(); pending.pop();
        result.push_back({a[i], b[j]});
        if (j + 1 < b.size()) pending.emplace((long long)a[i] + b[j + 1], i, j + 1);
    }
    return result;
}

optional<pair<int, int>> smallestCoveringRange(const vector<vector<int>>& lists) {
    if (lists.empty()) return nullopt;
    using Entry = tuple<int, size_t, size_t>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    int currentMax = INT_MIN;
    for (size_t row = 0; row < lists.size(); ++row) {
        if (lists[row].empty()) return nullopt;
        pending.emplace(lists[row][0], row, 0);
        currentMax = max(currentMax, lists[row][0]);
    }
    int bestLeft = get<0>(pending.top()), bestRight = currentMax;
    while (true) {
        auto [currentMin, row, index] = pending.top(); pending.pop();
        long long width = (long long)currentMax - currentMin;
        long long bestWidth = (long long)bestRight - bestLeft;
        if (width < bestWidth || (width == bestWidth && currentMin < bestLeft)) {
            bestLeft = currentMin; bestRight = currentMax;
        }
        if (index + 1 == lists[row].size()) break;
        int next = lists[row][index + 1];
        currentMax = max(currentMax, next);
        pending.emplace(next, row, index + 1);
    }
    return pair<int, int>{bestLeft, bestRight};
}

#include <set>
#include <iterator>

class RemovableMedian {
    multiset<int> lo, hi;
    void rebalance() {
        while (lo.size() > hi.size() + 1) {
            auto it = prev(lo.end());
            hi.insert(*it); lo.erase(it);
        }
        while (lo.size() < hi.size()) {
            auto it = hi.begin();
            lo.insert(*it); hi.erase(it);
        }
    }
public:
    void add(int value) {
        if (lo.empty() || value <= *prev(lo.end())) lo.insert(value);
        else hi.insert(value);
        rebalance();
    }
    void remove(int value) {
        auto it = lo.find(value);
        if (it != lo.end()) lo.erase(it);
        else {
            auto other = hi.find(value);
            if (other == hi.end()) throw invalid_argument("value not present");
            hi.erase(other);
        }
        rebalance();
    }
    double median() const {
        if (lo.empty()) throw out_of_range("no data");
        if (lo.size() != hi.size()) return *prev(lo.end());
        return ((long long)*prev(lo.end()) + *hi.begin()) / 2.0;
    }
};
vector<double> slidingMedians(const vector<int>& a, int k) {
    if (k <= 0 || (size_t)k > a.size()) return {};
    RemovableMedian state;
    vector<double> answer;
    for (size_t i = 0; i < a.size(); ++i) {
        if (i >= (size_t)k) state.remove(a[i - k]);
        state.add(a[i]);
        if (i + 1 >= (size_t)k) answer.push_back(state.median());
    }
    return answer;
}

int minimumMeetingRooms(vector<pair<int, int>> meetings) {
    for (auto [start, end] : meetings)
        if (start >= end) throw invalid_argument("require start < end");
    sort(meetings.begin(), meetings.end());
    priority_queue<int, vector<int>, greater<int>> occupied;
    int best = 0;
    for (auto [start, end] : meetings) {
        while (!occupied.empty() && occupied.top() <= start) occupied.pop();
        occupied.push(end);
        best = max(best, (int)occupied.size());
    }
    return best;
}

struct WeightedEdge { int to; int weight; };
vector<optional<long long>> shortestDistances(
    const vector<vector<WeightedEdge>>& graph, int source) {
    if (graph.size() > 100000) throw invalid_argument("too many vertices");
    int n = (int)graph.size();
    if (source < 0 || source >= n) throw out_of_range("invalid source");
    for (const auto& edges : graph)
        for (const auto& edge : edges)
            if (edge.to < 0 || edge.to >= n || edge.weight < 0 ||
                edge.weight > 1000000000)
                throw invalid_argument("invalid edge");
    const long long INF = LLONG_MAX / 4;
    vector<long long> distance(n, INF);
    using Entry = pair<long long, int>;
    priority_queue<Entry, vector<Entry>, greater<Entry>> pending;
    distance[source] = 0; pending.push({0, source});
    while (!pending.empty()) {
        auto [value, u] = pending.top(); pending.pop();
        if (value != distance[u]) continue;
        for (const auto& edge : graph[u]) {
            long long candidate = value + edge.weight;
            if (candidate < distance[edge.to]) {
                distance[edge.to] = candidate;
                pending.push({candidate, edge.to});
            }
        }
    }
    vector<optional<long long>> result(n);
    for (int i = 0; i < n; ++i)
        if (distance[i] != INF) result[i] = distance[i];
    return result;
}

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
optional<pair<int,int>> bruteRange(const vector<vector<int>>& rows) {
    if (rows.empty()) return nullopt;
    vector<int> values;
    for (const auto& row : rows) {
        if (row.empty()) return nullopt;
        values.insert(values.end(), row.begin(), row.end());
    }
    sort(values.begin(), values.end());
    optional<pair<int,int>> best;
    for (int left : values) for (int right : values) {
        if (left > right) continue;
        bool covers = true;
        for (const auto& row : rows) {
            bool found = false;
            for (int value : row) if (left <= value && value <= right) found = true;
            if (!found) covers = false;
        }
        if (!covers) continue;
        if (!best || (long long)right - left < (long long)best->second - best->first ||
            ((long long)right - left == (long long)best->second - best->first &&
             left < best->first)) best = pair<int,int>{left, right};
    }
    return best;
}
vector<double> bruteMedians(const vector<int>& a, int k) {
    vector<double> result;
    if (k <= 0 || (size_t)k > a.size()) return result;
    for (size_t i = 0; i + k <= a.size(); ++i) {
        vector<int> window(a.begin() + i, a.begin() + i + k);
        sort(window.begin(), window.end());
        result.push_back(k % 2 ? window[k / 2] :
            ((long long)window[k / 2 - 1] + window[k / 2]) / 2.0);
    }
    return result;
}
int main() {
    IntMinHeap heap({3,1,5,2,2});
    vector<int> popped;
    while (!heap.empty()) popped.push_back(heap.pop());
    require(popped == vector<int>({1,2,2,3,5}), "bottom-up heap");
    bool rejected = false;
    try { heap.pop(); } catch (const out_of_range&) { rejected = true; }
    require(rejected, "empty heap");
    require(orderedTasks({{2,0,"a"},{1,1,"b"},{1,2,"c"}}) ==
            vector<string>({"b","c","a"}), "comparator and FIFO");
    require(slidingMedians({INT_MIN,INT_MAX},2) == vector<double>{-0.5}, "median overflow");
    require(minimumMeetingRooms({{0,10},{10,20}}) == 1, "touching intervals");
    require(topFrequent({2,2,1,1,3},2) == vector<int>({1,2}), "frequency tie");
    require(smallestCoveringRange({{INT_MIN},{INT_MAX}}) ==
            optional<pair<int,int>>{pair<int,int>{INT_MIN,INT_MAX}}, "range width overflow");
    mt19937 rng(20260921);
    uniform_int_distribution<int> value(-5,5), length(0,12);
    priority_queue<int, vector<int>, greater<int>> referenceHeap;
    for (int step = 0; step < 1000; ++step) {
        if (referenceHeap.empty() || rng() % 2 == 0) {
            int x = value(rng); heap.push(x); referenceHeap.push(x);
        } else {
            require(heap.pop() == referenceHeap.top(), "heap pop"); referenceHeap.pop();
        }
        require(heap.size() == referenceHeap.size(), "heap size");
        if (!heap.empty()) require(heap.top() == referenceHeap.top(), "heap top");
    }
    VersionedMinQueue versioned;
    unordered_map<int,int> live;
    for (int step = 0; step < 1000; ++step) {
        int operation = rng() % 3, id = rng() % 8;
        if (operation == 0) {
            int priority = value(rng); versioned.put(id,priority); live[id]=priority;
        } else if (operation == 1) {
            versioned.cancel(id); live.erase(id);
        } else {
            optional<pair<int,int>> expected;
            for (auto [key, priority] : live)
                if (!expected || tie(priority,key) < tie(expected->second,expected->first))
                    expected = pair<int,int>{key,priority};
            require(versioned.pop() == expected, "versioned snapshots");
            if (expected) live.erase(expected->first);
        }
    }
    for (int run = 0; run < 200; ++run) {
        vector<int> a(length(rng));
        for (int& x : a) x = value(rng);
        int rank = 1 + rng() % 5;
        KthLargestStream stream(rank);
        vector<int> prefix;
        for (int x : a) {
            prefix.push_back(x);
            sort(prefix.begin(), prefix.end(), greater<int>());
            auto actual = stream.add(x);
            if (prefix.size() < (size_t)rank) require(!actual, "insufficient stream");
            else require(actual == optional<int>{prefix[rank-1]}, "stream rank");
        }
        unordered_map<int,int> frequency;
        for (int x : a) ++frequency[x];
        vector<int> ordered;
        for (auto [x,count] : frequency) ordered.push_back(x);
        sort(ordered.begin(),ordered.end(),[&](int x,int y) {
            if (frequency[x] != frequency[y]) return frequency[x] > frequency[y];
            return x < y;
        });
        int k = rng() % (ordered.size()+1);
        auto expectedFrequency = ordered;
        expectedFrequency.resize(k);
        require(topFrequent(a,k) == expectedFrequency, "top frequency");
        int width = a.empty() ? 1 : 1 + rng() % a.size();
        require(slidingMedians(a,width) == bruteMedians(a,width), "window median");
        vector<pair<int,int>> points;
        for (int x : a) points.push_back({x,value(rng)});
        vector<size_t> indices(points.size());
        iota(indices.begin(),indices.end(),0);
        auto distance = [&](size_t i) {
            return 1LL*points[i].first*points[i].first +
                   1LL*points[i].second*points[i].second;
        };
        sort(indices.begin(),indices.end(),[&](size_t i,size_t j) {
            return pair<long long,size_t>{distance(i),i} <
                   pair<long long,size_t>{distance(j),j};
        });
        int pointCount = rng() % (points.size()+1);
        vector<pair<int,int>> expectedPoints;
        for (int i=0;i<pointCount;++i) expectedPoints.push_back(points[indices[i]]);
        require(closestPoints(points,pointCount) == expectedPoints, "closest points");
        vector<vector<int>> rows(3);
        for (auto& row : rows) {
            row.resize(rng()%5);
            for (int& x : row) x=value(rng);
            sort(row.begin(),row.end());
        }
        require(smallestCoveringRange(rows) == bruteRange(rows), "covering range");
        vector<tuple<long long,size_t,size_t>> pairs;
        for (size_t i=0;i<rows[0].size();++i)
            for (size_t j=0;j<rows[1].size();++j)
                pairs.emplace_back((long long)rows[0][i]+rows[1][j],i,j);
        sort(pairs.begin(),pairs.end());
        int requested = rng()%10;
        vector<pair<int,int>> expectedPairs;
        for (size_t p=0;p<pairs.size() && p<(size_t)requested;++p) {
            auto [sum,i,j]=pairs[p];
            expectedPairs.push_back({rows[0][i],rows[1][j]});
        }
        require(smallestPairs(rows[0],rows[1],requested) == expectedPairs, "pair frontier");
        deque<ListNode> storage;
        vector<ListNode*> heads;
        vector<int> flat;
        for (const auto& row : rows) {
            ListNode* head=nullptr; ListNode* tail=nullptr;
            for (int x : row) {
                storage.emplace_back(x);
                ListNode* fresh=&storage.back();
                if (tail) tail->next=fresh; else head=fresh;
                tail=fresh; flat.push_back(x);
            }
            heads.push_back(head);
        }
        ListNode* merged=mergeSortedLists(heads);
        unordered_set<ListNode*> seen;
        vector<int> actualValues;
        for (ListNode* p=merged;p;p=p->next) {
            require(seen.insert(p).second,"list cycle or duplicate node");
            actualValues.push_back(p->val);
        }
        sort(flat.begin(),flat.end());
        require(actualValues==flat && seen.size()==storage.size(),"list merge");
        vector<pair<int,int>> meetings;
        for (int x : a) meetings.push_back({x,x+1+(int)(rng()%5)});
        int needed=0;
        for (auto [start,end] : meetings) {
            int active=0;
            for (auto [s,e] : meetings) active += s<=start && start<e;
            needed=max(needed,active);
        }
        require(minimumMeetingRooms(meetings)==needed,"rooms vs overlap");
        int n=1+rng()%6;
        vector<vector<WeightedEdge>> graph(n);
        const long long INF=1000000000000000LL;
        vector<vector<long long>> distanceMatrix(n,vector<long long>(n,INF));
        for (int i=0;i<n;++i) distanceMatrix[i][i]=0;
        for (int i=0;i<n;++i) for (int j=0;j<n;++j) if (rng()%3==0) {
            int weight=rng()%10;
            graph[i].push_back({j,weight});
            distanceMatrix[i][j]=min(distanceMatrix[i][j],(long long)weight);
        }
        for (int via=0;via<n;++via) for (int i=0;i<n;++i) for (int j=0;j<n;++j)
            distanceMatrix[i][j]=min(distanceMatrix[i][j],
                                    distanceMatrix[i][via]+distanceMatrix[via][j]);
        auto actual=shortestDistances(graph,0);
        for (int i=0;i<n;++i) {
            if (distanceMatrix[0][i]==INF) require(!actual[i],"unreachable");
            else require(actual[i]==optional<long long>{distanceMatrix[0][i]},"Dijkstra vs Floyd");
        }
    }
    cout << "All chapter 8 checks passed" << endl;
}
