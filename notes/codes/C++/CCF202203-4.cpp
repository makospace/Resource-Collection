#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;
const int N = 100010;
struct node {
	int id;
	int w;
	bool operator < (const node & t) const {
		return w > t.w || w == t.w && id < t.id;
	}  
};
struct Line {
	struct line {
		int l, r, w;
	};
	vector<line> lines; 
	long long add(int up, int R, int L) {
		//在L， R上增加权值up
		int ans = 0;
		vector<line> back;
		lines.push_back({L, R, up});
		for(int i = 0; i < lines.size(); i ++) {
			if(lines[i].r >= L) {
				ans += lines[i].w;
				back.push_back(lines[i]);
			}
		}
		lines = back;
		return ans;
	};
};
vector<set<node>> g(N, set<node>{});
//g[i]表示i的邻接点的集合，集合中存储的是邻接点的编号和边的权值，set按照边的权值从大到小排序
unordered_map<int, unordered_map<int, Line>> w; //两点之间的权值
int n, m;

int main() {
	cin >> n >> m;
	for(int i = 0; i < m; i ++) {
		int k;	cin >> k;
		int u, v, x, y;
		cin >> u >> v >> x >> y;
		long long now = w[u][v].add(x, i + y - 1, i);
		g[u].insert({v, now});
		g[v].insert({u, now});
		int l;	cin >> l;
		for(int i = 0; i < l; i ++) {
			int q;	cin >> q;
			cout << g[q].begin()->id << endl;
		}
		int p, q; cin >> p >> q;
		if(p) {
			cout << 
		}
	}
}