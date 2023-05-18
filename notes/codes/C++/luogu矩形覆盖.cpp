#include <iostream>
using namespace std;
const int INF = 0x7f7f7f;
const int N = 60;
int min(int a, int b)  // 手写min函数更快
{
  return a < b ? a : b;
}
int n, k, x[N], y[N], ans;

struct rec  // 强大功能的结构体
{
  int ux, uy, dx, dy;  // 为左上角，右下角坐标
  bool use;            // 记录这个矩形中有没有点
  // 求出矩形面积
  int Get() {
    if (!use) return 0;  // 如果还没用过，返回零
    return (dx - ux) * (uy - dy);
  }
  void Add(int x, int y)  // 加入点
  {
    if (!use)  // 还没有用过的话，就把矩形设成这个点
    {
      ux = x, uy = y, dx = x, dy = y;
      use = 1;
      return;
    }
    if (ux > x) ux = x;  // 沿点的方向扩张矩形
    if (dx < x) dx = x;
    if (uy < y) uy = y;
    if (dy > y) dy = y;
  }
  bool in_rec(int x, int y)  // 判断这个点是否在矩形内
  {
    if (x < ux || x > dx || y > uy || y < dy) return 0;
    return 1;
  }
  bool cross(struct rec u)  // 判断另一个矩形是否与这个矩形相交
  {
    // 如果某一个矩形还没用过，那肯定不相交
    if (!use || !u.use) return 0;
    // 只要四个顶点中有一个在对方内部，就肯定相交了
    return u.in_rec(dx, dy) || u.in_rec(dx, uy) || u.in_rec(ux, dy) ||
           u.in_rec(ux, uy);
  }
} g[5];  // 最多4个矩形
bool not_cross() {
  int i, j;
  for (i = 1; i <= k; i++)
    for (j = i + 1; j <= k; j++)  // 枚举每两个矩形
    {
      // 只要有一个矩形与另一个矩形相交，此方案就不合法
      // 我们需要两个都判断因为cross函数只能判断另一个矩形与自己的单向关系
      if (g[i].cross(g[j]) || g[j].cross(g[i]) != 0) return 0;
    }
  return 1;
}
void dfs(int area, int cur)  // area是当前矩形总面积，cur是当前点的编号
{
  if (area >= ans)  // 剪枝
    return;
  if (cur > n)  // 如果n个点全搜完，且没有矩形相交，更新答案并返回
  {
    if (not_cross()) ans = min(area, ans);
    return;
  }
  struct rec t;
  for (int i = 1; i <= k; i++)  // 枚举该把这个点放到哪个矩形里
  {
    t = g[i];                  // 记录
    g[i].Add(x[cur], y[cur]);  // 把这个点加进去
    dfs(area - t.Get() + g[i].Get(),
        cur + 1);  // 新的面积=原面积-原矩形面积+加入这个点之后的该矩形面积
    g[i] = t;      // 回溯
  }
}
int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> x[i] >> y[i];
  }
  ans = INF;
  dfs(0, 1);  // 初始面积为零，从第一个点开始
  cout << ans;
  return 0;
}