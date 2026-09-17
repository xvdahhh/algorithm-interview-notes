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

class Trie {
    struct Node {
        array<int,26> next;
        bool terminal=false;
        Node(){ next.fill(-1); }
    };
    vector<Node> nodes{Node{}};
    static int letter(char c) {
        if(c<'a'||c>'z') throw invalid_argument("lowercase a-z only");
        return c-'a';
    }
    int walk(const string& s) const {
        int u=0;
        for(char c:s){
            int v=nodes[u].next[letter(c)];
            if(v==-1) return -1;
            u=v;
        }
        return u;
    }
public:
    void insert(const string& s){
        int u=0;
        for(char c:s){
            int k=letter(c);
            if(nodes[u].next[k]==-1){
                int v=(int)nodes.size();
                nodes.emplace_back();
                nodes[u].next[k]=v;
            }
            u=nodes[u].next[k];
        }
        nodes[u].terminal=true;
    }
    bool search(const string& s) const {
        int u=walk(s); return u!=-1 && nodes[u].terminal;
    }
    bool startsWith(const string& s) const { return walk(s)!=-1; }
};
