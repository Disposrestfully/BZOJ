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
#define int ll
const int N=1e6+5;
int n,m;
int las[N],pre[N];
int a[N],w[N];
ll ans;
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid (l+r>>1)
	ll add[N<<2],mx[N<<2];
	inline void pushup(int x){
		mx[x]=max(mx[ls],mx[rs]);
	}
	inline void Add(int x,int w){
		add[x]+=w,mx[x]+=w;
	}
	inline void pushdown(int x){
		if (!add[x]) return;
		Add(ls,add[x]);
		Add(rs,add[x]);
		add[x]=0;
	}
	void update(int x,int l,int r,int L,int R,int w){
		if (L<=l && r<=R){
			Add(x,w);
			return;
		}
		pushdown(x);
		if (L<=mid) update(ls,l,mid,L,R,w);
		if (R>mid) update(rs,mid+1,r,L,R,w);
		pushup(x);
	}
	ll query(int x,int l,int r,int L,int R){
		if (L<=l && r<=R) return mx[x];
		pushdown(x);
		ll res=-(ll)1e18;
		if (L<=mid) res=max(res,query(ls,l,mid,L,R));
		if (R>mid) res=max(res,query(rs,mid+1,r,L,R));
		return res;
	}
}
using namespace seg;
signed main(){
	freopen("3747.in","r",stdin);
	freopen("3747.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i){
		a[i]=read();
		pre[i]=las[a[i]];
		las[a[i]]=i;
	}
	for (int i=1;i<=m;++i) w[i]=read();
	for (int i=1;i<=n;++i){
		update(1,1,n,1,i,w[a[i]]);
		if (pre[i]) update(1,1,n,1,pre[i],-2*w[a[i]]);
		if (pre[pre[i]]) update(1,1,n,1,pre[pre[i]],w[a[i]]);
		ans=max(ans,query(1,1,n,1,i));
	}
	printf("%lld\n",ans);
	return 0;
}
