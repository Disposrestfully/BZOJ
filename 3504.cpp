#include<bits/stdc++.h>
inline int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
		if (ch==EOF) return -1;
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
using namespace std;
typedef long long ll;
const int N=5005;
const int inf=1e9;
int n,tot,sum;
int a1,a2,an;
int b1,b2,bn;
int mp[N][N];
char str[N];
namespace dinic{
	struct edge{
		int next,to,w;
	}a[100005];
	int head[N],cnt;
	inline void Add(int u,int v,int w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	inline void add(int u,int v,int w){
		Add(u,v,w),Add(v,u,0);
		//printf("%d %d %d\n",u,v,w);
	}
	int S,T,tim;
	int vis[N],l[N];
	int cur[N];
	queue<int>q;
	inline void init(){
		memset(head,0,sizeof(head));
		cnt=1,tim=0;
		memset(vis,0,sizeof(vis));
	}
	inline bool bfs(){
		vis[S]=++tim;
		q=queue<int>();
		q.push(S),l[S]=1;
		while (!q.empty()){
			int x=q.front();
			q.pop();
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (vis[y]==tim || !a[i].w) continue;
				l[y]=l[x]+1,vis[y]=tim;
				if (y==T) return 1;
				q.push(y);
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
			int w=dfs(y,min(flow,a[i].w));
			if (w){
				res+=w,flow-=w;
				a[i].w-=w,a[i^1].w+=w;
				if (!flow) return res;
			}else l[y]=-1;
		}
		return res; 
	}
	inline int calc(){
		int res=0;
		while (bfs()){
			for (int i=1;i<=tot;++i) cur[i]=head[i];
			res+=dfs(S,inf);
		}
		return res;
	}
}
using namespace dinic;
int main(){
	freopen("3504.in","r",stdin);
	freopen("3504.out","w",stdout);
	while (1){
		n=tot=read();
		if (n==-1) return 0;
		a1=read()+1,a2=read()+1,an=read();
		b1=read()+1,b2=read()+1,bn=read();
		for (int i=1;i<=n;++i){
			scanf("%s",str+1);
			for (int j=1;j<=n;++j){
				if (str[j]=='O') mp[i][j]=2;
				else if (str[j]=='X') mp[i][j]=0;
				else mp[i][j]=inf;
			}
		}
		init();
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				if (mp[i][j]) add(i,j,mp[i][j]);
		S=++tot;T=++tot;
		add(S,a1,(an<<1)),add(a2,T,(an<<1));
		add(S,b1,(bn<<1)),add(b2,T,(bn<<1));
		sum=(an<<1)+(bn<<1);
		if (calc()<sum){
			puts("No");
			continue;
		}
		init(),tot=n;
		for (int i=1;i<=n;++i)
			for (int j=1;j<=n;++j)
				if (mp[i][j]) add(i,j,mp[i][j]);
		S=++tot;T=++tot;
		add(S,a1,(an<<1)),add(a2,T,(an<<1));
		add(S,b2,(bn<<1)),add(b1,T,(bn<<1));
		if (calc()<sum){
			puts("No");
			continue;
		}
		puts("Yes");
	}
	return 0;
}
