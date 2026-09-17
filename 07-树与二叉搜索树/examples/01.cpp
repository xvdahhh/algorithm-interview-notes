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

struct TreeNode {
    int val; TreeNode *left=nullptr, *right=nullptr;
    explicit TreeNode(int v):val(v){}
};
vector<int> inorder(TreeNode* root) {
    vector<int> ans;
    stack<TreeNode*> st;
    TreeNode* cur=root;
    while (cur || !st.empty()) {
        while (cur) { st.push(cur); cur=cur->left; }
        cur=st.top(); st.pop();
        ans.push_back(cur->val);
        cur=cur->right;
    }
    return ans;
}
