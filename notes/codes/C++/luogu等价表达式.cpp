// #include <iostream>
// #include <algorithm>
// #include <unordered_map>
// #include <vector>
// #include <stack>
// #include <cmath>
// using namespace std;
// string s;
// char id = 'A';
// unordered_map<char, int> ops{{'+', 1}, {'-', 1}, {'*', 2}, {'^', 3}};
// stack<int> nums;
// stack<char> op;
// int n;
// int selected[12];

// void eval() {
// 	int b = nums.top(); nums.pop();
// 	int a = nums.top(); nums.pop();
// 	char c = op.top(); op.pop();
// 	if(c == '+') nums.push(a + b);
// 	else if(c == '-') nums.push(a - b);
// 	else if(c == '*') nums.push(a * b);
// 	else if(c == '^') nums.push(pow(a, b));
// }

// int get(int a) {
// 	for(int i = 0; i < s.size(); i ++) {
// 		if(s[i] == '(') op.push('(');
// 		else if(isdigit(s[i])) {
// 			int t = 0, j = i;
// 			while(j < s.size() && isdigit(s[j])) {
// 				t = t * 10 + s[j] - '0';
// 				j ++;
// 			}
// 			nums.push(t);
// 			i = j - 1;
// 		} else if(s[i] == ' ' || s[i] == '\t') {
// 			continue;
// 		} else if(s[i] == ')') {
// 			while(op.top() != '(') {
// 				eval();
// 			}
// 			op.pop();
// 		} else if(s[i] == 'a') {
// 			nums.push(a);
// 		} else {
// 			while(op.size() && op.top() != '(' && ops[op.top()] >= ops[s[i]]) {
// 				eval();
// 			}
// 			op.push(s[i]);
// 		}
// 	}
// 	while(op.size()) {
// 		eval();
// 	}
// 	return nums.top();
// }

// int main() {
// 	getline(cin, s);
// 	cin >> n;
// 	for(int i = 0; i < 10; i ++) {
// 		nums = stack<int>();
// 		op = stack<char>();
// 		int target = get(i);
// 		selected[i] = target;
// 	}
// 	for(int i = 0; i < n; i ++) {
// 		string tmp;
// 		getline(cin >> ws, tmp);
// 		s = tmp;
// 		int flag = true;
// 		for(int j = 0; j < 10; j ++) {
// 			nums = stack<int>();
// 			op = stack<char>();
// 			int t = get(j);
// 			if(t != selected[j]) {
// 				flag = false;
// 				break;
// 			}
// 		}
// 		if(flag) {
// 			cout << id;
// 		}
// 		id ++;
// 	}
// 	return 0;
// }

#include <iostream>
#include <cstring>
#include <cstdio>

#define MX 55
#define oo 10020123
#define MD 100000007

using namespace std;

typedef long long ll;

ll qpw(ll x,ll t){ll ans=1;for(int i=1;i<=t;i++)ans=ans*x%MD;return ans;}

//计算中缀表达式
ll calc(char *str,int l,int r,ll a)
{
    int prio=0,mnpos=MX,mn=+oo,cnt=0,p[MX],num=0;
    memset(p,0x3f,sizeof(p));
    for(int i=r;i>=l;i--)
    {
        if(str[i]==')')prio+=100;
        if(str[i]=='(')prio-=100;
        if(str[i]=='^')p[i]=prio+3,cnt++;
        if(str[i]=='*')p[i]=prio+2,cnt++;
        if(str[i]=='+')p[i]=prio+1,cnt++;
        if(str[i]=='-')p[i]=prio+1,cnt++;
        if(mn>p[i])mn=p[i],mnpos=i;
    }
	//找到最小的
    if(cnt==0)
    {
        for(int i=l;i<=r;i++)if(str[i]=='a')return a;
        for(int i=l;i<=r;i++)if(isdigit(str[i]))num=num*10+str[i]-'0';
        return num;
    }
    else
    {
        if(str[mnpos]=='^')return qpw(calc(str,l,mnpos-1,a),calc(str,mnpos+1,r,a));
        if(str[mnpos]=='*')return (calc(str,l,mnpos-1,a)*calc(str,mnpos+1,r,a))%MD;
        if(str[mnpos]=='+')return (calc(str,l,mnpos-1,a)+calc(str,mnpos+1,r,a))%MD;
        if(str[mnpos]=='-')return (calc(str,l,mnpos-1,a)-calc(str,mnpos+1,r,a))%MD;
    }
    return 0;
}

int main()
{
    int len[27],n,ans[15];
    char str[27][MX];    
    scanf("%[^\r]",str[0]),getchar();
    len[0]=strlen(str[0]);
    scanf("%d",&n),getchar();
    for(int i=1;i<=n;i++)
    {
        scanf("%[^\r]",str[i]),getchar();
        len[i]=strlen(str[i]);
    }
    for(int i=0;i<=10;i++)ans[i]=calc(str[0],0,len[0]-1,i-5);
    for(int i=1;i<=n;i++)
    {
        int f=1;
        for(int j=0;j<=10;j++)
            if(ans[j]!=calc(str[i],0,len[i]-1,j-5))
                {f=0;break;}
        if(f)printf("%c",'A'+i-1);
    }
    return 0;
}