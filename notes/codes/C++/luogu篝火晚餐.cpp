#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
const int Maxn = 50010;
int Dv1[Maxn], Dv2[Maxn];
// 分别表示与1,2,...,n和n,n-1,...,2,1的差值
int vis[Maxn];
int c[Maxn];  // 目标链
int l1[Maxn], l2[Maxn];
int si = 1, n, ans = 0;
void Build()  // 建目标链
{
  c[1] = 1;
  c[2] = l1[1];
  vis[c[1]] = vis[c[2]] = 1;
  for (int i = 2; i <= n - 1; i++) {
    if (c[i - 1] == l1[c[i]])
      c[i + 1] = l2[c[i]], vis[c[i + 1]] = 1;
    else if (c[i - 1] == l2[c[i]])
      c[i + 1] = l1[c[i]], vis[c[i + 1]] = 1;
    else {
      si = 0;
      printf("-1\n");
      return;
    }
  }
  for (int i = 1; i <= n; i++)
    if (!vis[i]) si = 0, printf("-1\n");
  // 前面没判断c[n]同学的需求是否满足，这里判断一下。
  if ((c[1] == l1[c[n]] && c[n - 1] != l2[c[n]]) ||
      (c[1] != l1[c[n]] && c[n - 1] == l2[c[n]]))
    si = 0, printf("-1\n");
  else if ((c[1] == l2[c[n]] && c[n - 1] != l1[c[n]]) ||
           (c[1] != l2[c[n]] && c[n - 1] == l1[c[n]]))
    si = 0, printf("-1\n");
}
void Simulation()  // 求答案
{
  for (int i = 1; i <= n; i++) {
    Dv1[(c[i] - i + n) % n]++;
    Dv2[(c[n - i + 1] - i + n) % n]++;
  }
  for (int i = 0; i <= n - 1; i++) ans = max(ans, max(Dv1[i], Dv2[i]));
  printf("%d\n", n - ans);
}
void read_ini() {
  cin >> n;
  for (int i = 1; i <= n; i++) {
	cin >> l1[i] >> l2[i];
  }
  Build();
  if (si) Simulation();
}
int main() {
  read_ini();
  return 0;
}