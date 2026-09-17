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

struct Student { string name; int score; };
void sortStudents(vector<Student>& students){
    sort(students.begin(),students.end(),
         [](const Student& a,const Student& b){
             if(a.score!=b.score) return a.score>b.score;
             return a.name<b.name;
         });
}
long long sumValues(const vector<int>& a){
    return accumulate(a.begin(),a.end(),0LL);
}
