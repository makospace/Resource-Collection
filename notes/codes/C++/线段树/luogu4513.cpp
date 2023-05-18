#include <iostream>
#include <algorithm>
using namespace std;
using LL = long long;
const int N = 5e5 + 10;
int n, m;
struct node {
	int l, r;
	LL sum, Lmax, Rmax, Max;
}tr[4 * N];
int a_[N];

void build(int id, int l, int r) {
	tr[id] = {l, r, 0, 0, 0, 0};
	if(l == r) return ;
	int mid = (l + r) >> 1;
	build(id << 1, l, mid);
	build(id << 1 | 1, mid + 1, r);
}

void pushup(int id) {
	tr[id].sum = tr[id << 1].sum + tr[id << 1 | 1].sum;
	tr[id].Lmax = max(tr[id << 1].Lmax, tr[id << 1].sum + tr[id << 1 | 1].Lmax);
	tr[id].Rmax = max(tr[id << 1 | 1].Rmax, tr[id << 1 | 1].sum + tr[id << 1].Rmax);
	tr[id].Max = max(tr[id << 1].Max, tr[id << 1 | 1].Max);
	tr[id].Max = max(tr[id].Max, tr[id << 1].Rmax + tr[id << 1 | 1].Lmax);
}

void pushup(node &res, node &left, node &right) {
	res.sum = left.sum + right.sum;
	res.Lmax = max(left.Lmax, left.sum + right.Lmax);
	res.Rmax = max(right.Rmax, right.sum + left.Rmax);
	res.Max = max(left.Max, right.Max);
	res.Max = max(res.Max, left.Rmax + right.Lmax);
}

void add(int id, int p, int x) {
	if(tr[id].l == tr[id].r) {
		tr[id].sum += x, tr[id].Lmax += x, tr[id].Rmax += x, tr[id].Max += x;
		return ;
	}
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(p <= mid) add(id << 1, p, x);
	else add(id << 1 | 1, p, x);
	pushup(id);
}

node query(int id, int l, int r) { // 查询的真正含义是得到l，r为题目参数的具体结果，这里返回一个值显然是不合适的
	if(tr[id].l >= l && tr[id].r <= r) return tr[id];
	int mid = (tr[id].l + tr[id].r) >> 1;
	if(r <= mid) return query(id << 1, l, r);
	else if(l > mid) return query(id << 1 | 1, l, r);
	else {
		node left = query(id << 1, l, r);  //这里query等价于query(id << 1, l, mid);
		node right = query(id << 1 | 1, l, r); //这里query等价于query(id << 1 | 1, mid + 1, r);
		node res;
		pushup(res, left, right);
		return res;
	}
}

int main() {
	cin >> n >> m;
	build(1, 1, n);
	for(int i = 1; i <= n; i ++) {
		cin >> a_[i];
		add(1, i, a_[i]);
	}
	while(m --) {
		int k, a, b;
		cin >> k;
		if(k == 1) {
			cin >> a >> b;
			if(a > b) swap(a, b);
			cout << query(1, a, b).Max << endl;
		} else {
			cin >> a >> b;
			add(1, a, -a_[a] + b);
			a_[a] = b;
		}
	}
	return 0;
}