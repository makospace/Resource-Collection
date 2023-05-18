#include <iostream>
#include <cstring>
#include <algorithm>
#include <stdio.h>
using namespace std;

typedef long long LL;
const int MOD=1000000007;
const int N=5010;
LL dp[N][N];
char str[N];
int len;
LL func()
{
    memset(dp,0,sizeof(dp));
    dp[0][0]=1;
    for(int i=1;i<=len;i++)//一个括号一个括号的判断
    {
        if(str[i]=='(')
        {
            for(int j=1;j<=len;j++)
            {
                dp[i][j]=dp[i-1][j-1];//不用考虑dp[i][0] 因为dp[i-1][-1]是不合法的情况 不存在 为0
            }
        }
        else
        {
            dp[i][0]=(dp[i-1][0]+dp[i-1][1])%MOD;//特判防止越界 这里数据短，用的是优化前的推断
            for(int j=1;j<=len;j++)
            {
                 dp[i][j]=(dp[i-1][j+1] + dp[i][j-1])%MOD;
            }
        }
    }
    for(int i=0;i<=len;i++)
        if(dp[len][i]) return dp[len][i];//我们需要的就是长度为len添加括号的合法情况，而从前往后遍历出现的第一个有可能的情况就是需要括号数最少的情况，因为左括号可以加很多个，我们仅需添加最少的情况
        return -1;
}
int main()
{
    scanf("%s",str+1);//从下标为1开始
    len=strlen(str+1);
    LL l=func();
    reverse(str+1,str+len+1);
    for(int i=1;i<=len;i++)
    {
        if(str[i]=='(') str[i]=')';
        else str[i]='(';
    }
    LL r=func();
    cout<<l*r%MOD;
    return 0;
}
