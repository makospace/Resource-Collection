// #include <iostream>
// #include <algorithm>
// using namespace std;
// const int N = 1e5 + 10;
// using LL = long long;
// struct node {
// 	int l, r;
// 	LL sum, add = 0, mul = 1;
// }tr[4 * N];
// int n, m, p;

// void build(int id, int l, int r) {
// 	tr[id] = {l, r, 0, 0, 1};
// 	if(l == r) return;
// 	int mid = (l + r) >> 1;
// 	build(id << 1, l, mid);
// 	build(id << 1 | 1, mid + 1, r);
// }

// void pushup(int id) {
// 	tr[id].sum = (tr[id << 1].sum + tr[id << 1 | 1].sum) % p;
// }

// void spread(int id) {
// 	tr[id << 1].sum = (tr[id << 1].sum * tr[id].mul % p + tr[id].add * (tr[id << 1].r - tr[id << 1].l + 1) % p) % p;
// 	tr[id << 1 | 1].sum = (tr[id << 1 | 1].sum * tr[id].mul % p + tr[id].add * (tr[id << 1 | 1].r - tr[id << 1 | 1].l + 1) % p) % p;
	
// 	tr[id << 1].mul = (tr[id << 1].mul * tr[id].mul) % p;
// 	tr[id << 1 | 1].mul = (tr[id << 1 | 1].mul * tr[id].mul) % p;

// 	tr[id << 1].add = (tr[id << 1].add * tr[id].mul + tr[id].add) % p;
// 	tr[id << 1 | 1].add = (tr[id << 1 | 1].add * tr[id].mul + tr[id].add) % p;

// 	tr[id].mul = 1;
// 	tr[id].add = 0;
// }

// void add(int id, int l, int r, int x) {
// 	if(tr[id].l >= l && tr[id].r <= r) {
// 		tr[id].sum = (tr[id].sum + (tr[id].r - tr[id].l + 1) * x % p) % p;
// 		tr[id].add = (tr[id].add + x) % p;
// 		return;
// 	}
// 	spread(id);
// 	int mid = (tr[id].l + tr[id].r) >> 1;
// 	if(l <= mid) add(id << 1, l, r, x);
// 	if(r > mid) add(id << 1 | 1, l, r, x);
// 	pushup(id);
// }

// void mul(int id, int l, int r, int x) {
// 	if(tr[id].l >= l && tr[id].r <= r) {
// 		tr[id].sum = (tr[id].sum * x) % p;
// 		tr[id].add = (tr[id].add * x) % p;
// 		tr[id].mul = (tr[id].mul * x) % p;
// 		return;
// 	}
// 	spread(id);
// 	int mid = (tr[id].l + tr[id].r) >> 1;
// 	if(l <= mid) mul(id << 1, l, r, x);
// 	if(r > mid) mul(id << 1 | 1, l, r, x);
// 	pushup(id);
// }

// LL query(int id, int l, int r) { 
// 	if(tr[id].l >= l && tr[id].r <= r) {
// 		return tr[id].sum;
// 	}
// 	spread(id);
// 	int mid = (tr[id].l + tr[id].r) >> 1;
// 	LL ans = 0;
// 	if(l <= mid) ans = (ans + query(id << 1, l, r)) % p;
// 	if(r > mid) ans = (ans + query(id << 1 | 1, l, r)) % p;
// 	return ans;
// }

// int main() {
// 	cin >> n >> m >> p;
// 	build(1, 1, n);
// 	for(int i = 1; i <= n; i ++ ) {
// 		int x;	cin >> x;
// 		add(1, i, i, x);
// 	}
// 	while(m --) {
// 		int op, x, y, k;
// 		cin >> op;
// 		if(op == 1) {
// 			cin >> x >> y >> k;
// 			mul(1, x, y, k);
// 		} else if(op == 2) {
// 			cin >> x >> y >> k;
// 			add(1, x, y, k);
// 		} else {
// 			cin >> x >> y;
// 			cout << query(1, x, y) << endl;
// 		}
// 	}
// 	return 0;
// }


#include <iostream>
#include <algorithm>
using namespace std;
const int N = 1e5 + 10;
using LL = long long;
struct node {
	int l, r;
	LL sum, add = 0, mul = 1;
}tr[4 * N];
int n, m, p;

void build(int id, int l, int r) {
	tr[id] = {l, r, 0, 0, 1};
	if(l == r) return;
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
}

void pushup(int id) {
	tr[id].sum = (tr[id << 1].sum + tr[id << 1 | 1].sum) % p;
}

void spread(int id) {
	if(tr[id].sum != 1) {
		tr[id << 1].sum = (tr[id << 1].sum * tr[id].mul) % p;
		tr[id << 1 | 1].sum = (tr[id << 1 | 1].sum * tr[id].mul) % p;
		tr[id << 1].mul = (tr[id << 1].mul * tr[id].mul) % p;
		tr[id << 1 | 1].mul = (tr[id << 1 | 1].mul * tr[id].mul) % p;
		tr[id].mul = 1;
	}
	if(tr[id].add) {
		tr[id << 1].sum = (tr[id << 1].sum + (tr[id << 1].r - tr[id << 1].l + 1) * tr[id].add % p) % p;
		tr[id << 1 | 1].sum = (tr[id << 1 | 1].sum + (tr[id << 1 | 1].r - tr[id << 1 | 1].l + 1) * tr[id].add % p) % p;
		tr[id << 1].add = (tr[id << 1].add + tr[id].add) % p;
		tr[id << 1 | 1].add = (tr[id << 1 | 1].add + tr[id].add) % p;
		tr[id].add = 0;
	} 
}

void add(int id, int l, int r, int x) {
	if(tr[id].l >= l && tr[id].r <= r) {
		spread(id);
		tr[id].sum = (tr[id].sum + (tr[id].r - tr[id].l + 1) * x % p) % p;
		tr[id].add = (tr[id].add + x) % p;
		return;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(l <= mid) add(id << 1, l, r, x);
	if(r > mid) add(id << 1 | 1, l, r, x);
	pushup(id);
}

void mul(int id, int l, int r, int x) {
	if(tr[id].l >= l && tr[id].r <= r) {
		spread(id);
		tr[id].sum = (tr[id].sum * x) % p;
		tr[id].mul = (tr[id].mul * x) % p;
		return;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(l <= mid) mul(id << 1, l, r, x);
	if(r > mid) mul(id << 1 | 1, l, r, x);
	pushup(id);
}

LL query(int id, int l, int r) { 
	if(tr[id].l >= l && tr[id].r <= r) {
		return tr[id].sum;
	}
	spread(id);
	int mid = (tr[id].l + tr[id].r) >> 1;
	LL ans = 0;
	if(l <= mid) ans = (ans + query(id << 1, l, r)) % p;
	if(r > mid) ans = (ans + query(id << 1 | 1, l, r)) % p;
	return ans;
}

int main() {
	cin >> n >> m >> p;
	build(1, 1, n);
	for(int i = 1; i <= n; i ++ ) {
		int x;	cin >> x;
		add(1, i, i, x);
	}
	while(m --) {
		int op, x, y, k;
		cin >> op;
		if(op == 1) {
			cin >> x >> y >> k;
			mul(1, x, y, k);
		} else if(op == 2) {
			cin >> x >> y >> k;
			add(1, x, y, k);
		} else {
			cin >> x >> y;
			cout << query(1, x, y) << endl;
		}
	}
	return 0;
}
