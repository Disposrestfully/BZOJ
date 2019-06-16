#include<bits/stdc++.h>
#define read() Read<int>()
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
using namespace std;
typedef long long ll;
const int N=505;
const int M=2e5+5;
const int inf=1e9;
int n,m;
int d[N];
namespace sub1{
	struct edge{
		int next,to,w;
	}a[M<<1];
	int head[M],cnt;
	inline void Add(int u,int v,int w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	inline void add(int u,int v,int w){
		Add(u,v,w),Add(v,u,0);
	}
	int S,T,tim,tt;
	int l[M],vis[M],cur[M];
	queue<int>q;
	inline void init(){
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		cnt=1,S=n+(m<<1)+1,T=S+1,tt=n;
		add(S,1,inf),add(2,T,inf);
		for (int i=1;i<=m;++i){
			int u=read(),v=read();
			add(S,++tt,1);add(++tt,T,1);
			add(tt-1,u,inf),add(u,tt,inf);
			add(tt-1,v,inf),add(v,tt,inf);
			++d[u],++d[v];
		}
	}
	inline bool bfs(){
		q=queue<int>();
		vis[S]=++tim,l[S]=1;
		q.push(S);
		while (!q.empty()){
			int x=q.front();
			q.pop();
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (vis[y]==tim || !a[i].w) continue;
				l[y]=l[x]+1,q.push(y),vis[y]=tim;
				if (y==T) return 1;
			}
		}	
		return 0;
	}
	int dfs(int x,int flow){
		if (!flow || x==T) return flow;
		int res=0;
		for (int &i=cur[x];i;i=a[i].next){
			int y=a[i].to;
			if (l[y]!=l[x]+1 || vis[y]!=tim || !a[i].w) continue;
			int w=dfs(y,min(flow,a[i].w));
			if (w){
				res+=w,flow-=w;
				a[i].w-=w,a[i^1].w+=w;
				if (!flow) return res;
			}else l[y]=-1;
		}
		return res;
	}
	inline void solve(){
		init();
		int ans=m<<1;
		while (bfs()){
		//	printf("Go\n");
			for (int i=1;i<=T;++i) cur[i]=head[i];
			ans-=dfs(S,inf);
		}
		printf("%d ",ans);
	}
}
namespace sub2{
	bitset<M>dp;
	inline void solve(){
		int ans=inf,tot=d[1]+d[2];
		dp.reset(),dp[d[2]]=1;
		//printf("\n%d %d ",d[1],d[2]);
		for (int i=3;i<=n;++i){
			tot+=d[i];
			dp|=(dp<<d[i]);
		//	printf("%d ",d[i]);
		}
		//printf("\n%d\n",tot);
		for (int i=0;i<=tot;++i){
			if (!dp[i]) continue;
			ans=min(ans,abs((tot>>1)-i));
		}
		printf("%d\n",ans);
	}
}
int main(){
	freopen("4155.in","r",stdin);
	freopen("4155.out","w",stdout);
	int t=read();
	while (t--){
		n=read(),m=read();
		memset(d,0,sizeof(d));
		sub1::solve();
		sub2::solve();
	}
	return 0;
}
