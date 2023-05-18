#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
using namespace std;
int n;
unordered_set<int> s;
int nums[110];
bool des = false;

int main() {
	cin >> n;
	s.insert(0);
	for(int i = 0; i < n; i ++) {
		cin >> nums[i];
	}
	for(int i = 0; i < n; i ++) {
		unordered_set<int> tmp;
		for(unordered_set<int>::iterator it = s.begin(); it != s.end(); it ++) {
			tmp.insert(*it + nums[i]);
			tmp.insert(*it - nums[i]);
			tmp.insert(*it);
		}
		s = tmp;
	}
	int ans = 0;
	for(unordered_set<int>::iterator it = s.begin(); it != s.end(); it ++) {
		if(*it > 0) ans ++;
	}
	cout << ans;
	return 0;
}
