#include <bits/stdc++.h>
using namespace std;
#define maxn 500005
inline int read()
{
    char ch = '*';
    int num = 0, f = 1;
    while (!isdigit(ch))
    {
        ch = getchar();
        if (ch == '-')
            f = -1;
    }
    while (isdigit(ch))
    {
        num = num * 10 + ch - '0';
        ch = getchar();
    }
    return num * f;
}
// struct edge {int to,val};
vector<pair<int, int>> e[maxn];
int dis[maxn];
bool vis[maxn];
int fa[maxn];
int n, m, s;
void dfs(int x)
{
    int siz = e[x].size();
    siz--;
    for (int i = 0; i <= siz; i++)
    {
        int v = e[x][i].first;
        if (vis[v] || fa[x] == v)
            continue;
        fa[v] = x;
        dis[v] = dis[x] + e[x][i].second;
        dfs(v);
    }
    return;
}
int main()
{
    n = read();
    s = read();
    int u, v, w;
    for (int i = 1; i < n; i++)
    {
        u = read();
        v = read();
        w = read();
        e[u].push_back(make_pair(v, w));
        e[v].push_back(make_pair(u, w));
    }
    int l = 1, l2 = 1;
    dis[l] = 0;
    dfs(l);
    memset(fa, 0, sizeof(fa));
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[l])
            l = i;
    dis[l] = 0;
    dfs(l);
    for (int i = 1; i <= n; i++)
        if (dis[i] > dis[l2])
            l2 = i;
    //现在l和l2是树的直径的两个端点
    int ans = 0x7fffffff, j = l2;
    for (int i = l2; i; i = fa[i])
    {
        while (fa[j] && dis[i] - dis[fa[j]] <= s)
            j = fa[j];
        ans = min(ans, max(dis[j], dis[l2] - dis[i]));
    }
    for (int i = l2; i; i = fa[i])
        vis[i] = 1;
    for (int i = l2; i; i = fa[i])
        dis[i] = 0, dfs(i);
    for (int i = 1; i <= n; i++)
        ans = max(ans, dis[i]);
    cout << ans << endl;
    return 0;
}