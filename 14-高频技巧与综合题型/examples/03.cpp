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

class RandomizedSet {
    vector<int> data;
    unordered_map<int,int> index;
    mt19937 rng{random_device{}()};
public:
    bool insert(int x){
        if(index.count(x)) return false;
        index[x]=(int)data.size(); data.push_back(x); return true;
    }
    bool remove(int x){
        auto it=index.find(x);
        if(it==index.end()) return false;
        int i=it->second,last=data.back();
        data[i]=last; index[last]=i;
        data.pop_back(); index.erase(x); return true;
    }
    int getRandom(){
        if(data.empty()) throw out_of_range("empty set");
        uniform_int_distribution<int> pick(0,(int)data.size()-1);
        return data[pick(rng)];
    }
};
