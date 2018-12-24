#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<string>
using namespace std;
typedef long long ll;
const int N=55;
int n;
queue<vector<int> >q;
vector<int>u,v;
map<vector<int>,int>mp;
string s[N];
void solve(){
	while (!q.empty()){
		u=q.front();
		q.pop();
		int x=mp[u],cnt=0;
		for (char ch='0';ch<='1';++ch){
			cnt=0;
			v.clear();
			for (int i=0;i<u.size();++i){
				int pos=u[i]>>6,t=u[i]&63;
				if (s[pos][t]^ch) continue;
				if (++t==s[pos].size()){
					++cnt;
					for (int j=1;j<=n;++j) v.push_back(j<<6);
				}else v.push_back(pos<<6|t);
			}
			if (cnt>=3){
				printf("%d\n",x+1);
				exit(0);
			}
			sort(v.begin(),v.end());
			int &th=mp[v];
			if (v.size() && !th) th=x+1,q.push(v);
		}
	}
	puts("-1");
}
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i){
		cin>>s[i];
		if (s[i]==""){
			puts("0");
			return 0;
		}
		u.push_back(i<<6);
	}
	q.push(u);
	mp[u]=0;
	solve();
	return 0;
}
