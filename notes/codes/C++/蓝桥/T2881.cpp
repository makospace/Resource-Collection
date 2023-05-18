#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> PII;

const int N = 20, INF = 1e9;

PII p[N];
int w[N][N], f[1 << N][N];

double get_distance(int i, int j)
{
    int x = p[i].first - p[j].first;
    int y = p[i].second - p[j].second;
    return sqrt(x * x + y * y);
}

int main()
{
    int n, d;
    cin >> n >> d;
    for (int i = 0; i < n; i ++) cin >> p[i].first >> p[i].second;
    
    for (int i = 0; i < n; i ++)
        for (int j = i + 1; j < n; j ++)
        {
            w[i][j] = w[j][i] = get_distance(i, j) * 10000;
            if(w[i][j] > d * 10000) w[i][j] = w[j][i] = INF;
        }
        
    for (int k = 0; k < n; k ++)
        for (int i = 0; i < n; i ++)
            for (int j = 0; j < n; j ++)
                w[i][j] = min(w[i][j], w[i][k] + w[k][j]);
				//先这样求就能避免出现在状态中多次遍历一个点的情况
                
    for (int i = 0; i < 1 << n; i ++)
        for (int j = 0; j < n; j ++)
            f[i][j] = INF;
            
    f[1][0] = 0;
    for (int i = 0; i < 1 << n; i ++)
        for (int j = 0; j < n; j ++)
            if(i >> j & 1)
                for (int k = 0; k < n; k ++)
                    if((i - (1 << j)) >> k & 1)
                        f[i][j] = min(f[i][j], f[i - (1 << j)][k] + w[k][j]);
						
                        
    int ans = INF;
    for (int i = 1; i < n; i ++)
        ans = min(ans, w[i][0] + f[(1 << n) - 1][i]);
        
    printf("%.2f", ans / 10000.0);
    return 0;
}
