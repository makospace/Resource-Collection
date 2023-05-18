#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N = 100010;
using LL = long long;
struct node {
	int a;
	vector<int> son;
	int id;
}tree[N];
int n;
int a[N] = {0};
LL ans[N] = {0};
vector<int> nums;

vector<int> dfs(int root) {
	if(root == 0) return {};
	nums.clear();
	for(int t : tree[root].son) {
		auto it = dfs(t);
		nums.insert(nums.end(), it.begin(), it.end());
	}
	nums.push_back(tree[root].a);
	sort(nums.begin(), nums.end());
	LL sum = 0;
	for(int i = 1; i <= nums.size(); i ++) {
		LL tmp = 0x3f3f3f3f3f3f;
		if(i > 1) tmp = min(tmp, (LL)tree[nums[i - 2]].a - tree[nums[i - 1]].a);
		if(i + 1 <= n) tmp = min(tmp, (LL)tree[nums[i]].a - tree[nums[i - 1]].a);
		if(tmp != 0x3f3f3f3f3f3f) sum += tmp * tmp;
	}
	ans[root] = sum;
	return nums;
}

int main() {
	cin >> n;
	for(int i = 2; i <= n; i ++) {
		int p;
		cin >> p;
		tree[p].son.push_back(i);
	}	
	for(int i = 1; i <= n; i ++) {
		cin >> tree[i].a;
		a[i] = i;
	}
	auto& it = tree;
	sort(a + 1, a + n + 1, [&it](int x, int y){ 
		return it[x].a < it[y].a; 
	});
	//a中存下标按照a的值从小到大排序

	for(int i = 1; i <= n; i ++) {
		tree[a[i]].id = i;
	}
	dfs(1);
	for(int i = 1; i <= n; i ++) {
		cout << ans[i] << endl;
	}
	return 0;
}
