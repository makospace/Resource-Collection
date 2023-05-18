// 第一类：位数为2—len-1的2k 进制数种数；  它等于从2k
// -1个数中分别不重复地取2个、3个、…….len-1个数的不同组合数之和，即c(2k-1,2)+
// c(2k-1,3)+……+ c(2k -1,len-1)，或∑c(2k -1,i)，(2< =i<=len-1)；

// 第二类：位数已经达到len的2k 进制数种数；
// 这类数的首位可能够是1，2，……2k-i-1，从第2位开始取数时每次都要扣除小于左边相邻数的这些数，因此可供选择的数越来越少，累加起来是∑c(2k
// –(i+1),len)，(1<=i<=2k )。

#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int Maxn = 205;
int K, W, N, M, P;
int Sum[Maxn] = {0}, b[Maxn], c[Maxn];
void Print(int p[]) {
  int i;
  printf("%d", p[p[0]]);
  for (i = p[0] - 1; i > 0; i--) {
   printf("%04d", p[i]);
  }
  printf("\n");
}

void CalC(int n, int m) {
  int i, j, k, x;
  if (m > n) return;
  memset(c, 0, sizeof(c));
  c[0] = c[1] = 1;
  for (k = 1; k <= m; k++) {
    x = n - k + 1;
    for (i = 1; i <= c[0]; i++) c[i] = c[i] * x;
    for (i = 1; i <= c[0]; i++) {
      c[i + 1] += c[i] / 10000;
      c[i] %= 10000;
    }
    if (c[c[0] + 1] > 0) c[0]++;
    x = k;
    j = 0;
    for (i = c[0]; i > 0; i--) {
      j = j * 10000 + c[i];
      c[i] = j / x;
      j %= x;
    }
    while (c[c[0]] == 0) c[0]--;
  }
  memcpy(b, Sum, sizeof(Sum));
  Sum[0] = max(b[0], c[0]);
  for (i = 1; i <= Sum[0]; i++) Sum[i] = b[i] + c[i];
  for (i = 1; i <= Sum[0]; i++) {
    Sum[i + 1] += Sum[i] / 10000;
    Sum[i] %= 10000;
  }
  if (Sum[Sum[0] + 1] > 0) Sum[0]++;
}

int main() {
  int i;
  scanf("%d%d", &K, &W);
  // 2^k进制，化成2进制的位数不超过W位
  N = (1 << K) - 1;
  M = W / K;
  P = W % K;
  P = (1 << P) - 1;
  for (i = 2; i <= M; i++) CalC(N, i);
  for (i = 1; i <= P; i++) CalC(N - i, M);
  Print(Sum);
  return 0;
}