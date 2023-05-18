#include <iostream>
#include <bitset>
#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;
using bits = bitset<2500>;
int n, m;
unordered_map<string, bits> map;
int ids;
unordered_map<int, int> id_ids;
unordered_map<int, int> ids_id;
unordered_map<int, bits> totals; //每个属性有哪些id是有值的

bits dfs(string s) {
	bits ans;
	if(isdigit(s[0])) {
		int id = 0;
		int num1 = 0, num2 = 0;
		while(isdigit(s[id])) {
			num1 = num1 * 10 + s[id] - '0';
			id ++;
		}
		char c = s[id ++];
		while(isdigit(s[id])) {
			num2 = num2 * 10 + s[id] - '0';
			id ++;
		}
		if(c == ':') ans = map[to_string(num1) + ":" + to_string(num2)];
		else ans = totals[num1] ^ map[to_string(num1) + ":" + to_string(num2)];
		//如果total是1，map是0，那么ans就是1，其余为0
	} else if(s[0] == '|' || s[0] == '&') {
		bits ans1, ans2;
		int cnt = 1, id = 2;
		while(cnt != 0) {
			if(s[id] == '(') cnt ++;
			if(s[id] == ')') cnt --;
			id ++;
		}
		ans1 = dfs(s.substr(2, id - 3));
		ans2 = dfs(s.substr(id + 1, s.size() - id - 2));
		if(s[0] == '|') ans = ans1 | ans2;
		else ans = ans1 & ans2;
	}
	return ans;
}
int main() {
	cin >> n;
	for(int i = 0; i < n; i ++) {
		int id, cnt;
		cin >> id >> cnt;
		while(cnt --) {
			int a, b;
			cin >> a >> b;
			if(id_ids.count(id) == 0) {
				id_ids[id] = ids ++;
				ids_id[ids - 1] = id;
			}
			//id取0~2499
			totals[a].set(id_ids[id]);
			map[to_string(a) + ":" + to_string(b)].set(id_ids[id]);
		}
	}
	cin >> m;
	while(m --) {
		vector<int> res;
		string s;
		cin >> s;
		bits ans = dfs(s);
		for(int i = 0; i < ans.size(); i++) {
			if(ans[i]) {
				res.push_back(ids_id[i]);
			}
		}
		sort(res.begin(), res.end());
		for(int t : res) cout << t << ' ';
		cout << endl;
	}
	return 0;
}
