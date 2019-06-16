#include<bits/stdc++.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
#define MP make_pair
#define fi first
#define se second
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int M=2e5+5;
const ll inf=1e18;
typedef pair<ll,int>pa;
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
struct node{
	int u,v,w;
	inline bool operator < (const node &x)const{
		if (u!=x.u) return u<x.u;
		if (v!=x.v) return v<x.v;
		return w<x.w;
	}
}p[M];
struct ID{
	int u,v;
	inline bool operator < (const ID &x)const{
		if (u!=x.u) return u<x.u;
		return v<x.v;
	}
};
vector<int>s[N];map<ID,int>id;
int n,m,tot;
struct edge{
	int nxt,to,w;
}a[M*12];
int head[M*2],cnt;
inline void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].nxt=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
ll d[M*2];
bool flag[M*2];
priority_queue<pa,vector<pa>,greater<pa> >q;
inline void dij(int s){
	for (int i=1;i<=tot;++i){
		flag[i]=0;
		d[i]=inf;
	}
	d[s]=0;
	q.push(MP(0,s));
	while (!q.empty()){
		int u=q.top().se;
		q.pop();
		if(flag[u]) continue;
		flag[u]=1;
		for (int e=head[u];e;e=a[e].nxt){
			int v=a[e].to;
			if (d[v]>1ll*d[u]+a[e].w) {
				d[v]=1ll*d[u]+a[e].w;
				q.push(MP(d[v],v));
			}
		}
	}
}
int main(){
	freopen("4289.in","r",stdin);
	freopen("4289.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		p[i]=(node){u,v,w};
		s[u].push_back(w);
		s[v].push_back(w);
	}			
	s[1].push_back(0);
	add(0,1,0);
	for (int i=1;i<=n;++i){
		sort(s[i].begin(),s[i].end());
   		s[i].erase(unique(s[i].begin(),s[i].end()),s[i].end());
		for (int j=0;j<s[i].size();++j){
			id[(ID){i,s[i][j]}]=++tot;
			if (j){
				add(tot,tot-1,0);
				add(tot-1,tot,s[i][j]-s[i][j-1]);
			}
		}
	}
	for (int i=1;i<=m;++i){
		int u=p[i].u,v=p[i].v,w=p[i].w;
		u=id[(ID){u,w}];v=id[(ID){v,w}];
		add(u,v,w);add(v,u,w);
	}
	dij(0);
	ll ans=inf;
	for (int i=0;i<s[n].size();++i){
		int u=id[(ID){n,s[n][i]}];
		ans=min(ans,d[u]);	
	}
	printf("%lld\n",ans);
	return 0;
}
