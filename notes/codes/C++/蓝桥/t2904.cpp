#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<map>
#include<queue>
#include<vector>
#include<cmath>
using namespace std;
const int N = 105;
int f[N][N][N], w[N], s[N];
/*
f[i][j][k]表示第i个人取到的最后一个糖果编号是j，第i-1
个人取到的最后一个糖果编号小于等于k时的最大重量的最小值 
*/
bool vis[N * N];//vis[i]记录存在一段区间满足区间和为i
int main()
{
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++)
	{
		scanf("%d", &w[i]);
		s[i] = s[i - 1] + w[i];
		for(int j = 0; j < i; j ++)
			vis[s[i] - s[j]] = true;
	}
	int ans = 0x3f3f3f3f;
	for(int mn = 1; mn * m <= 2 * s[n]; mn ++)//枚举重量最小值 
	{
		if(!vis[mn]) continue;//剪枝 
		memset(f, 0x3f,sizeof f);
		f[0][0][0] = 0;
		for(int i = 1; i <= m; i ++)//枚举当前更新状态
		for(int k = 0; k <= n; k ++)//枚举第i-1个人选的最后一个糖果编号
		{
			int id = 0;//找到第i-2个人选的最后一个糖果编号
			for(int j = k; j <= n; j ++)//第i个人选的最后一个糖果编号 
			{ 
				if(k > 0) f[i][j][k] = f[i][j][k - 1]; 
				if(s[j] < mn) continue;//每个人选取的最小重量不能小于mn
				//第i个人选的区间是[id + 1,j]
				while(id < k && s[j] - s[id] > mn) id ++;
				if(s[j] - s[id] < mn) id --;
				f[i][j][k] = min(f[i][j][k], max(f[i - 1][k][id], s[j] - s[id]));
			}
		}
		ans = min(ans, f[m][n][n] - mn); 
	}
	printf("%d", ans);
	return 0;
}