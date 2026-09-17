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

class LRUCache {
    size_t cap;
    list<pair<int,int>> order;
    unordered_map<int,list<pair<int,int>>::iterator> pos;
public:
    explicit LRUCache(int capacity):cap(max(0,capacity)){}
    LRUCache(const LRUCache&)=delete;
    LRUCache& operator=(const LRUCache&)=delete;
    int get(int key){
        auto it=pos.find(key);
        if(it==pos.end()) return -1;
        order.splice(order.begin(),order,it->second);
        return it->second->second;
    }
    void put(int key,int value){
        auto it=pos.find(key);
        if(it!=pos.end()){
            it->second->second=value;
            order.splice(order.begin(),order,it->second);
            return;
        }
        if(cap==0) return;
        order.emplace_front(key,value);
        pos[key]=order.begin();
        if(order.size()>cap){
            pos.erase(order.back().first);
            order.pop_back();
        }
    }
};
