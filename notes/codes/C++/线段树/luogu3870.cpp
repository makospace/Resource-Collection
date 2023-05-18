#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
struct node {
	int l, r;
	int sum, lazy;
}tr[4 * N];
int n, m;

void build(int id, int l, int r) {
	tr[id] = {l, r, 0};
	if(l == r) return ;
	int mid = (l + r) / 2;
	build(id * 2, l, mid);
	build(id * 2 + 1, mid + 1, r);
}

void spread(int id) {
	if(tr[id].lazy) {
		tr[id * 2].sum = tr[id * 2].r - tr[id * 2].l + 1 - tr[id * 2].sum;
		tr[id * 2 + 1].sum = tr[id * 2 + 1].r - tr[id * 2 + 1].l + 1 - tr[id * 2 + 1].sum;
		tr[id * 2].lazy ^= 1;
		tr[id * 2 + 1].lazy ^= 1;
		tr[id].lazy ^= 1;
	}
}

void pushup(int id) {
	tr[id].sum = tr[id * 2].sum + tr[id * 2 + 1].sum;
}

int query(int id, int l, int r) {
	if(tr[id].l >= l && tr[id].r <= r) {
		return tr[id].sum;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) / 2;
	int ans = 0;
	if(l <= mid) ans += query(id * 2, l, r);
	if(r > mid) ans += query(id * 2 + 1, l, r);
	return ans;
}

void filp(int id, int l, int r) {
	if(tr[id].l >= l && tr[id].r <= r) {
		tr[id].sum = tr[id].r - tr[id].l + 1 - tr[id].sum;
		tr[id].lazy ^= 1;
		return ;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) / 2;
	if(l <= mid) filp(id * 2, l, r);
	if(r > mid) filp(id * 2 + 1, l, r);
	pushup(id);
}

int main() {
	cin >> n >> m;
	build(1, 1, n);
	for(int i = 1; i <= m; i ++) {
		int k, x, y;
		cin >> k >> x >> y;
		if(k == 0) {
			filp(1, x, y);
		} else {
			cout << query(1, x, y) << endl;
		}
	}
	return 0;
}