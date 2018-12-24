#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<queue>
using namespace std;
const int N=1e5+5;
const int M=1e6+5;
int read(){
	int x=0;
	char ch=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x;
}
int n,m,Mod;
struct edge{
	int next,to;
}a[M<<1];
int head[N],cnt;
void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int dfn[N],low[N],id[N];
int sz[N],q[N],vis[N],top;
int ans=0,mx=0,t,tot;
vector<int>p[M];
void tarjan(int x){
	dfn[x]=low[x]=++t;
	q[++top]=x;
	vis[x]=1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (!dfn[y]){
			tarjan(y);	
			low[x]=min(low[x],low[y]);
		}else if (vis[y]) low[x]=min(low[x],dfn[y]);
	}
	if (low[x]==dfn[x]){
		tot++;
		int now=0;
		while (now!=x){
			now=q[top];
			--top;
			id[now]=tot;
			vis[now]=0;
			sz[tot]++;
		}
	}
}
int size[N],dp[N],d[N],pre[N];
queue<int>h;
void solve(){
	for (int i=1;i<=tot;++i)
		if (!d[i]){
			h.push(i);
			dp[i]=1;
			size[i]=sz[i];	
		}
	while (!h.empty()){
		int x=h.front();
		h.pop();
		mx=max(mx,size[x]);
		for (int i=0;i<p[x].size();++i){
			int y=p[x][i];
			--d[y];
			if (!d[y]) h.push(y);
			if (pre[y]==x) continue;
			if (size[x]+sz[y]==size[y])
				dp[y]=(dp[y]+dp[x])%Mod;
			if (size[x]+sz[y]>size[y]){
				size[y]=size[x]+sz[y];
				dp[y]=dp[x];
			}
			pre[y]=x;
		}
	} 
}
int main(){
	//freopen("4.in","r",stdin);
	//freopen("a.out","w",stdout);
	n=read();m=read();Mod=read();
	for (int i=1;i<=m;++i){
		 int u=read(),v=read();
		 add(u,v);
	}
	for (int i=1;i<=n;++i)
		if (!dfn[i])
			tarjan(i);
	cnt=0;
	for (int i=1;i<=n;++i){
		for (int j=head[i];j;j=a[j].next){
			int y=a[j].to;
			if (id[i]!=id[y]){
				p[id[i]].push_back(id[y]);
				++d[id[y]];
			}
		}
	}
/*	for (int i=1;i<=tot;++i){
		sort(p[i].begin(),p[i].end());
   		p[i].erase(unique(p[i].begin(),p[i].end()),p[i].end());
    }*/
	solve();
    printf("%d\n",mx);
    for (int i=1;i<=tot;++i)
    	if (size[i]==mx) ans=(ans+dp[i])%Mod;
    printf("%d\n",ans);
	return 0;
}
