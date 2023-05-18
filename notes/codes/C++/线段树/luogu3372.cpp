#include <iostream>
#include <algorithm>
using namespace std;

const int N = 1e5 + 10;
int n, m;
struct node {
	int l, r;
	long long sum, lazy;
}tr[4 * N];

void pushup(int id) {
	tr[id].sum = tr[id << 1].sum + tr[id << 1 | 1].sum;
} 

void build(int id, int l, int r) {
	tr[id] = {l, r, 0};
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
}

void spread(int id) {
	//下传懒标记
	if(tr[id].lazy) {
		tr[id << 1].lazy += tr[id].lazy;
		tr[id << 1 | 1].lazy += tr[id].lazy;
		tr[id << 1].sum += (tr[id << 1].r - tr[id << 1].l + 1) * tr[id].lazy;
		tr[id << 1 | 1].sum += (tr[id << 1 | 1].r - tr[id << 1 | 1].l + 1) * tr[id].lazy;
		tr[id].lazy = 0;
	}
}

void add(int id, int l, int r, int x) {  //在l,r上加上x
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].sum = tr[id].sum + (tr[id].r - tr[id].l + 1) * x;
		tr[id].lazy += x;
		return ;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	spread(id); //下传懒标记
	if(l <= mid) add(id << 1, l, r, x);
	if(r > mid) add(id << 1 | 1, l, r, x);
	pushup(id);
}

long long query(int id, int l, int r) {
	if(tr[id].l >= l && tr[id].r <= r) {
		return tr[id].sum;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) >> 1;
	long long ans = 0;
	if(l <= mid) ans += query(id << 1, l, r);
	if(r > mid) ans += query(id << 1 | 1, l, r);
	return ans;
}

int main() {
	cin >> n >> m;
	build(1, 1, n);
	for(int i = 1; i <= n; i ++) {
		int x;	cin >> x;
		add(1, i, i, x);
	}
	while(m --) {
		int k, x, y;
		cin >> k >> x >> y;
		if(k == 1) {
			int d; cin >> d;
			add(1, x, y, d);
		} else {
			cout << query(1, x, y) << endl;
		}
	}
	return 0;
}