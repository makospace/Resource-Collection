#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int gcd(int a, int b) {
	//辗转相除法求最大公约数
	if (b == 0) return a;
	else return gcd(b, a % b);
}

void get(double x, double y) {
	//先约分，再输出
	int a = x, b = y;
	int d = gcd(y, x);
	cout << a / d << ' ' << b / d << endl;
}

int main() {
	//nb的来了
	//对于无线小数，可以从其与x乘积-其入手（要求x*其的小数部分等于其的小数部分），消去小数部分
	double x, y;
	int p, q;
	cin >> p >> q;
	cin >> x; y = x;
	x = x / pow(10, q - p + 1);
	get(y - int(x), pow(10, q) - pow(10, -1 + p));
	return 0;
}