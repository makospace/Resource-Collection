//对于单点查询考虑差分
#include <iostream>
#include <algorithm>
using namespace std;
int n, m;
const int N = 1e5 + 10;
int a[N], d[N];
struct node {
	int l, r;
	long long sum;  //不是区间增加不用lazy标记
	long long lazy; //懒标记，用long long 
}tr[4 * N];

void pushup(int id) {
	tr[id].sum = tr[id * 2].sum + tr[id * 2 + 1].sum;
}

void build(int id, int l, int r) {
	tr[id] = {l, r, 0, 0};
	if(l == r) {
		tr[id].sum = d[l];
		return ;
	}
	int mid = (l + r) / 2;
	build(id * 2, l, mid);
	build(id * 2 + 1, mid + 1, r);
	pushup(id);
}

void spread(int id) {
	if(tr[id].lazy) {
		tr[id * 2].lazy += tr[id].lazy;
		tr[id * 2 + 1].lazy += tr[id].lazy;
		tr[id * 2].sum += tr[id].lazy * (tr[id * 2].r - tr[id * 2].l + 1);
		tr[id * 2 + 1].sum += tr[id].lazy * (tr[id * 2 + 1].r - tr[id * 2 + 1].l + 1);
		tr[id].lazy = 0;
	}
}

void add(int id, int l, int r, int d) {
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].sum += d * (tr[id].r - tr[id].l + 1);
		tr[id].lazy += d;
		return ;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) / 2;
	if(l <= mid) add(id * 2, l, r, d);
	if(r > mid) add(id * 2 + 1, l, r, d);
	pushup(id);
}

long long query(int id, int l, int r) {
	if(tr[id].l >= l && tr[id].r <= r) return tr[id].sum;
	spread(id); //查询的时候也要下传lazy标记(因为要用到子节点的值
	int mid = (tr[id].l + tr[id].r) / 2;
	long long ans = 0;
	if(l <= mid) ans += query(id * 2, l, r);
	if(r > mid) ans += query(id * 2 + 1, l, r);
	return ans;
}

int main() {
	cin >> n >> m;
	for(int i = 1; i <= n; i ++) cin >> a[i];
	for(int i = 1; i <= n; i ++) d[i] = a[i] - a[i - 1];
	build(1, 1, n + 10);
	while(m --) {
		int op, l, r, K, D, p;
		cin >> op;
		if(op == 1) {
			cin >> l >> r >> K >> D;
			//对差分数组的影响是
			add(1, l, l, K);
			add(1, r + 1, r + 1, -(K + (r - l) * D));
			if(l + 1 <= r) add(1, l + 1, r, D);
		} else {
			cin >> p;
			cout << query(1, 1, p) << endl;
		}
	}
	return 0;
}