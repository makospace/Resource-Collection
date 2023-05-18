//记录每一句话是谁说的以及这句话的内容
//可以用map存人名对应的下标 

//我们枚举每一个人i，假设i是罪犯
//然后枚举今天是星期几，用day表示 
//然后判断有没有矛盾

//如何判断？
//进行每一次判断的时候，先使所有人的状态不确定，也就是不知道他们会说真话假话
//TF[a]==-1是不确定，TF[a]=1是说真话，TF[a]=0是说假话
//T是说真话的人数，F是说假话的人数 
//设罪犯为 i 
//设flag为这句话是真话还是假话，flag=1是真话，flag=0是假话 
//id是说这句话的人 
//枚举每一句话
//	看一下id以前的状态，如果状态不确定（TF==-1），就TF[id]=flag
//	否则，如果和以前状态一样(TF[id]==flag)，就没有矛盾，
//	TF[id]!=flag就是出现了矛盾(因为一个人始终直说一种话)，判断不出来了，直接return去枚举下一个人是罪犯 
//如果F>n或者T>m-n了，也就是说假话的人数超过了题目中给的人数，矛盾，return
//如果找到了不止一个罪犯，输出"Cannot Determine"，直接exit(0) 

//怎么知道这句话是真话假话？ 
//①如果话里有 "I am guilty."
//	那么看一下id是不是i，不是的话，就是在说假话
//②话里有"I am not guilty"
//	看一下id是不是i，不是的话，就是在说真话，否则就是假话 
//③话里有"xxx is guilty"
//	如果xxx是i的话，就是真话，否则是假话
//④话里有"xxx is not guilty"
//	如果xxx不是i的话，就是真话，否则是假话
//⑤话里有"Today is XXX"
//	如果xxx与day一样，就是真话，否则是假话
 
#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<algorithm>
using namespace std;

string S[10]=
{
	"Today is Sunday.",
	"Today is Monday.",
	"Today is Tuesday.",
	"Today is Wednesday.",
	"Today is Thursday.",
	"Today is Friday.",
	"Today is Saturday.",
};

int m,n,p;
int T,F,ans;
int TF[25];
struct Sen
{
	int id;
	string s;
}sen[105];
map<string,int> ma;

bool judgeTF(int id,bool flag)	//看一下有没有冲突，return 1 表示有冲突 
{
	if(TF[id]==-1)		//状态不确定 
	{
		TF[id]=flag;	//赋状态 
		if(flag)	//说真话的人数++ 
			++T;
		else	//说假话的人数++ 
			++F;
	}
	else
		return TF[id] != flag;	//和之前的一不一样，一样返回0，不一样返回1 
	if(F > n || T > m - n)	//在当前条件下判断失败就返回1
		return 1;
	return 0;
}

void judge(int id,string day)  //假定id是罪犯，当前天为day
{
	memset(TF,-1,sizeof(TF));	//所有人都不知道说的是真话假话 
	T=F=0;		//说真话、假话人数置0 
	string tmp;
	for(int i=1;i<=p;++i)
	{
		int pos=sen[i].s.find("I am guilty.");	//pos为-1则没说这句话 
		if(~pos)
		{
			if(judgeTF(sen[i].id,sen[i].id==id))	//因为我们假设了id是罪犯，所以不是id的人就不是罪犯，就是在说假话
				return;
		}
		pos=sen[i].s.find("I am not guilty");
		if(~pos)
		{
			if(judgeTF(sen[i].id,sen[i].id!=id))
				return;
		}
		pos=sen[i].s.find(" is guilty.");
		if(~pos)
		{
			tmp=sen[i].s;
			tmp.erase(pos,11);
			if(judgeTF(sen[i].id,ma[tmp]==id))
				return;
		}
		pos=sen[i].s.find(" is not guilty.");
		if(~pos)
		{
			tmp=sen[i].s;
			tmp.erase(pos,15);
			if(judgeTF(sen[i].id,ma[tmp]!=id))
				return;
		}
		pos=sen[i].s.find("Today is ");
		if(~pos)
		{
			if(judgeTF(sen[i].id,sen[i].s==day))
				return;
		}
	}
	if(ans&&ans!=id)	//找到了不止一个罪犯 
	{
		puts("Cannot Determine");	//不能确定 
		exit(0);
	}
	ans=id;		//id是罪犯 
}

string s[25],name,a;
int main()
{
	scanf("%d%d%d",&m,&n,&p);
	for(int i=1;i<=m;++i)
	{
		cin>>s[i];
		ma[s[i]]=i;		//存名字标号 
	}
	for(int i=1;i<=p;++i)
	{
		cin>>name;		//输入说话者 
		name.erase(name.length()-1,1);		//把后边的冒号搞掉 
		getline(cin,a);
		a.erase(0,1);	//把前边的空格搞掉 
		if(a[a.length()-1]=='\n'||a[a.length()-1]=='\r')	//把坑爹的换行符搞掉 
			a.erase(a.length()-1,1);
		sen[i].id=ma[name];		//存说话者 
		sen[i].s=a;		//存说话内容 
	}
	for(int i=1;i<=m;++i)	//假设第i个人是罪犯 
		for(int j=0;j<7;++j)	//假设今天是S[j]天 
			judge(i,S[j]);
	if(!ans)	//找不到罪犯 
		puts("Impossible");
	else
		cout<<s[ans];	//罪犯名字 
	return 0;
}