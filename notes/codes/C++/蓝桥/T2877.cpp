#include <bits/stdc++.h>
using namespace std;
double dp[505][505][2];
double ld[505],rd[505];
double d,w;
int L,R;
double dis(double x1,double x2,double w)
{
  return sqrt((x1-x2)*(x1-x2)+w*w);
}
int main()
{
  memset(dp,127,sizeof(dp));
  cin>>L>>R>>d>>w;
  for(int i = 1;i<=L;++i) cin>>ld[i];
  for(int i = 1;i<=R;++i) cin>>rd[i];
  dp[1][0][0] = dis(ld[1],0,w/2);
  dp[0][1][1] = dis(rd[1],0,w/2);
  for(int i = 0;i<=L;++i)
  	 for(int j = 0;j<=R;++j)
     {
    		if(i) dp[i][j][0] = min(dp[i][j][0],min(dp[i][j][0],min(dp[i-1][j][0]+ld[i]-ld[i-1],dp[i-1][j][1]+dis(ld[i],rd[j],w))));
    	  	if(j) dp[i][j][1] = min(dp[i][j][1],min(dp[i][j][1],min(dp[i][j-1][1]+rd[j]-rd[j-1],dp[i][j-1][0]+dis(rd[j],ld[i],w))));
 	 }
  double ans = min(dp[L][R][0]+dis(ld[L],d,w/2),dp[L][R][1]+dis(rd[R],d,w/2));
  printf("%.2lf",ans);
  return 0;
}