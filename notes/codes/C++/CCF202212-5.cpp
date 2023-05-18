//先跑一遍dijkstra，求出到1到所有点的最短距离
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int N = 100010;
struct node {
	int val;
	int pre1, pre2;
	int to1, to2;
	int a, b;
}nodes[2 * N];
int n, m;

int main() {
	cin >> n >> m;
	for(int i = 1; i <= m; i ++) {
		//m个卫星
		cin >> nodes[i + n].pre1 >> nodes[i + n].pre2 >> nodes[i + n].to1 >> nodes[i + n].to2;
		cin >> nodes[i + n].a >> nodes[i + n].b;
	}
	
}