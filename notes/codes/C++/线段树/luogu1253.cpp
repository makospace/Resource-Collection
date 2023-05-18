#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e6 + 10;
struct node {
	int l, r;
	long long Max, lazy1, lazy2;
	bool need;
} tr[4 * N];
int n, q;

void build(int id, int l, int r) {
	tr[id] = {l, r, 0, 0, 0};
	if(l == r)	return;
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
}

void spread(int id) {
	if(tr[id].need) {
		tr[id << 1].Max = tr[id].lazy2;
		tr[id << 1 | 1].Max = tr[id].lazy2;
		tr[id << 1].lazy2 = tr[id].lazy2;
		tr[id << 1 | 1].lazy2 = tr[id].lazy2;
		tr[id << 1].need = true;
		tr[id << 1 | 1].need = true;
		tr[id].need = false;
		tr[id].lazy2 = 0;
	}
	if(tr[id].lazy1) {
		tr[id << 1].Max += tr[id].lazy1;
		tr[id << 1 | 1].Max += tr[id].lazy1;
		tr[id << 1].lazy1 += tr[id].lazy1;
		tr[id << 1 | 1].lazy1 += tr[id].lazy1;
		tr[id].lazy1 = 0;
	}
}

void pushup(int id) {
	tr[id].Max = max(tr[id << 1].Max, tr[id << 1 | 1].Max);
}

void add(int id, int l, int r, long long x) {
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].Max += x;
		tr[id].lazy1 += x;
		return;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	spread(id);
	if(l <= mid) add(id << 1, l, r, x);
	if(r > mid)	add(id << 1 | 1, l, r, x);
	pushup(id);
}

void modify(int id, int l, int r, long long x) {
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].Max = x;
		tr[id].lazy2 = x;
		tr[id].lazy1 = 0;
		tr[id].need = true;
		return;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	spread(id);
	if(l <= mid) modify(id << 1, l, r, x);
	if(r > mid)	modify(id << 1 | 1, l, r, x);
	pushup(id);
}

long long query(int id, int l, int r) {
	if(tr[id].l >= l && tr[id].r <= r) {
		return tr[id].Max;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	spread(id);
	long long ans = -1e18;
	if(l <= mid) ans = max(ans, query(id << 1, l, r));
	if(r > mid)	ans = max(ans, query(id << 1 | 1, l, r));
	return ans;
}

int main() {
	cin >> n >> q;
	build(1, 1, n);
	for(int i = 1; i <= n; i++) {
		int x;	cin >> x;
		add(1, i, i, x);
	}
	while(q --) {
		int op, l, r;
		long long x;
		cin >> op;
		if(op == 1) {
			cin >> l >> r >> x;
			modify(1, l, r, x);
		} else if(op == 2) {
			cin >> l >> r >> x;
			add(1, l, r, x);
		} else {
			cin >> l >> r;
			cout << query(1, l, r) << endl;
		}
	}
	return 0;
}



