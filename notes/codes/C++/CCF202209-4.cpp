#include <bits/stdc++.h>
using namespace std;
using LL = long long;
#define INF 0x3f3f3f3f

map<int, int> mp;       //映射回该作品的真正的ID
struct Cmp
{
	//重载的另一种形式，这次给出了两个参数，默认是前后两个元素，因为这里没给struct里的变量，所以只能用这种方式
    bool operator () (const pair<LL, int> & a,const pair<LL, int> & b) const {
        if (a.first == b.first) return a.second < b.second;
        return a.first > b.first;
    }
};
int f[200010], p[200010];       //p[i]表示作品i真正的id。
int tot;
int finds(int x) { 
	return f[x] == x ? x : finds(f[x]); 
}
void unions(int x, int y) { 
	f[finds(x)] = finds(y); 
}
LL n;
int m, q;
map<int, LL> cnt;                               //纪录每个作品的票数
set <pair<LL, pair<LL, int>>> seg;              //维护现有的段 <右端点,<左端点, 作品id>>
set <pair<LL, int>, Cmp> heap;                  //维护当前各个作品的得票数排名
 
int main() {
    cin >> n >> m >> q;  //n个人（最大1e9），m个作品（最大1e5），q个操作（最大1e5）
    tot = m;
    for (int i = 1; i <= max(2 * q, 2 * m); i ++) {
		f[i] = p[i] = i; 
	}
    for (int i = 1; i <= m; i++) mp[i] = i;
    cnt[0] = n;

    seg.insert(make_pair(n, make_pair(1, 0)));  //表示的是[1, n]这个区间，作品id为0
    for (int _ = 0; _ < q; _++) {   //后面用不到下标，所以搞一个下划线
        int op;
        int x, y, w;
        LL l, r;
        cin >> op;
        if (op == 1) {
            cin >> l >> r >> x;  //标号为l到r的人将投票对象改为x
            int rx = p[x];
			//找到第一个大于等于l的区间
			//找到第一个大于等于r的区间
            auto bg = seg.lower_bound(make_pair(l, make_pair(0, rx)));      //找到插入本次段落的起点bg和终点ed
            auto ed = seg.lower_bound(make_pair(r, make_pair(0, rx)));
            if (bg == seg.end()) {
				//代表这是一个新区间，和其他区间没有交集
                // auto tmp = heap.find(make_pair(cnt[x], x));
                // if (tmp != heap.end()) heap.erase(tmp);
                // cnt[x] += (r - l + 1);
                // heap.insert(make_pair(cnt[x], x));
                // seg.insert(make_pair(r, make_pair(l, x)));
            } else {
                LL b; LL a;
                int c, rc;
                vector<pair<LL, pair<LL, int>>> add;
                for (auto it = bg; it != seg.end(); it++) {                 //删除bg和ed之间的段(因为都被本次插入覆盖了)
                    b = (*it).first; a = (*it).second.first;
                    c = (*it).second.second;
                    //a，b，c分别代表左右端点和作品id
                    rc = finds(c);   //找到c真正所属的作品的id
                    #ifdef DEBUG
                        // cout << a << ' ' << b << ' ' << c << '\n';
                    #endif
                    //更新信息（先删除，再插入)
                    heap.erase(make_pair(cnt[rc], rc));
                    cnt[rc] -= (b - a + 1);
                    if (rc && cnt[rc] > 0) {
                        heap.insert(make_pair(cnt[rc], rc));
                    }
                    if (it == ed) break;
                }
 
                b = (*bg).first; a = (*bg).second.first;
                c = (*bg).second.second;
                rc = finds(c);
                //现在是第一个左端点大于等于l的段a，b，c
                if (a <= l - 1 && l <= b) {     //考虑因为开头没有覆盖完，而新增加的段 
                    heap.erase(make_pair(cnt[rc], rc));
                    cnt[rc] += (l - a);
                    if (rc && cnt[rc] > 0)
                        heap.insert(make_pair(cnt[rc], rc));
                    add.push_back(make_pair(l - 1, make_pair(a, rc)));
                }
                if (ed != seg.end()) {      //考虑结尾没有覆盖完，而新增加的段
                    b = (*ed).first; a = (*ed).second.first;
                    c = (*ed).second.second;
                    rc = finds(c);
                    if (a <= r  && r + 1 <= b) {
                        heap.erase(make_pair(cnt[rc], rc));
                        cnt[rc] += (b - r);
                        if (rc && cnt[rc] > 0)
                            heap.insert(make_pair(cnt[rc], rc));
                        add.push_back(make_pair(b, make_pair(r + 1, rc)));
                    }
                }
                if (ed != seg.end()) ed = next(ed);
                seg.erase(bg, ed);
                for (auto ad: add) seg.insert(ad);
                seg.insert(make_pair(r, make_pair(l, rx)));
                heap.erase(make_pair(cnt[rx], rx));
                cnt[rx] += (r - l + 1);
                heap.insert(make_pair(cnt[rx], rx));
                #ifdef DEBUG
                    cout << "set: " << '\n';
                    for (auto x : seg) {
                        cout << x.first << ' ' << x.second.first << ' ' << x.second.second << '\n';
                    }
                    cout << '\n';
                #endif
            }
        } else if (op == 2) {
            cin >> x >> w;
            heap.erase(make_pair(cnt[p[x]], p[x]));
            heap.erase(make_pair(cnt[p[w]], p[w]));
            cnt[p[w]] += cnt[p[x]];
            if (p[w]) heap.insert(make_pair(cnt[p[w]], p[w]));
            unions(p[x], p[w]);     //将x合并到w中
            p[x] = ++tot;           //给x一个新身份id（原来的已经被合并到w了，再用就会出错）
            mp[tot] = x;
        } else if (op == 3) {
            cin >> x >> y;
            swap(mp[p[x]], mp[p[y]]);
            swap(p[x], p[y]);
        } else if (op == 4) {
            cin >> w;
            w = p[w];
            cout << cnt[w] << '\n';
        } else {
            if (heap.size() == 0) cout << 0 << '\n';
            else {
                int ans = 0; int ans_id = 0;
                for (auto it: heap) {
                    if (it.first > ans) {
                        ans = it.first;
                        ans_id = mp[it.second];
                    }
                    if (it.first == ans && mp[it.second] < ans_id) ans_id = mp[it.second];
                    if (ans > it.first) break;
                }
                cout << ans_id << '\n';
            }
        }
    }
    return 0;
}