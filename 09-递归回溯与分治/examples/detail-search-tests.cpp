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

#include <set>

vector<vector<int>> chooseK(int n, int k) {
    if (n < 0 || n > 20 || k < 0 || k > n)
        throw invalid_argument("require 0 <= k <= n <= 20");
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int)> dfs = [&](int start) {
        int need = k - (int)path.size();
        if (need == 0) { answer.push_back(path); return; }
        for (int value = start; value <= n - need + 1; ++value) {
            path.push_back(value);
            dfs(value + 1);
            path.pop_back();
        }
    };
    dfs(1);
    return answer;
}

vector<vector<int>> combinationUnlimited(vector<int> candidates, int target) {
    if (target < 0 || target > 100 || candidates.size() > 20)
        throw invalid_argument("unsupported target or candidate count");
    for (int value : candidates)
        if (value <= 0) throw invalid_argument("positive candidates required");
    sort(candidates.begin(), candidates.end());
    candidates.erase(unique(candidates.begin(), candidates.end()), candidates.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int,int)> dfs = [&](int start, int remaining) {
        if (remaining == 0) { answer.push_back(path); return; }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (candidates[i] > remaining) break;
            path.push_back(candidates[i]);
            dfs(i, remaining - candidates[i]);
            path.pop_back();
        }
    };
    dfs(0, target);
    return answer;
}

vector<vector<int>> combinationOnce(vector<int> candidates, int target) {
    if (target < 0 || target > 100 || candidates.size() > 20)
        throw invalid_argument("unsupported target or candidate count");
    for (int value : candidates)
        if (value <= 0) throw invalid_argument("positive candidates required");
    sort(candidates.begin(), candidates.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int,int)> dfs = [&](int start, int remaining) {
        if (remaining == 0) { answer.push_back(path); return; }
        for (int i = start; i < (int)candidates.size(); ++i) {
            if (i > start && candidates[i] == candidates[i - 1]) continue;
            if (candidates[i] > remaining) break;
            path.push_back(candidates[i]);
            dfs(i + 1, remaining - candidates[i]);
            path.pop_back();
        }
    };
    dfs(0, target);
    return answer;
}

vector<vector<int>> uniqueSubsets(vector<int> a) {
    if (a.size() > 20) throw invalid_argument("too many elements");
    sort(a.begin(), a.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(int)> dfs = [&](int start) {
        answer.push_back(path);
        for (int i = start; i < (int)a.size(); ++i) {
            if (i > start && a[i] == a[i - 1]) continue;
            path.push_back(a[i]); dfs(i + 1); path.pop_back();
        }
    };
    dfs(0);
    return answer;
}

vector<vector<int>> frequencyPermutations(vector<int> a) {
    if (a.size() > 9) throw invalid_argument("permutation output too large");
    sort(a.begin(), a.end());
    vector<int> values, count;
    for (int x : a) {
        if (values.empty() || values.back() != x) {
            values.push_back(x); count.push_back(1);
        } else ++count.back();
    }
    vector<vector<int>> answer;
    vector<int> path;
    function<void()> dfs = [&] {
        if (path.size() == a.size()) { answer.push_back(path); return; }
        for (size_t i = 0; i < values.size(); ++i) {
            if (count[i] == 0) continue;
            --count[i]; path.push_back(values[i]);
            dfs();
            path.pop_back(); ++count[i];
        }
    };
    dfs();
    return answer;
}

vector<string> phoneLetters(const string& digits) {
    const array<string, 10> letters{"", "", "abc", "def", "ghi", "jkl",
                                  "mno", "pqrs", "tuv", "wxyz"};
    if (digits.size() > 8) throw invalid_argument("output too large");
    for (char c : digits)
        if (c < '2' || c > '9') throw invalid_argument("digits 2..9 required");
    if (digits.empty()) return {};
    vector<string> answer;
    string path;
    function<void(size_t)> dfs = [&](size_t index) {
        if (index == digits.size()) { answer.push_back(path); return; }
        for (char c : letters[digits[index] - '0']) {
            path.push_back(c); dfs(index + 1); path.pop_back();
        }
    };
    dfs(0);
    return answer;
}

vector<vector<string>> solveNQueens(int n) {
    if (n < 0 || n > 12) throw invalid_argument("require 0 <= n <= 12");
    if (n == 0) return {{}};
    vector<vector<string>> answer;
    vector<string> board(n, string(n, '.'));
    vector<bool> column(n, false), down(2*n-1, false), up(2*n-1, false);
    function<void(int)> dfs = [&](int row) {
        if (row == n) { answer.push_back(board); return; }
        for (int col = 0; col < n; ++col) {
            int d = row - col + n - 1, u = row + col;
            if (column[col] || down[d] || up[u]) continue;
            board[row][col] = 'Q';
            column[col] = down[d] = up[u] = true;
            dfs(row + 1);
            column[col] = down[d] = up[u] = false;
            board[row][col] = '.';
        }
    };
    dfs(0);
    return answer;
}

bool wordExists(const vector<string>& board, const string& word) {
    if (board.empty()) return word.empty();
    size_t columns = board[0].size();
    for (const auto& row : board)
        if (row.size() != columns) throw invalid_argument("rectangular board required");
    if (board.size() > 20 || columns > 20)
        throw invalid_argument("board too large for this example");
    if (word.empty()) return true;
    if (columns == 0 || word.size() > board.size()*columns) return false;
    array<int,256> available{}, needed{};
    for (const auto& row : board)
        for (unsigned char c : row) ++available[c];
    for (unsigned char c : word)
        if (++needed[c] > available[c]) return false;
    int rows = (int)board.size(), cols = (int)columns;
    vector<vector<bool>> used(rows, vector<bool>(cols, false));
    const int dr[4] = {-1,1,0,0}, dc[4] = {0,0,-1,1};
    function<bool(int,int,size_t)> dfs = [&](int r,int c,size_t index) {
        if (used[r][c] || board[r][c] != word[index]) return false;
        if (index + 1 == word.size()) return true;
        used[r][c] = true;
        bool found = false;
        for (int direction=0; direction<4 && !found; ++direction) {
            int nr=r+dr[direction], nc=c+dc[direction];
            if (nr>=0 && nr<rows && nc>=0 && nc<cols)
                found = dfs(nr,nc,index+1);
        }
        used[r][c] = false;
        return found;
    };
    for (int r=0;r<rows;++r)
        for (int c=0;c<cols;++c)
            if (dfs(r,c,0)) return true;
    return false;
}

bool solveSudoku(vector<string>& board) {
    if (board.size()!=9) throw invalid_argument("9 rows required");
    for (const auto& line:board)
        if (line.size()!=9) throw invalid_argument("9 columns required");
    array<unsigned,9> row{}, col{}, box{};
    vector<pair<int,int>> empty;
    for (int r=0;r<9;++r) for (int c=0;c<9;++c) {
        if (board[r][c]=='.') { empty.push_back({r,c}); continue; }
        if (board[r][c]<'1' || board[r][c]>'9') throw invalid_argument("bad symbol");
        unsigned bit=1U<<(board[r][c]-'1');
        int b=(r/3)*3+c/3;
        if ((row[r]|col[c]|box[b])&bit) throw invalid_argument("conflicting clues");
        row[r]|=bit; col[c]|=bit; box[b]|=bit;
    }
    auto candidates = [&](int r,int c) {
        return 511U & ~(row[r]|col[c]|box[(r/3)*3+c/3]);
    };
    auto countBits = [](unsigned x) {
        int count=0;
        while (x) { x&=x-1; ++count; }
        return count;
    };
    function<bool(size_t)> dfs = [&](size_t index) {
        if (index==empty.size()) return true;
        size_t best=index;
        int minimum=10;
        for (size_t i=index;i<empty.size();++i) {
            auto [r,c]=empty[i];
            int count=countBits(candidates(r,c));
            if (count<minimum) { minimum=count; best=i; }
        }
        if (minimum==0) return false;
        swap(empty[index],empty[best]);
        auto [r,c]=empty[index];
        int b=(r/3)*3+c/3;
        unsigned options=candidates(r,c);
        for (int digit=0;digit<9;++digit) {
            unsigned bit=1U<<digit;
            if (!(options&bit)) continue;
            row[r]|=bit; col[c]|=bit; box[b]|=bit;
            board[r][c]=char('1'+digit);
            if (dfs(index+1)) return true;
            board[r][c]='.';
            row[r]^=bit; col[c]^=bit; box[b]^=bit;
        }
        swap(empty[index],empty[best]);
        return false;
    };
    return dfs(0);
}

bool wordBreakMemo(const string& text, const vector<string>& dictionary) {
    if (text.size() > 10000) throw invalid_argument("text too large");
    for (const auto& word : dictionary)
        if (word.empty()) throw invalid_argument("empty word forbidden");
    vector<int> memo(text.size() + 1, -1);
    memo[text.size()] = 1;
    function<bool(size_t)> dfs = [&](size_t start) {
        if (memo[start] != -1) return memo[start] != 0;
        for (const string& word : dictionary) {
            if (word.size() <= text.size() - start &&
                text.compare(start, word.size(), word) == 0 &&
                dfs(start + word.size())) {
                memo[start] = 1;
                return true;
            }
        }
        memo[start] = 0;
        return false;
    };
    return dfs(0);
}

vector<long long> expressionResults(const string& expression) {
    vector<int> numbers;
    vector<char> operators;
    size_t pos = 0;
    while (pos < expression.size()) {
        if (expression[pos] < '0' || expression[pos] > '9')
            throw invalid_argument("expected nonnegative integer");
        int value = 0;
        while (pos < expression.size() && expression[pos] >= '0' && expression[pos] <= '9') {
            int digit = expression[pos++] - '0';
            if (value > (100 - digit) / 10) throw invalid_argument("number exceeds 100");
            value = value * 10 + digit;
        }
        numbers.push_back(value);
        if (numbers.size() > 8) throw invalid_argument("too many operands");
        if (pos == expression.size()) break;
        char op = expression[pos++];
        if (op != '+' && op != '-' && op != '*') throw invalid_argument("bad operator");
        operators.push_back(op);
        if (pos == expression.size()) throw invalid_argument("missing operand");
    }
    if (numbers.empty()) throw invalid_argument("empty expression");
    int n = (int)numbers.size();
    vector<vector<vector<long long>>> memo(n, vector<vector<long long>>(n));
    vector<vector<bool>> ready(n, vector<bool>(n, false));
    function<const vector<long long>&(int,int)> solve =
        [&](int left, int right) -> const vector<long long>& {
            if (ready[left][right]) return memo[left][right];
            auto& result = memo[left][right];
            if (left == right) result.push_back(numbers[left]);
            else for (int split = left; split < right; ++split) {
                const auto& a = solve(left, split);
                const auto& b = solve(split + 1, right);
                for (long long x : a) for (long long y : b) {
                    char op = operators[split];
                    if (op == '+') result.push_back(x + y);
                    else if (op == '-') result.push_back(x - y);
                    else result.push_back(x * y);
                }
            }
            ready[left][right] = true;
            return result;
        };
    return solve(0, n - 1);
}

struct SegmentSummary {
    long long sum, prefix, suffix, best;
};
SegmentSummary summarizeSegment(const vector<int>& a, int left, int right) {
    if (right - left == 1) {
        long long value = a[left];
        return {value, value, value, value};
    }
    int middle = left + (right - left) / 2;
    auto l = summarizeSegment(a, left, middle);
    auto r = summarizeSegment(a, middle, right);
    return {l.sum + r.sum,
            max(l.prefix, l.sum + r.prefix),
            max(r.suffix, r.sum + l.suffix),
            max({l.best, r.best, l.suffix + r.prefix})};
}
optional<long long> maximumSubarrayDivide(const vector<int>& a) {
    if (a.size() > 100000) throw invalid_argument("array too large");
    for (int value : a)
        if (value < -1000000000 || value > 1000000000)
            throw invalid_argument("value outside supported range");
    if (a.empty()) return nullopt;
    return summarizeSegment(a, 0, (int)a.size()).best;
}

void require(bool ok, const string& message) {
    if (!ok) throw runtime_error(message);
}
vector<vector<int>> canonical(vector<vector<int>> value) {
    sort(value.begin(), value.end());
    return value;
}
vector<vector<int>> bruteSubsets(vector<int> a, optional<int> target = nullopt) {
    sort(a.begin(),a.end());
    set<vector<int>> answer;
    for (unsigned mask=0;mask<(1U<<a.size());++mask) {
        vector<int> path;
        int sum=0;
        for (size_t i=0;i<a.size();++i) if (mask&(1U<<i)) {
            path.push_back(a[i]); sum+=a[i];
        }
        if (!target || sum==*target) answer.insert(path);
    }
    return {answer.begin(),answer.end()};
}
vector<vector<int>> bruteUnlimited(vector<int> candidates,int target) {
    sort(candidates.begin(),candidates.end());
    candidates.erase(unique(candidates.begin(),candidates.end()),candidates.end());
    vector<vector<int>> answer;
    vector<int> path;
    function<void(size_t,int)> dfs=[&](size_t index,int remaining) {
        if (index==candidates.size()) {
            if (remaining==0) answer.push_back(path);
            return;
        }
        size_t saved=path.size();
        int value=candidates[index];
        for (int count=0;count<=remaining/value;++count) {
            path.resize(saved);
            path.insert(path.end(),count,value);
            dfs(index+1,remaining-count*value);
        }
        path.resize(saved);
    };
    dfs(0,target);
    return canonical(answer);
}
bool bruteWord(const vector<string>& board,const string& word) {
    if (word.empty()) return true;
    int rows=(int)board.size(),cols=(int)board[0].size();
    function<bool(int,size_t,unsigned)> dfs=[&](int position,size_t index,unsigned used) {
        if ((used&(1U<<position)) || board[position/cols][position%cols]!=word[index])
            return false;
        if (index+1==word.size()) return true;
        used|=1U<<position;
        for (int next=0;next<rows*cols;++next)
            if (abs(position/cols-next/cols)+abs(position%cols-next%cols)==1 &&
                dfs(next,index+1,used)) return true;
        return false;
    };
    for (int position=0;position<rows*cols;++position)
        if (dfs(position,0,0)) return true;
    return false;
}
bool validSudokuSolution(const vector<string>& board) {
    for (const auto& row:board) for (char c:row) if (c<'1'||c>'9') return false;
    for (int i=0;i<9;++i) {
        unsigned row=0,col=0,box=0;
        for (int j=0;j<9;++j) {
            row|=1U<<(board[i][j]-'1');
            col|=1U<<(board[j][i]-'1');
            box|=1U<<(board[(i/3)*3+j/3][(i%3)*3+j%3]-'1');
        }
        if (row!=511 || col!=511 || box!=511) return false;
    }
    return true;
}
int main() {
    require(chooseK(0,0)==vector<vector<int>>{{}}, "empty combination");
    require(uniqueSubsets({})==vector<vector<int>>{{}}, "empty subset");
    require(frequencyPermutations({})==vector<vector<int>>{{}}, "empty permutation");
    require(phoneLetters("").empty() && phoneLetters("23").size()==9, "phone contract");
    require(canonical(combinationOnce({1,1,2},2))==vector<vector<int>>({{1,1},{2}}),
            "same-level duplicate removal");
    require(!maximumSubarrayDivide({}), "empty maximum subarray");
    require(maximumSubarrayDivide({-5,-2,-8})==optional<long long>{-2}, "all negative");
    auto expression=expressionResults("2*3-4*5");
    sort(expression.begin(),expression.end());
    require(expression==vector<long long>({-34,-14,-10,-10,10}), "expression multiplicities");
    require(expressionResults("100")==vector<long long>{100}, "single operand");
    bool rejected=false;
    try { (void)combinationUnlimited({0,1},3); }
    catch (const invalid_argument&) { rejected=true; }
    require(rejected,"nonpositive unlimited choice");
    const int queenCounts[]={1,1,0,0,2,10,4};
    for (int n=0;n<=6;++n) {
        auto boards=solveNQueens(n);
        require(boards.size()==(size_t)queenCounts[n],"queen count");
        set<vector<string>> distinct(boards.begin(),boards.end());
        require(distinct.size()==boards.size(),"queen duplicates");
        for (const auto& board:boards) {
            set<int> cols,down,up;
            for (int r=0;r<n;++r) {
                int found=0;
                for (int c=0;c<n;++c) if (board[r][c]=='Q') {
                    ++found;
                    require(cols.insert(c).second && down.insert(r-c).second &&
                            up.insert(r+c).second,"queen attack");
                }
                require(found==1,"one queen per row");
            }
        }
    }
    mt19937 rng(20260921);
    for (int run=0;run<200;++run) {
        int n=rng()%8;
        vector<int> a(n);
        for (int& x:a) x=1+rng()%3;
        int target=rng()%9;
        require(canonical(uniqueSubsets(a))==bruteSubsets(a),"unique subsets");
        require(canonical(combinationOnce(a,target))==bruteSubsets(a,target),"single use sum");
        require(canonical(combinationUnlimited(a,target))==bruteUnlimited(a,target),"reuse sum");
        auto perm=a;
        sort(perm.begin(),perm.end());
        vector<vector<int>> expectedPerm;
        do { expectedPerm.push_back(perm); } while (next_permutation(perm.begin(),perm.end()));
        require(canonical(frequencyPermutations(a))==expectedPerm,"permutations");
        int k=rng()%(n+1);
        vector<int> range(n);
        iota(range.begin(),range.end(),1);
        auto subsets=bruteSubsets(range);
        vector<vector<int>> expectedChoose;
        for (auto& subset:subsets) if ((int)subset.size()==k) expectedChoose.push_back(subset);
        require(canonical(chooseK(n,k))==expectedChoose,"choose k");
        vector<int> values(n);
        for (int& x:values) x=(int)(rng()%11)-5;
        optional<long long> bruteBest;
        for (int l=0;l<n;++l) {
            long long sum=0;
            for (int r=l;r<n;++r) {
                sum+=values[r];
                if (!bruteBest || sum>*bruteBest) bruteBest=sum;
            }
        }
        require(maximumSubarrayDivide(values)==bruteBest,"segment merge");
        vector<string> board(2,string(3,'a'));
        for (auto& row:board) for (char& c:row) c=char('a'+rng()%2);
        string word(rng()%8,'a');
        for (char& c:word) c=char('a'+rng()%2);
        auto saved=board;
        require(wordExists(board,word)==bruteWord(board,word),"word path");
        require(board==saved,"word board unchanged");
        string text(rng()%9,'a');
        for (char& c:text) c=char('a'+rng()%2);
        vector<string> dictionary={"a","ab","ba"};
        vector<bool> reachable(text.size()+1,false);
        reachable[0]=true;
        for (size_t i=0;i<text.size();++i) if (reachable[i])
            for (const auto& token:dictionary)
                if (i+token.size()<=text.size() && text.substr(i,token.size())==token)
                    reachable[i+token.size()]=true;
        require(wordBreakMemo(text,dictionary)==reachable.back(),"word break");
    }
    const vector<string> solved={"534678912","672195348","198342567",
                                "859761423","426853791","713924856",
                                "961537284","287419635","345286179"};
    for (int run=0;run<20;++run) {
        auto puzzle=solved;
        for (int i=0;i<25;++i) puzzle[rng()%9][rng()%9]='.';
        auto clues=puzzle;
        require(solveSudoku(puzzle) && validSudokuSolution(puzzle),"Sudoku solution");
        for (int r=0;r<9;++r) for (int c=0;c<9;++c)
            if (clues[r][c]!='.') require(puzzle[r][c]==clues[r][c],"clue preserved");
    }
    vector<string> impossible(9,string(9,'.'));
    impossible[0]="12345678.";
    impossible[1]="........9";
    auto original=impossible;
    require(!solveSudoku(impossible) && impossible==original,"unsatisfiable rollback");
    cout << "All chapter 9 checks passed" << endl;
}
