#include <iostream>
#include <algorithm>
using namespace std;
const int N = 110;
using LL = __int128;
int a[N][N];
int n, m;
LL ans;

LL get(int a[]) {
	LL dp[N][N] = {0};
	for(int len = 1; len <= m; len ++) {
		for(int i = 1; i + len - 1 <= m; i ++) {
			int j = i + len - 1;
			dp[i][j] = max(dp[i + 1][j] * 2 + a[i] * 2, dp[i][j - 1] * 2 + a[j] * 2);
		}
	}
	return dp[1][m];
}

void print(LL x)
{
    if(!x) return;
    if(x) print(x/10);
    putchar(x%10+'0');
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) {
		for(int j = 1; j <= m; j ++) {
			cin >> a[i][j];
		}
		ans += get(a[i]);
	}
	print(ans);
	return 0;
}
