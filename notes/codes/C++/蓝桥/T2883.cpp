// This is a dynamic programming solution to the 3D staircase problem
// We use a 3D array to store the number of ways to reach each step
// The base cases are when there are 0 or 1 steps, in which case there is only 1 way to reach the top
// For all other steps, we can reach the current step from the previous three steps
// So we add up the number of ways to reach the previous three steps to get the total number of ways to reach the current step
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
int n, m, w;
struct point {
    int x, y, z;
    point(int x, int y, int z) : x(x), y(y), z(z) {}
    bool operator < (const point &p) const {
        if(x != p.x) return x < p.x;
        if(y != p.y) return y < p.y;
        return z < p.z;
    }
    bool operator == (const point &p) const {
        return x == p.x && y == p.y && z == p.z;
    }
};

map<point, int> dp;
vector<point> trap;
const int mod = 1000000007;
int primes[1010];
bool st[1010];
int cnt;

void get_primes(int n) {
    // get all primes less than 1000
    for (int i = 2; i <= n; i++) {
        if (!st[i]) {
            primes[cnt++] = i;
        }
        for (int j = 0; primes[j] <= n / i; j++) {
            st[primes[j] * i] = true;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
}

bool check(point v) {
    if(trap[0] == v || trap[1] == v)
        return false;
    else return true;
}

int main() {
    cin >> n >> m >> w; // input the number of steps, the number of ways to reach the first step, and the number of ways to reach the second step
    for(int i = 0; i < 2; i ++) {
// change make_tuple to point constructor
        int x, y, z;
        cin >> x >> y >> z;
        trap.push_back(point(x, y, z));
    }
    dp[point(1, 1, 1)] = 1;
	get_primes(max(n, max(m, w)));
    // fill in the rest of the array using dynamic programming
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= w; k++) {
                if(dp[point(i, j, k)] == 0) continue;
                //可以向上东，南，上走质数格
				// cout << i << ' ' << j << ' ' << k  << ' ' << dp[point(i, j, k)] << endl;
                for(int p = 0; p < cnt; p ++) {
                    if(i + primes[p] <= n && check(point(i + primes[p], j, k))) {
                        dp[point(i + primes[p], j, k)] = (dp[point(i + primes[p], j, k)] % mod + dp[point(i, j, k)] % mod) % mod;
						// cout << i + primes[p] << ' ' << j << ' ' << k  << ' ' << dp[point(i + primes[p], j, k)] << endl;
					}
                    if(j + primes[p] <= m && check(point(i, j + primes[p], k))) {
                        dp[point(i, j + primes[p], k)] = (dp[point(i, j + primes[p], k)] % mod + dp[point(i, j, k)] % mod) % mod;
						// cout << i << ' ' << j + primes[p] << ' ' << k  << ' ' << dp[point(i, j + primes[p], k)] << endl;
					}
                    if(k + primes[p] <= w && check(point(i, j, k + primes[p]))) {
                        dp[point(i, j, k + primes[p])] = (dp[point(i, j, k + primes[p])] % mod + dp[point(i, j, k)] % mod) % mod;
						// cout << i << ' ' << j << ' ' << k + primes[p]  << ' ' << dp[point(i, j, k + primes[p])] << endl;
					}
                }
            }
        }
    }

    cout << dp[point(n, m, w)]; // output the number of ways to reach the top
    return 0;
}
