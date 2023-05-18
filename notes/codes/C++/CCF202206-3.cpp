// #include <iostream>
// #include <algorithm>
// #include <vector>
// #include <unordered_map>
// using namespace std;

// int n, m, q;
// //角色数量，角色关联数量，询问数量
// struct Role {
// 	string name;
// 	int nv; //操作数数量
// 	vector<string> op;  //nv个操作数
// 	int no; //资源种类数量
// 	vector<string> re_type; //no个资源种类
// 	int nn; //资源名称数量
// 	vector<string> re_name; //nn个资源名称
// };

// unordered_map<string, int> connected_role;  //user -> index, index为角色在Roles中的下标
// unordered_map<string, int> group_map;       //group_name -> index
// vector<vector<int>> group;			        //由group_map得到对应的index，再由index得到对应的group
// vector<Role> Roles;                         //角色
// unordered_map<string, int> role_map;        //Role_name -> index

// int main() 
// {
// 	cin >> n >> m >> q;
// 	Roles.resize(n);
// 	for(int i = 0; i < n; i ++) {
// 		cin >> Roles[i].name >> Roles[i].nv;
// 		Roles[i].op.resize(Roles[i].nv);
// 		for(int j = 0; j < Roles[i].nv; j ++) {
// 			cin >> Roles[i].op[j];
// 		}
// 		cin >> Roles[i].no;
// 		Roles[i].re_type.resize(Roles[i].no);
// 		for(int j = 0; j < Roles[i].no; j ++) {
// 			cin >> Roles[i].re_type[j];
// 		}
// 		cin >> Roles[i].nn;
// 		Roles[i].re_name.resize(Roles[i].nn);
// 		for(int j = 0; j < Roles[i].nn; j ++) {
// 			cin >> Roles[i].re_name[j];
// 		}
// 		role_map[Roles[i].name] = i;
// 	}
// 	for(int i = 0; i < m; i ++) {
// 		string Role_name;
// 		cin >> Role_name;
// 		int ns; cin >> ns;
// 		for(int j = 0; j < ns; j ++) {
// 			string s; cin >> s;
// 			string user_name; cin >> user_name;
// 			if(s == "u") {
// 				connected_role[user_name] = role_map[Role_name]; 
// 				//connected_role[user_name] = i;  //i为角色在Roles中的下标
// 			}
// 			else { 
// 				if(group_map.count(user_name) == 0) {
// 					group_map[user_name] = group.size();
// 					group.push_back(vector<int>(1, role_map[Role_name]));
// 					//group_map存的是组名对应的group的下标，group[i]存的是组i中的角色的下标
// 				}
// 				else {
// 					group[group_map[user_name]].push_back(role_map[Role_name]);
// 				}
// 			}
// 		}
// 	}

// 	for(int i = 0; i < q; i ++) {
// 		string user_name;
// 		cin >> user_name;  //用户名称
		
// 		int ng; cin >> ng; //用户所属组数量
// 		vector<int> user_group; //所属的组的下标
// 		for(int j = 0; j < ng; j ++) {
// 			string s; cin >> s;
// 			user_group.push_back(group_map[s]);
// 		}
// 		string op_name, re_type, re_name;
// 		cin >> op_name >> re_type >> re_name;
// 		bool flag = false;
// 		if(connected_role.count(user_name) != 0) {
// 			Role& r = Roles[connected_role[user_name]];
// 			if((find(r.op.begin(), r.op.end(), op_name) != r.op.end() || find(r.op.begin(), r.op.end(), "*") != r.op.end()) && 
// 			   (find(r.re_type.begin(), r.re_type.end(), re_type) != r.re_type.end() || find(r.re_type.begin(), r.re_type.end(), "*") != r.re_type.end()) && 
// 				(r.re_name.empty() || find(r.re_name.begin(), r.re_name.end(), re_name) != r.re_name.end())) {
// 				flag = true;
// 			}
// 		}
		
// 		if(!flag) {
// 			for(int j = 0; j < user_group.size(); j ++) {
// 				for(int k = 0; k < group[user_group[j]].size(); k ++) {
// 					Role& r = Roles[group[user_group[j]][k]];
// 					if((find(r.op.begin(), r.op.end(), op_name) != r.op.end() || find(r.op.begin(), r.op.end(), "*") != r.op.end()) && 
// 			   		   (find(r.re_type.begin(), r.re_type.end(), re_type) != r.re_type.end() || find(r.re_type.begin(), r.re_type.end(), "*") != r.re_type.end()) && 
// 					   (r.re_name.empty() || find(r.re_name.begin(), r.re_name.end(), re_name) != r.re_name.end())) {
// 						flag = true;
// 						break;
// 					}
// 				}
// 				if(flag) break;
// 			}
// 		}
// 		if(flag) cout << 1 << endl;
// 		else cout << 0 << endl;
// 	}
// }

#include <bits/stdc++.h>
using namespace std;
struct Character_Class{//角色的能力 
	string name;
	map<string,int> opt;//操作清单
	map<string,int> zz;//资源种类清单
	map<string,int> zm;//资源名称清单
}Character[600];
map<string,int> name_CID;
map<string,vector<int> > Uname_CID;
int n,m,q;
int nv,no,nn,ns,ng;
string s;
string uname;
string ugroup[500];
string wopt,wzz,wzm;
bool check(int cid,string o,string z,string m){
	if((Character[cid].opt.count(o)&&Character[cid].opt[o]==1)||
	(Character[cid].opt.count("*")&&Character[cid].opt["*"]==1)){
		if((Character[cid].zz.count(z)&&Character[cid].zz[z]==1)||
		(Character[cid].zz.count("*")&&Character[cid].zz["*"]==1)){
			if((Character[cid].zm.count(m)&&Character[cid].zm[m]==1)||
			(Character[cid].zm.size()==0)){
				return 1;
			}
		}
	}
	return 0;
}
signed main()
{
	cin>>n>>m>>q;
	for(int i=1;i<=n;i++){
		cin>>Character[i].name;
		name_CID[Character[i].name]=i;
		cin>>nv;
		for(int j=1;j<=nv;j++){
			cin>>s;
			Character[i].opt[s]=1;
		}
		cin>>no;
		for(int j=1;j<=no;j++){
			cin>>s;
			Character[i].zz[s]=1; 
		} 
		cin>>nn;
		for(int j=1;j<=nn;j++){
			cin>>s;
			Character[i].zm[s]=1;
		}
	}
	for(int i=1;i<=m;i++){
		cin>>s;
		int CID=name_CID[s];
		cin>>ns;
		for(int j=1;j<=ns;j++){
			cin>>s;
			cin>>s;
			Uname_CID[s].push_back(CID);
		}
	}
	for(int i=1;i<=q;i++){
		cin>>uname;
		cin>>ng;
		for(int j=1;j<=ng;j++){
			cin>>ugroup[j];
		}
		cin>>wopt>>wzz>>wzm;
		int flag=0;
		for(int j=0;j<Uname_CID[uname].size();j++){
			int id=Uname_CID[uname][j];
			if(check(id,wopt,wzz,wzm)){
				flag=1;
				break;
			}
		}
		if(!flag){
			for(int j=1;j<=ng;j++){
				if(flag) break;
				for(int k=0;k<Uname_CID[ugroup[j]].size();k++){
					int id=Uname_CID[ugroup[j]][k];
					if(check(id,wopt,wzz,wzm)){
						flag=1;
						break;
					}
				}	
			} 
		}
		cout<<flag<<endl;
	}
	
}

