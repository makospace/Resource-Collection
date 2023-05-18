#include <algorithm>
#include <iostream>
using namespace std;

const int N = 5010;
// 最长下降序列
int a[N], n;
int dp[N], cnt[N];

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        dp[i] = 1;
        cnt[i] = 1;
        for (int j = 0; j < i; j++)
        {
            if (a[j] > a[i])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (dp[j] + 1 == dp[i])
                {
                    cnt[i] += cnt[j];
                }
            }
            // 去重
            if (dp[j] == dp[i] && a[j] == a[i]) //这时候dp[i]同样和dp[j]一样，是通过0~j来更新的，所以如果dp[i]和dp[j]一样，并且a[i]和a[j]一样，那么二者当前的串就相同
            {
                cnt[i] = 0;
            }
        }
    }
    int Max = 0;
    for (int i = 0; i < n; i++)
        Max = max(Max, dp[i]);
    int sum = 0;
    for (int i = 0; i < n; i++)
    {
        if (dp[i] == Max)
            sum += cnt[i];
    }
    cout << Max << " " << sum << endl;
    return 0;
}