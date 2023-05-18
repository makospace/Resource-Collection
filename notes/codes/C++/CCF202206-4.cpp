#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_map>
using namespace std;

const int N = 100010;
struct edge {
	int k, b;  //斜率和截距
	int x1, y1, x2, y2;  //两个端点
	int a;
	bool operator < (const edge &e) const {
		return b < e.b;
	}
	bool operator == (const edge &e) const {
		return x1 == e.x1 && y1 == e.y1 && x2 == e.x2 && y2 == e.y2;
	}
}plu[N], minu[N];
int m;
set<edge> plus_set, minus_set;
unordered_map<int, edge> times;
int cnt; // number

int main()
{
	cin >> m;
	while(m --) {
		int op;
		cin >> op;
		if(op == 1) {
			int x1, y1, x2, y2;
			cin >> x1 >> y1 >> x2 >> y2;
			int a; cin >> a;
			int k = (y2 - y1) / (x2 - x1);
			int b = y1 - k * x1;
			if(k == 1) plus_set.insert({k, b, x1, y1, x2, y2, a});
			else minus_set.insert({k, b, x1, y1, x2, y2, a});
			times[++ cnt] = {x1, y1, x2, y2};
		}	
		else if(op == 2) {
			int k; cin >> k;  //删除第k个插入的反射面
			auto it = plus_set.find(times[k]);
			if(it != plus_set.end()) plus_set.erase(it);
			else {
				it = minus_set.find(times[k]);
				minus_set.erase(it);
			}
		}
		else {
			int x, y, d, I, t;
			cin >> x >> y >> d >> I >> t;
			//光源在(x, y)方向为d的直线上，光强为I，输出时间为t的位置和反射光强
			int b1 = y - x, b2 = y + x;
			auto it2 = plus_set.lower_bound({0, 0, 0, b2, 0, 0, 0});
			auto it1 = plus_set.upper_bound({0, 0, 0, b1, 0, 0, 0});
			-- it1;
			
		}
	}
	return 0;
}