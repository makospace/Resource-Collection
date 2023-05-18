#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
vector<string> v1, v2;
string s1, s2;
int dp[1010][1010];

void take(string s, vector<string>& v){
	for(int i = 0; i < s.size(); ) {
		int j = i + 1;
		while(j < s.size() && islower(s[j])) j ++;
		v.push_back(s.substr(i, j - i));
		i = j;
	}
}

int main() {
	cin >> s1 >> s2;
	take(s1, v1);
	take(s2, v2);
	//dp[i][j]表示v1[0..i - 1]和v2[0..j - 1]的最长公共可不连续子序列
	for(int i = 0; i < v1.size(); i ++) {
		for(int j = 0; j < v2.size(); j ++) {
			if(v1[i] == v2[j]) dp[i + 1][j + 1] = dp[i][j] + 1;
			else dp[i + 1][j + 1] = max(dp[i][j + 1], dp[i + 1][j]);
		}
	}
	cout << dp[v1.size()][v2.size()];
}