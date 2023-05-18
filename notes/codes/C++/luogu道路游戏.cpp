#include <cstring>
#include <iostream>
using namespace std;
int n, m, p;
int pay[1001];
int money[1001][1001];
int f[1001];
int main() {
  cin >> n >> m >> p;
  memset(f, -999999, sizeof(f));
  f[0] = 0;
  for (int i = 1; i <= n; i++)
    for (int j = 1; j <= m; j++) cin >> money[i][j];
	//第j时间第i条路上出现的金币
  for (int i = 1; i <= n; i++) cin >> pay[i];
	//每个工厂的机器人生产费用
  for (int i = 1; i <= m; i++)
  //枚举时间
    for (int j = 1; j <= n; j++) {
      //枚举现在这个机器人在哪个工厂
      int ff = j - 1;
      if (!ff) ff = n;
      int ss = money[ff][i];
      for (int k = 1; k <= p; k++) {
        //枚举这个机器人现在走了多远
        if (i - k < 0) break;
        f[i] = max(f[i], f[i - k] + ss - pay[ff]);
        ff--;
        if (!ff) ff = n;
        ss += money[ff][i - k];
      }
    }
  cout << f[m];
  return 0;
}
