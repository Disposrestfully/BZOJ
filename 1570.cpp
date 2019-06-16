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
const int N=1e6+5;
const int inf=1e9;
int n,m,tot,tt,num;
int las[N];
int s[N],t[N],w[N];
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
		Add(u,v,w),Add(v,u,0);
		//printf("%d %d %d\n",u,v,w);
	}
	int S,T,tim;
	int vis[N],l[N];
	int cur[N];
	queue<int>q;
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
		//printf("%d\n",res);
		return res;
	}
}
using namespace dinic;
inline void input(){
	memset(head,0,sizeof(head)),cnt=S=1;
	tot=n=read(),m=read(),num=read();
	for (int i=1;i<=m;++i)
		s[i]=read(),t[i]=read(),w[i]=read();
	for (int i=1;i<=m;++i) las[i]=i;
}
inline void solve(){
	for (int ans=1;;++ans){
		for (int i=1;i<=m;++i)
			add(las[s[i]],tot+t[i],w[i]);
		for (int i=1;i<=n;++i)
			add(las[i],tot+i,inf);
		for (int i=1;i<=n;++i)
			las[i]=++tot;
		T=tot;
		tt+=calc();
		if (tt>=num){
			printf("%d\n",ans);
			exit(0);
		}
	}
}
int main(){
	freopen("1570.in","r",stdin);
	freopen("1570.out","w",stdout);
	input(),solve();
	return 0;
}
