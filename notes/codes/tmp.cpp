#include <iostream>
#include <algorithm>
#include <cstdlib>   // 包含 srand 和 rand 函数
#include <chrono>    // 包含高精度时间库
#include <fstream>
using namespace std;
bool connect[3010][3010];
// (2 ≤ N, M ≤ 5000; 2 ≤ T ≤ 10,000; 2 ≤ P ≤ 80; 2 ≤ D ≤ 1000)
int n, m, t, p, d;

void print() {
	auto now = chrono::high_resolution_clock::now();
    auto seed = now.time_since_epoch().count();

    srand(seed);   // 设置随机数种子为当前时间戳
	n = rand() % 5000 + 2;
	m = rand() % 5000 + 2;
	p = rand() % 80 + 2;
	t = rand() % 10000 + 2;
	d = rand() % 1000 + 2;
	ofstream outfile("tmp.txt");
	if (outfile.is_open()) {
		outfile << n << ' ' << m << ' ' << ' ' << t << ' ' << p << ' ' << d << endl;
		//随即输出m条边，每条边的两个端点的编号为0~n-1
		//每行有三个整数，分别表示一条边的两个端点的编号和这条边的权值，同时加入随机种子，保证每次输出的边都不一样

		for (int i = 0; i < m; i++) {
			int u = rand() % n;
			int v = rand() % n;
			int w = rand() % 1010;
			outfile << u << " " << v << " " << w << endl;
		}
		outfile.close();
	} else {
		cout << "Unable to open file";
	}
}

void read() {
	//从tmp.txt中读取数据
	ifstream infile("tmp.txt");
	if(infile.is_open()) {
		infile >> n >> m >> t >> p >> d;
		for(int i = 0; i < m; i ++) {
			int u, v, w;
			infile >> u >> v >> w;
			connect[u][v] = connect[v][u] = true;
		}
		infile.close();
	} else {
		cout << "Unable to open file";
	}
	//计算所有点是否连通
	for(int k = 0; k < n; k ++) {
		for(int i = 0; i < n; i ++) {
			for(int j = 0; j < n; j ++) {
				connect[i][j] = connect[i][j] || (connect[i][k] && connect[k][j]);
			}
		}
	}
}

void print_append() {
	//输出t条询问
	auto now = chrono::high_resolution_clock::now();
    auto seed = now.time_since_epoch().count();

    srand(seed);   // 设置随机数种子为当前时间戳
	//在tmp.txt中追加输出t条询问
	ofstream outfile("tmp.txt", ios::app);
	if (outfile.is_open()) {
		for (int i = 0; i < t; i++) {
			int u = rand() % n;
			int v = rand() % n;
			while(!connect[u][v]) {
				u = rand() % n;
				v = rand() % n;
			}
			outfile << u << " " << v << endl;
		}
		outfile.close();
	} else {
		cout << "Unable to open file";
	}
}

void test() {
	auto now = chrono::high_resolution_clock::now();
    auto seed = now.time_since_epoch().count();

    srand(seed);   // 设置随机数种子为当前时间戳
	for(int i = 0; i < 100; i ++) {
		cout << rand() % 100 << endl;
	}
}

int main() {
	print();
	read();
	print_append();
	// test();
}

