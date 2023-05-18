#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
//剪枝：dfs搜索顺序，每个节点往下的某个极端情况都难以满足当前局部最优解或者难以达到答案要求
const int N = 40;
int a[N];
int n, x;
int ans = 0;
int backsum[N];

void dfs(int u, int sum) {
	if(sum >= x) ans = ans == 0 ? sum : min(ans, sum);
	if(u == n) return ;
	if(sum >= x) return ;
	if(sum + backsum[u] < x) return ;
	dfs(u + 1, sum + a[u]);
	dfs(u + 1, sum);
}

int main()
{
	cin >> n >> x;
	for(int i = 0; i < n; i ++) cin >> a[i];
	sort(a, a + n);
	reverse(a, a + n);
	for(int i = n - 1; i >= 0; i --) {
		backsum[i] = backsum[i + 1] + a[i];
	}
	dfs(0, 0);
	cout << ans;
	return 0;
}