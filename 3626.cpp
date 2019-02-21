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
const int N=5e4+5;
const int Mod=201314;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
namespace seg{
	#define mid (l+r>>1)
	#define ls (x<<1)
	#define rs (ls|1)
	int Add[N<<2],sum[N<<2];
	inline void pushdown(int x,int l,int r){
		if (Add[x]){
			ad(Add[ls],Add[x]);
			ad(Add[rs],Add[x]);
			ad(sum[ls],1ll*Add[x]*(mid-l+1)%Mod);
			ad(sum[rs],1ll*Add[x]*(r-mid)%Mod);
			Add[x]=0;
		}
	}
	inline void pushup(int x){
		sum[x]=(sum[ls]+sum[rs])%Mod;
	}
	void update(int x,int l,int r,int L,int R,int w){
		if (L<=l && r<=R){
			ad(Add[x],w);
			ad(sum[x],1ll*w*(r-l+1)%Mod);
			return;
		}	
		pushdown(x,l,r);
		if (L<=mid) update(ls,l,mid,L,R,w);
		if (R>mid) update(rs,mid+1,r,L,R,w);
		pushup(x);
	}
	int query(int x,int l,int r,int L,int R){
		if (L<=l && r<=R) return sum[x];
		int res=0;
		pushdown(x,l,r);
		if (L<=mid) ad(res,query(ls,l,mid,L,R));
		if (R>mid) ad(res,query(rs,mid+1,r,L,R));
		return res;
	}
}
using namespace seg;
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int n,m,tot;
int dep[N],top[N],dfn[N];
int sz[N],son[N],fa[N];
int p[N],s[N],ans[N];
vector<int>g[N];
void dfs1(int x){
	dep[x]=dep[fa[x]]+1;
	sz[x]=1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		dfs1(y),sz[x]+=sz[y];
		if (sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs2(int x){
	if (x==son[fa[x]]) top[x]=top[fa[x]];
	else top[x]=x;
	dfn[x]=++tot;
	if (son[x]) dfs2(son[x]);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==son[x]) continue;
		dfs2(y);
	}
}
inline void work(int u,int v,int w){
	while (top[u]^top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		update(1,1,n,dfn[top[u]],dfn[u],w);
		u=fa[top[u]];
	}
	if (dfn[u]>dfn[v]) swap(u,v);
	update(1,1,n,dfn[u],dfn[v],w);
}
inline int get_sum(int u,int v){
	int res=0;
	while (top[u]^top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		ad(res,query(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if (dfn[u]>dfn[v]) swap(u,v);
	ad(res,query(1,1,n,dfn[u],dfn[v]));
	return res;
}
int main(){
	freopen("3626.in","r",stdin);
	freopen("3626.out","w",stdout);
	n=read(),m=read();
	for (int i=2;i<=n;++i){	
		fa[i]=read()+1;
		add(fa[i],i);
	}
	dfs1(1),dfs2(1);
	for (int i=1;i<=m;++i){
		int l=read()+1,r=read()+1,x=read()+1;
		p[i]=l==1?1:-1,s[i]=x,ans[i]=0;
		g[l-1].push_back(i);
		g[r].push_back(i);
	}
	for (int i=1;i<=n;++i){
		work(i,1,1);
		for (int j=0,sz=g[i].size();j<sz;++j){
			int x=g[i][j];
			ad(ans[x],1ll*p[x]*get_sum(s[x],1)%Mod);
			p[x]=1;
		}
	}	
	for (int i=1;i<=m;++i)
		Print(ans[i]);
	io::flush();
	return 0;
}
