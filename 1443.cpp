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
const int M=105;
const int inf=1e9;
int n,m,tot,flag;
char ss[N],col[N];
int p[M][M],s[N];
namespace dinic{
	struct edge{
		int next,to,w;
	}a[N<<1];
	int head[N],cnt;
	inline void Add(int u,int v,int w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	inline void add(int u,int v,int w){
		if (!u || !v) return;		
		Add(u,v,w),Add(v,u,0);
	}
	int S,T,tim;
	int vis[N],l[N],cur[N];
	queue<int>q;
	inline void init(){
		memset(head,0,sizeof(head));
		cnt=1;
	}
	inline void build(){
		S=tot+1,T=tot+2;
		for (int i=1;i<=n;++i){
			for (int j=1;j<=m;++j){
				if (!p[i][j]) continue;
				if ((i+j)&1){
					add(S,p[i][j],1);
					add(p[i][j],p[i+1][j],1);
					add(p[i][j],p[i][j+1],1);
					add(p[i][j],p[i-1][j],1);
					add(p[i][j],p[i][j-1],1);
				}else add(p[i][j],T,1),col[p[i][j]]=1;;
			}
		}
	}
	inline bool bfs(){
		q=queue<int>();
		++tim,q.push(S);
		l[S]=1,vis[S]=tim;
		while (!q.empty()){
			int x=q.front();
			if (x==T) return 1;
			q.pop();
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (!a[i].w || vis[y]==tim) continue;
				vis[y]=tim,l[y]=l[x]+1;
				q.push(y);
				if (y==T) return 1;
			}
		}
		return 0;
	}
	int dfs(int x,int flow){
		if (x==T || !flow) return flow;
		int res=0;
		for (int &i=cur[x];i;i=a[i].next){
			int y=a[i].to;
			if (!a[i].w || vis[y]!=tim || l[y]!=l[x]+1) continue;
			int now=dfs(y,min(flow,a[i].w));
			if (now){
				res+=now,flow-=now;
				a[i].w-=now,a[i^1].w+=now;
				if (!flow) return res;
			}else l[y]=-1;
		}
		if (flow) l[x]=-1;
		return res;
	}
	inline void solve(){
		while (bfs()){
			for (int i=1;i<=T;++i) cur[i]=head[i];
			dfs(S,inf);
		}
	}
	void chk(int x,int c){
		vis[x]=1;
		if (col[x]==c) s[x]=flag=1;
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (vis[y] || !a[i^c].w) continue;
			chk(y,c);
		}
	}
	inline void work(){
		init(),build(),solve();
		memset(vis,0,sizeof(vis));
		chk(S,0);
		memset(vis,0,sizeof(vis));
		chk(T,1);
	}
}
using namespace dinic;
int main(){
	freopen("1443.in","r",stdin);
	freopen("1443.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i){
		scanf("%s",ss+1);
		for (int j=1;j<=m;++j)
			if (ss[j]=='.') p[i][j]=++tot;
	}
	work();
	if (!flag) printf("LOSE\n");
	else printf("WIN\n");
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (s[p[i][j]]) printf("%d %d\n",i,j);
	return 0;
}
