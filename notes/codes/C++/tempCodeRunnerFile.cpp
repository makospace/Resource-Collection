#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

const int N = 40;
int a[N];
int n, x;
int ans = 0;

void dfs(int u, int sum) {
	if(sum >= x) ans = ans == 0 ? sum : min(ans, sum);
	if(u == n) return ;
	if(sum >= x) return ;
	dfs(u + 1, sum + a[u]);
	dfs(u + 1, sum);
}

int main()
{
	cin >> n >> x;
	for(int i = 0; i < n; i ++) cin >> a[i];
	sort(ans, ans + n);
	reverse(ans, ans + n);
	//从a数组中选出若干个数，使得和在大于等于x的情况下，和最小
	//这个问题可以转化为01背包问题
	//dp[i][j]表示前i个数中选出若干个数，使得和为j的最小值
	//dp[i][j] = min(dp[i - 1][j], dp[i - 1][j - a[i]] + a[i])
	//dp[i][j] = min(dp[i - 1][j], dp[i][j - a[i]] + a[i])
	dfs(0, 0);
	cout << ans;
	return 0;
}