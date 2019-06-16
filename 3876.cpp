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
const int N=1e5+5;
const int inf=1e9;
#define int ll
int n;
namespace dinic{
	struct edge{
		int next,to,w,c;
	}a[N<<1];
	int head[N],cnt;
	inline void Add(int u,int v,int w,int c){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
		a[cnt].c=c;
	}	
	inline void add(int u,int v,int w,int c){
		Add(u,v,w,c),Add(v,u,0,-c);
	}
	int S,T,ans;
	int inc[N],pre[N];
	int vis[N],d[N],las[N];
	queue<int>q;
	inline void init(){
		memset(head,0,sizeof(head));
		cnt=1,ans=0;
		n=read();
		for (int i=1;i<=n;++i){
			int m=read();
			for (int j=1;j<=m;++j){
				int y=read(),t=read();
				++inc[y],--inc[i];
				add(i,y,inf,t);
				ans+=t;
			}
		}
		for (int i=2;i<=n;++i)
			add(i,n+1,inf,0);
		add(n+1,1,inf,0);
		S=n+2,T=n+3;
		for (int i=1;i<=n+1;++i){
			if (inc[i]>0) add(S,i,inc[i],0);
			if (inc[i]<0) add(i,T,-inc[i],0);
		}
	}
	inline bool spfa(){
		q=queue<int>();
		for (int i=1;i<=T;++i)
			d[i]=inf,vis[i]=pre[i]=0;
		vis[S]=1,d[S]=0,q.push(S);
		while (!q.empty()){
			int x=q.front();
			q.pop();
			vis[x]=0;
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (!a[i].w) continue;
				if (d[y]>d[x]+a[i].c){
					d[y]=d[x]+a[i].c;
					pre[y]=x,las[y]=i;
					if (!vis[y]) vis[y]=1,q.push(y);
				}
			}
		}
		return pre[T];
	}
	inline void solve(){
		init();
		while (spfa()){
			int flow=inf;
			for (int i=T;i!=S;i=pre[i])
				flow=min(flow,a[las[i]].w);
			ans+=flow*d[T];
			for (int i=T;i!=S;i=pre[i]){
				a[las[i]].w-=flow;
				a[las[i]^1].w+=flow;
			}
		}	
		printf("%lld\n",ans);
	}
}
signed main(){
	freopen("3876.in","r",stdin);
	freopen("3876.out","w",stdout);
	dinic::solve();
	return 0;
}
