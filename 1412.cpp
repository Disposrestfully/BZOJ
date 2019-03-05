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
const int N=2e5+5;
const int inf=1e9;
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
	int n,m,tim,S,T;
	int cur[N],l[N],vis[N];
	queue<int>q;
	inline void init(){
		cnt=1;
		memset(head,0,sizeof(head));
	}
	inline bool bfs(){
		q=queue<int>();
		vis[S]=++tim,l[S]=1;
		q.push(S);
		while (!q.empty()){
			int x=q.front();
			q.pop();
			if (x==T) return 1;
			for (int i=head[x];i;i=a[i].next){
				int y=a[i].to;
				if (vis[y]==tim || !a[i].w) continue;
				vis[y]=tim,l[y]=l[x]+1,q.push(y);
			}
		}
		return 0;
	}
	int dfs(int x,int flow){
		if (!flow || x==T) return flow;
		int res=0;
		for (int &i=cur[x];i;i=a[i].next){
			int y=a[i].to;
			if (!a[i].w || vis[y]!=tim || l[y]!=l[x]+1) continue;
			int w=dfs(y,min(flow,a[i].w));
			if (w){
				flow-=w,res+=w;
				a[i].w-=w,a[i^1].w+=w;
				if (!flow) return res;
			}else l[y]=-1;
		}
		return res;
	}
	inline int solve(){
		int res=0;
		while (bfs()){
			for (int i=1;i<=n;++i) cur[i]=head[i];
			res+=dfs(S,inf);
		}
		return res;
	}
}
using namespace dinic;
int nn,mm,ans;
int id[105][105];
inline void link(int x,int y){
	if (x!=1) add(id[x][y],id[x-1][y],1);
	if (x!=nn) add(id[x][y],id[x+1][y],1);
	if (y!=1) add(id[x][y],id[x][y-1],1);
	if (y!=mm) add(id[x][y],id[x][y+1],1);
}
int main(){
	freopen("1412.in","r",stdin);
	freopen("1412.out","w",stdout);
	nn=read(),mm=read();
	init();
	for (int i=1;i<=nn;++i)
		for (int j=1;j<=mm;++j)
			id[i][j]=++n;
	S=++n;T=++n;
	for (int i=1;i<=nn;++i)
		for (int j=1;j<=mm;++j){
			link(i,j);
			int opt=read();
			if (opt==1) add(S,id[i][j],inf);
			if (opt==2)	add(id[i][j],T,inf);
		}
	printf("%d\n",solve());
	return 0;
}
