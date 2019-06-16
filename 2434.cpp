#include<bits/stdc++.h>
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
using namespace std;
typedef long long ll;
const int N=1e5+5;
int n,m,k,tot,tt,rt;
int fa[N],dfn[N],sz[N];
int fail[N],ch[N][26];
int pos[N],ans[N],ed[N];
char s[N];
queue<int>q;
vector<int>id[N],g[N],p[N];
namespace bit{
	#define lowbit(x) (x&(-x))
	int sss[N];
	inline void add(int x,int k){
		for (int i=x;i<=tot;i+=lowbit(i))
			sss[i]+=k;
	}
	inline int sum(int x){
		int res=0;
		for (int i=x;i;i-=lowbit(i))
			res+=sss[i];
		return res;
	}
	inline int query(int l,int r){
		return sum(r)-sum(l-1);	
	}
}
using namespace bit;
inline void build(){
	q=queue<int>();
	q.push(1),fail[1]=0;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=0;i<26;++i){
			if (ch[x][i]){
				int now=fail[x];
				while (!ch[now][i]) now=fail[now];
				fail[ch[x][i]]=ch[now][i];
				g[ch[now][i]].push_back(ch[x][i]);
				q.push(ch[x][i]);
			}
		}
	}
}
void dfs(int x){
	dfn[x]=++tt,sz[x]=1;
	for (int i=0,ssz=g[x].size();i<ssz;++i)
		dfs(g[x][i]),sz[x]+=sz[g[x][i]];
}
void solve(int x){
	add(dfn[x],1);
	for (int i=0,ssz=p[x].size();i<ssz;++i){
		int y=p[x][i];
		for (int j=0,dsz=id[y].size();j<dsz;++j){
			int now=id[y][j];
			ans[now]=query(dfn[pos[now]],dfn[pos[now]]+sz[pos[now]]-1);
		}
	}
	for (int i=0;i<26;++i)
		if (ch[x][i]) solve(ch[x][i]);
	add(dfn[x],-1);
}
int main(){
	freopen("2434.in","r",stdin);
	freopen("2434.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1),rt=tot=1;
	for (int i=0;i<26;++i) ch[0][i]=1;
	for (int i=1;i<=n;++i){
		if (s[i]=='P'){
			p[rt].push_back(++k);
			ed[k]=rt;
		}else if (s[i]<='z' && s[i]>='a'){
			int x=s[i]-'a';
			if (!ch[rt][x]) ch[rt][x]=++tot,fa[tot]=rt;
			rt=ch[rt][x];
		}else rt=fa[rt];
	}
	build();
	m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		pos[i]=ed[u],id[v].push_back(i);
	}
	dfs(1),solve(1);
	for (int i=1;i<=m;++i)
		printf("%d\n",ans[i]);
	return 0;
}
