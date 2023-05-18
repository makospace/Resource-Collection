#include <iostream>
#include <cstdio>
#include <math.h>
using namespace std;

int n;
double a[1010];

int main()
{
	scanf("%d", &n);
	for(int i = 0; i < n; i ++) scanf("%lf", &a[i]);
	double ave = 0.0, ave_2 = 0.0;
	for(int i = 0; i < n; i ++) {
		ave += a[i];
	}
	ave /= n;
	for(int i = 0; i < n; i ++) {
		ave_2 += (a[i] - ave) * (a[i] - ave);
	}
	double D = sqrt(ave_2 / n);
	for(int i = 0; i < n; i ++) {
		printf("%.15lf\n", (a[i] - ave) / D);
	}
	return 0;
}