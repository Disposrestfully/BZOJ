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
int gcd(int x,int y){
	if (!y) return x;
	return gcd(y,x%y);
}
inline bool chk(ll x){
	ll y=(ll)sqrt(x);
	return (y*y==x);
}
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
	}
	int n,S,T,ans,tim;
	int p1[N],p2[N];
	int vis[N],l[N],cur[N];
	queue<int>q;
	inline void init(){
		memset(head,0,sizeof(head));
		cnt=1;
		n=read(),S=n+1,T=n+2;
		for (int i=1;i<=n;++i) p1[i]=read();
		for (int i=1;i<=n;++i) ans+=(p2[i]=read());
		for (int i=1;i<=n;++i){
			if (p1[i]&1){
				add(S,i,p2[i]);
				for (int j=1;j<=n;++j)
					if (!(p1[j]&1))
						if (gcd(p1[i],p1[j])==1 && chk(1ll*p1[i]*p1[i]+1ll*p1[j]*p1[j]))
							add(i,j,inf);
			}else add(i,T,p2[i]);	
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
				vis[y]=tim,l[y]=l[x]+1,q.push(y);
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
			if (vis[y]!=tim || l[y]!=l[x]+1 || !a[i].w) continue;
			int w=dfs(y,min(flow,a[i].w));
			if (w){
				res+=w,flow-=w;
				a[i].w-=w,a[i^1].w+=w;
				if (!flow) return res;
			}else l[y]=-1;
		}
		if (flow) l[x]=-1;
		return res;
	}
	inline void solve(){
		init();
		while (bfs()){
			for (int i=1;i<=T;++i)
				cur[i]=head[i];
			ans-=dfs(S,inf);
		}
		printf("%d\n",ans);
	}
}
int main(){
	freopen("3158.in","r",stdin);
	freopen("3158.out","w",stdout);
	dinic::solve();
	return 0;
}
