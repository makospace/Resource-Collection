#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
double pi = acos(-1);
int Q[8][8];
double M[8][8] = {
	{0, 1, 5, 6, 14, 15, 27, 28},
	{2, 4, 7, 13, 16, 26, 29, 42},
	{3, 8, 12, 17, 25, 30, 41, 43},
	{9, 11, 18, 24, 31, 40, 44, 53},
	{10, 19, 23, 32, 39, 45, 52, 54},
	{20, 22, 33, 38, 46, 51, 55, 60},
	{21, 34, 37, 47, 50, 56, 59, 61},
	{35, 36, 48, 49, 57, 58, 62, 63},
};
int n, T;
int Qs[64];

int main() {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			cin >> Q[i][j];
		}
	}
	cin >> n >> T;
	for(int i = 0; i < n; i++) {
		cin >> Qs[i];
	}
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 8; j++) {
			if(M[i][j] < n) M[i][j] = Qs[(int)M[i][j]];
			else M[i][j] = 0;
		}
	}
	if(T == 0) {
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				cout << M[i][j] << ' ';
			}
			cout << endl;
		}
	} else if(T == 1) {
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				M[i][j] *= Q[i][j];
				cout << M[i][j] << ' ';
			}
			cout << endl;
		}
	} else if(T == 2) {
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				M[i][j] *= Q[i][j];
			}
		}
		
		for(int i = 0; i < 8; i++) {
			for(int j = 0; j < 8; j++) {
				double ans = 0;
				for(int u = 0; u < 8; u ++) {
					for(int v = 0; v < 8; v ++) {
						double tmp = 1;
						if(u == 0) tmp *= sqrt(1.0 / 2);
						if(v == 0) tmp *= sqrt(1.0 / 2);
						tmp *= cos(pi / 8.0 * (i + 1.0 / 2) * u);
						tmp *= cos(pi / 8.0 * (j + 1.0 / 2) * v);
						tmp *= M[u][v];
						ans += tmp;
					}
				}
				ans /= 4.0;
				ans += 128;
				if(ans > 255) ans = 255;
				if(ans < 0) ans = 0;
				cout << round(ans) << ' ';
			}
			cout << endl;
		}
	}
	return 0;
}