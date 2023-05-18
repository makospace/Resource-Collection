#include <iostream>
#include <vector>
#include <climits>
using namespace std;
const int N = 310;
struct node {
	int deep;
	bool select;
	vector<int> child;
	int sum;
} nodes[N];
int n, m;
bool st[N];
int ans = INT_MAX;

int deep(int root, int now) {
	int sum = 1;
	nodes[root].deep = now;
	for(int t : nodes[root].child) {
		sum += deep(t, now + 1);
	}
	nodes[root].sum = sum;
	return sum;
}

void select(int root, bool flag) {
	if(nodes[root].select == flag) return;
	nodes[root].select = flag;
	for(int t : nodes[root].child) {
		select(t, flag);
	}
}

void dfs(vector<int> q, int sum) {
	ans = min(ans, sum);
	vector<int> temp;
	for(int t : q) {
		if(nodes[t].select) continue;
		for(int t2 : nodes[t].child) {
			if(!nodes[t2].select) {
				temp.push_back(t2);
			}
		}
	}
	for(int t : temp) {
		select(t, true);
		dfs(temp, sum - nodes[t].sum);
		select(t, false);
	}
}

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i ++) {
		int x, y;
		cin >> x >> y;
		if(x > y) {
			swap(x, y);
		}
		nodes[x].child.push_back(y);
	}
	deep(1, 0);
	dfs({1}, n);
	cout << ans << endl;
	return 0;
}