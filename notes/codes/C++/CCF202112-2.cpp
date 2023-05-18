#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e7 + 10;
int a[N];
int n, m;
long long ans;

int main() {
	cin >> n >> m;
	int r = m / (n + 1);
	for(int i = 1; i <= n; i ++) {
		//找小于等于i的最大下标
		cin >> a[i];
	}
	for(int i = 0, j = 0; i < m; i ++) {
		while(j + 1 <= n && a[j + 1] <= i) j ++;
		ans += abs(j - i / r);
	}
	cout << ans;
	return 0;
}