#include <iostream>
#include <algorithm>
using namespace std;
int nxt[110], pre[110];
int day[110];
int n, m;
int ans_fast[110], ans_low[110];

int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i ++) {
		cin >> pre[i];
		nxt[pre[i]] = i;
	}	
	for(int i = 1; i <= m; i ++) cin >> day[i];
	bool can = true;
	//求最早开始时间
	for(int i = 1; i <= m; i ++) {
		if(pre[i] == 0) {
			ans_fast[i] = 1;
		} else {
			int cost = 1;
			int j = pre[i];
			while(j) {
				cost += day[j];
				j = pre[j];
			}
			ans_fast[i] = cost;
		}
		if(ans_fast[i] + day[i] - 1 > n) can = false;
		// cout << ans_fast[i] << ' ';
	}
	// 求最晚开始时间
	for(int i = 1; i <= m; i ++) {
		if(nxt[i] == 0) {
			ans_low[i] = n - day[i] + 1;
		} else {
			int cost = 0;
			int j = i;
			while(j) {
				cost += day[j];
				j = nxt[j];
			}
			ans_low[i] = n - cost + 1;
			if(ans_low[i] < 1) can = false;
		}
	}
	int sum = 0;
	for(int i = 1; i <= m; i ++) sum += day[i];
	if(sum > n) can = false;
	for(int i = 1; i <= m; i ++) cout << ans_fast[i] << " ";
	if(can) {
		cout << endl;
		for(int i = 1; i <= m; i ++) cout << ans_low[i] << ' ';
	}
	return 0;
}