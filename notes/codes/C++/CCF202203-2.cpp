#include <iostream>
#include <algorithm>
using namespace std;
const int N = 100010;
int n, m, k;
int d[2 * N];

int main() {
	cin >> n >> m >> k;
	for(int i = 0; i < n; i ++) {
		int t, c;
		cin >> t >> c;
		int start = t - (c - 1) - k; //最早的核酸检测时间
		int end = t - k; //最晚的核酸检测时间
		//[start, end] ++
		if(end < 1) continue;
		d[max(1, start)] ++;
		d[end + 1] --;
	}
	for(int i = 2; i < 2 * N; i ++) {
		d[i] += d[i - 1];
	}
	for(int i = 0; i < m; i ++) {
		int time;
		cin >> time;
		cout << d[time] << endl;
	}
	return 0;
}