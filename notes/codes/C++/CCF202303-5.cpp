#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <bitset>
#include <vector>
using namespace std;
const int N = 200010;
using bits = bitset<N>;
using PII = pair<int, int>;
unordered_map<int, bits> cnts; //以L为左端点的右端点数目:cnts[L]
vector<PII> lines;
int n, m;
unordered_set<int> st;
//不存在包含关系，那么左端点和右端点就不会相等

bits dfs(int u) {
    if(st.count(u)) return cnts[u];
    //找到以lines[u]起始的最大长度
    bits res;
    res.set(1 << lines[u].second);
    for(int i = u + 1; i < m; i ++) {
        if(lines[i].first > lines[u].second) break;
        else if(lines[i].second > lines[u].second) {
            res |= dfs(i);
        }
    }
    st.insert(u);
    return cnts[u] = res;
}

int main() {
    cin >> n >> m;
    for(int i = 0; i < m; i ++) {
        int l, r;
        cin >> l >> r;
        lines.push_back({l, r + 1});
        //包括左不包括右
    }
    sort(lines.begin(), lines.end(), [](PII& a, PII& b) {
        return a.first < b.first || a.first == b.first && a.second < b.second;
    });
    //完成从小到大排序
    long long ans = 0;
    for(int i = 0; i < m; i ++) {
        dfs(i);
    }
    for(auto it : cnts) {
        ans += it.second.count();
    }
    cout << ans;
    return 0;
}