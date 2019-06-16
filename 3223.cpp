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
namespace splay{
	#define ls ch[x][0]
	#define rs ch[x][1]
	#define getson(x) (x==ch[fa[x]][1])
	int n,m,rt;
	int ch[N][2],sz[N];
	int rev[N],val[N],fa[N];
	inline void Rev(int x){
		if (!x) return;
		rev[x]^=1,swap(ls,rs);
	}
	inline void pushup(int x){
		if (!x) return;
		sz[x]=sz[ls]+sz[rs]+1;
	}
	inline void pushdown(int x){
		if (!x || !rev[x]) return;
		Rev(ls),Rev(rs),rev[x]=0;
	}
	void build(int x,int l,int r){
		int mid=(l+r)>>1;
		val[x]=mid,sz[x]=1;
		if (l==r) return;
		if (l<mid) build(ls=(x<<1),l,mid-1),fa[ls]=x;
		if (r>mid) build(rs=((x<<1)|1),mid+1,r),fa[rs]=x;
		pushup(x);
	}	 
	inline void rotate(int x){
		int y=fa[x],z=fa[y],k=getson(x);
		pushdown(y),pushdown(x);
		ch[y][k]=ch[x][!k];
		if (ch[x][!k]) fa[ch[x][!k]]=y;
		ch[x][!k]=y;
		if (z) ch[z][getson(y)]=x;
		fa[x]=z,fa[y]=x;
		pushup(y),pushup(x);
	}
	inline void splay(int x,int goal){
		while (fa[x]!=goal){
			int y=fa[x];
			pushdown(fa[y]),pushdown(y),pushdown(x);
			if (fa[y]!=goal)
				(getson(x)^getson(y))?rotate(x):rotate(y);
			rotate(x);
		}
		pushup(x);
		if (!goal) rt=x;
	}
	inline int get_kth(int x,int k){
		while (x){
			pushdown(x);
			if (sz[ls]+1==k) return x;
			if (sz[ls]+1>k) x=ls;
			else k-=sz[ls]+1,x=rs;
		}
	}
	inline void update(int l,int r){
		int L=get_kth(rt,l-1),R=get_kth(rt,r+1);
		splay(L,0),splay(R,L);
		Rev(ch[R][0]);
	}
	void dfs(int x){
		pushdown(x);
		if (ls) dfs(ls);
		if (val[x]>=1 && val[x]<=n) Print(val[x],' ');
		if (rs) dfs(rs);
	}
	inline void solve(){
		n=read(),m=read();
		build(rt=1,0,n+1);
		for (int i=1;i<=m;++i){
			int l=read(),r=read();
			update(l+1,r+1);
		}
		dfs(rt);
		io::flush();
		puts("");
	}
}
using namespace splay;
int main(){
	freopen("3223.in","r",stdin);
	freopen("3223.out","w",stdout);
	solve();
	return 0;
}
