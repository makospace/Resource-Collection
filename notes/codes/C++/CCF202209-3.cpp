#include <iostream>
#include <vector>
#include <set>

using namespace std;

typedef long long LL;
//需要去重和排序的，用set就对了
set<LL> sd[1050], su;   //sd[i]存储第i天的风险地区
struct node
{
    LL d, u, r;
}a;

vector<node> v[1050];
LL n, ri, mi, d, u, r, pi;

int main()
{
    cin >> n;
    for (int i = 0; i < n; i ++ ) // i:生成名单这一天
    {
        cin >> ri >> mi;
        
        for (int j = 0; j < ri; j ++ ) // ri个风险地区1
        {
            cin >> pi;
            for (int k = i; k < i + 7; k ++ ) sd[k].insert(pi); // pi地区i ~ i+6天都是风险地区
        }
        
        for (int j = 0; j < mi; j ++ ) // mi个漫游用户
        {
            cin >> d >> u >> r;      // 输入用户的到达天数，用户id，用户到达的地区
            if (d < 0) continue;     // 说了自0天起，所以d<0的不用管
            if (!sd[d].count(r)) continue; // 因为某日是否有风险取决于前面的日子，现在d<=i，已经知道了到i天的风险情况，所以此时无风险，后面也不会有风险
            v[i].push_back({d, u, r}); // 存储第i天的漫游数据
        }
        
        // 对漫游信息进行判断,从第i-6天开始.因为7天前的用户漫游数据有可能到现在还是风险的
        for (int j = max(0, i - 6); j <= i; j ++ )
        {
            for (int k = 0; k < v[j].size(); k ++ )
            {
                d = v[j][k].d;
                u = v[j][k].u;
                r = v[j][k].r;
                
                // 1.该用户的d要在7日内
                // 2.该用户在近7日内到访的地区在到访的那一日处于风险状态
                // 3.上述存在风险的地区自到访日(d)至生成名单当日(i)持续处于风险状态

                bool flag = 1;
                if (d <= i - 7) continue; // 要求1
                for (int l = d; l <= i; l ++ ) // 要一直持续到当前i这一天 要求2&3
                    flag = flag & sd[l].count(r);
                if (flag) su.insert(u);
            }
        }
        
        cout << i << " ";
		for (auto it : su) cout << it << " ";
		cout << endl;
		su.clear();
    }
    
    return 0;
}
