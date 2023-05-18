#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100010;
struct Node {
	int id;
	vector<int> sons;
} nodes[N];
int n;

int dfs(int u) {
	//求由此根节点变换成左孩子右兄弟的形式时的最大深度
	int maxDepth = 0;
	vector<int> depths;
	for(int i = 0; i < nodes[u].sons.size(); i ++) {
		int v = nodes[u].sons[i];
		int depth = dfs(v);
		depths.push_back(depth);
	}
	sort(depths.begin(), depths.end());
	reverse(depths.begin(), depths.end());
	return depths.size() ? depths[0] + depths.size() : 0;
}

int main() {
	cin >> n;
	for(int i = 2; i <= n; i ++) {
		int p;	cin >> p;
		nodes[p].sons.push_back(i);
	}
	cout << dfs(1);
	return 0;
}