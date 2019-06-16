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
const int N=855;
const int M=8505;
const ll inf=(ll)1e18;
int n,m;
int mp[M][3];
set<ll>s;
namespace dinic{
	struct edge{
		int next,to,w;
	}a[M<<1];
	int head[N],cnt;
	inline void Add(int u,int v,int w){
		a[++cnt].to=v;
		a[cnt].next=head[u];
		head[u]=cnt;
		a[cnt].w=w;
	}
	inline void add(int u,int v,int w){
		Add(u,v,w),Add(v,u,w);
		//printf("%d %d %d\n",u,v,w);
	}
	int S,T,tim;
	int vis[N],cur[N],l[N];
	queue<int>q;
	inline void init(int ss,int tt){
		cnt=1,tim=0;
		memset(head,0,sizeof(head));
		memset(vis,0,sizeof(vis));
		S=ss,T=tt;
		for (int i=1;i<=m;++i)
			add(mp[i][0],mp[i][1],mp[i][2]);
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
				if (!a[i].w || vis[y]==tim) continue;
				vis[y]=tim,l[y]=l[x]+1;
				if (y==T) return 1;
				q.push(y);
			}
		}
		return 0;
	}
	ll dfs(int x,ll flow){
		if (x==T || !flow) return flow;
		ll res=0;
		for (int &i=cur[x];i;i=a[i].next){
			int y=a[i].to;
			if (!a[i].w || vis[y]!=tim || l[y]!=l[x]+1) continue;
			ll w=dfs(y,min(flow,(ll)a[i].w));
			if (w){
				res+=w,flow-=w;
				a[i].w-=w,a[i^1].w+=w;
				if (!flow) return res;
			}else l[y]=-1;
		}
		return res;
	}
	void DFS(int x){
		if (vis[x]==tim) return;
		vis[x]=tim;
		for (int i=head[x];i;i=a[i].next)
			if (a[i].w) DFS(a[i].to);
	}
	inline ll calc(){
		ll ans=0;
		while (bfs()){
			for (int i=1;i<=n;++i) cur[i]=head[i];
			ans+=dfs(S,inf);
		}	
		++tim,DFS(S);
		s.insert(ans);
		//printf("%lld\n",ans);
		return ans;
	}
}
using namespace dinic;
void solve(vector<int>p){
	if (p.size()==1) return;
	init(p[0],p.back()),calc();
	vector<int>s1,s2;
	s1=s2=vector<int>();
	for (int i=0,sz=p.size();i<sz;++i)
		if (vis[p[i]]==tim) s1.push_back(p[i]);
		else s2.push_back(p[i]);
	solve(s1),solve(s2);
}
int main(){
	freopen("4519.in","r",stdin);
	freopen("4519.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=m;++i){
		mp[i][0]=read();
		mp[i][1]=read();
		mp[i][2]=read();
	}
	vector<int>st;
	st=vector<int>();
	for (int i=1;i<=n;++i)
		st.push_back(i);
	solve(st);
	printf("%d\n",(int)s.size());
	return 0;
}
