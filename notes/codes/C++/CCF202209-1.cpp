#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
using LL = long long;

const int N = 30;
int ans[N], a[N];
int n;
LL m;
LL c[N], d[N];
//d是矩阵的右侧常数

int main()
{
	c[0] = 1;
	d[0] = 0;
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];  //输入每道题的选项个数
	for(int i = 1; i <= n; i ++) c[i] = c[i - 1] * a[i];  //选项个数的前缀积
	for(int i = 1; i <= n; i ++) {
		d[i] = m % c[i];
		LL tmp = d[i] - d[i - 1];
		ans[i] = tmp / c[i - 1];
	}
	for(int i = 1; i <= n; i ++) {
		cout << ans[i] << " ";
	}
}