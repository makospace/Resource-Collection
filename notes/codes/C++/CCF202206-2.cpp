//图的匹配
#include <iostream>
#include <algorithm>
#include <cstring>
#include <map>
using namespace std;
using PII = pair<int, int>;
map <PII, bool> tree;
int n, L, S;
int s[60][60];

int main() 
{
	cin >> n >> L >> S;
	//n个树的位置
	int x = 0, y = 0;
	for(int i = 0; i < n; i ++) {
		cin >> x >> y;
		tree[{x, y}] = true;
	}
	for(int i = S; i >= 0; i --) {
		for(int j = 0; j <= S; j ++) {
			cin >> s[i][j];
		}
	}
	int ans = 0;
	for(auto it : tree) {
		int sx = it.first.first;
		int sy = it.first.second;
		bool flag = true;
		for(int i = 0; i <= S; i ++) {
			for(int j = 0; j <= S; j ++) {
				if(i + sx > L || j + sy > L) {
					flag = false;
					break;
				}
				if(s[i][j] == 1 && tree.count({i + sx, j + sy}) == 0) {
					flag = false;
					break;
				}
				if(s[i][j] == 0 && tree.count({i + sx, j + sy}) == 1) {
					flag = false;
					break;
				}
			}
			if(!flag) break; 
		}
		if(flag) ++ ans;
	}
	cout << ans;
	return 0;
}