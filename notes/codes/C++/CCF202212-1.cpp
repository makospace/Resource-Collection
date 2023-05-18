#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

double price[60] = {0};
double phi;
int n;

int main() {
	cin >> n >> phi;
	for(int i = 0; i <= n; i ++) cin >> price[i];
	for(int i = 1; i <= n; i ++) {
		price[0] += price[i] * pow(1 + phi, -i); 
	}
	cout << price[0];
	return 0;
}