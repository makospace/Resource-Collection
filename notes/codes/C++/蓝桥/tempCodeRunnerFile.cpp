#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll N;

ll C(int a, int b)//求第i行第j列的值
{
	ll res = 1; 
	for (ll i = a, j = 1; j <= b; i --, j ++)
	{
		res = res * i / j; //不会出现不能整除的情况，因为j从1开始
		if (res > N)//如果中间结果超过N就直接返回
			return res;
	}
	return res;
}

int main()
{
	cin >> N;
	for (int k = 16; k >= 0; k --)//一列一列的找，列越大，平铺后的序号越小
	{
		ll l = 2 * k, r = max(N, l);
		while (l < r) {//对第k列二分查找行
			int mid = l + r >> 1;//二分行
			ll CC = C(mid, k);
			if(CC > N) r = mid - 1;
			else l = mid;
		}
		if (C(l, k) == N)
		{//第l行、第k列的数就是N
			cout << (l + 1) * l / 2 + k + 1 << endl;
			//杨辉三角形的行数符号公差为1的等差数列，故用等差数列求和公式
			//加上第几列再加上1（因为列从0开始）即可得出该数的位置
			break;
		}
	}
	return 0;
}