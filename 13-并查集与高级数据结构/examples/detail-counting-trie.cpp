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

class CountingTrie {
    struct Node {
        array<int,26> next;
        long long pass = 0, end = 0;
        Node() { next.fill(-1); }
    };
    vector<Node> nodes{Node{}};
    static void validate(const string& s, bool wildcard = false) {
        for (char c : s)
            if (!(c >= 'a' && c <= 'z') && !(wildcard && c == '.'))
                throw invalid_argument("lowercase a-z, or dot in pattern");
    }
    int walk(const string& s) const {
        int u = 0;
        for (char c : s) {
            u = nodes[u].next[c-'a'];
            if (u == -1) return -1;
        }
        return u;
    }
public:
    void insert(const string& word) {
        validate(word);
        if (nodes[0].pass == LLONG_MAX) throw overflow_error("word count");
        vector<int> path{0}; int u = 0;
        for (char c : word) {
            int k = c-'a';
            if (nodes[u].next[k] == -1) {
                int v = (int)nodes.size(); nodes.emplace_back();
                nodes[u].next[k] = v;
            }
            u = nodes[u].next[k]; path.push_back(u);
        }
        for (int v : path) ++nodes[v].pass;
        ++nodes[u].end;
    }
    long long countWord(const string& word) const {
        validate(word); int u = walk(word);
        return u == -1 ? 0 : nodes[u].end;
    }
    long long countPrefix(const string& prefix) const {
        validate(prefix); int u = walk(prefix);
        return u == -1 ? 0 : nodes[u].pass;
    }
    bool eraseOne(const string& word) {
        validate(word);
        int u = walk(word);
        if (u == -1 || nodes[u].end == 0) return false;
        --nodes[u].end;
        u = 0; --nodes[u].pass;
        for (char c : word) { u = nodes[u].next[c-'a']; --nodes[u].pass; }
        return true;
    }
    bool matches(const string& pattern) const {
        validate(pattern,true);
        vector<pair<int,size_t>> stack{{0,0}};
        while (!stack.empty()) {
            auto [u,pos] = stack.back(); stack.pop_back();
            if (nodes[u].pass == 0) continue;
            if (pos == pattern.size()) {
                if (nodes[u].end > 0) return true;
                continue;
            }
            if (pattern[pos] == '.') {
                for (int v : nodes[u].next)
                    if (v != -1 && nodes[v].pass > 0) stack.push_back({v,pos+1});
            } else {
                int v = nodes[u].next[pattern[pos]-'a'];
                if (v != -1) stack.push_back({v,pos+1});
            }
        }
        return false;
    }
};
