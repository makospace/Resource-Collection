#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
bool st[N];
//是常量或者已经被初始化的变量
int n, k;

int main() {
	cin >> n >> k;
	st[0] = true;
	int ans = 0;
	while(k --) {
		int x, y;
		cin >> x >> y;
		if(!st[y]) ans ++;
		st[x] = true;
	}
	cout << ans;
	return 0;
}