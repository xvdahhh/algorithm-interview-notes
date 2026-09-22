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

struct RoomAssignment {
    int rooms = 0;
    vector<int> roomForMeeting;
};
RoomAssignment assignMeetingRooms(const vector<pair<int,int>>& meetings) {
    vector<tuple<int,int,int>> ordered;
    RoomAssignment result; result.roomForMeeting.assign(meetings.size(),-1);
    for (int i = 0; i < (int)meetings.size(); ++i) {
        auto [l,r] = meetings[i];
        if (l > r) throw invalid_argument("interval");
        if (l < r) ordered.push_back({l,r,i});
    }
    sort(ordered.begin(),ordered.end());
    using Busy = pair<int,int>; // 结束时刻、房间号
    priority_queue<Busy,vector<Busy>,greater<Busy>> busy;
    priority_queue<int,vector<int>,greater<int>> freeRooms;
    for (auto [start,end,id] : ordered) {
        while (!busy.empty() && busy.top().first <= start) {
            freeRooms.push(busy.top().second); busy.pop();
        }
        int room;
        if (freeRooms.empty()) room = result.rooms++;
        else { room = freeRooms.top(); freeRooms.pop(); }
        result.roomForMeeting[id] = room; busy.push({end,room});
    }
    return result;
}
