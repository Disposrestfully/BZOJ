#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=2e5+5;
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
int n,m,a[N],p1,p2;
namespace segment{
	ll sum[N<<2],tag[N<<2];
	#define mid (l+r>>1)
	#define ls (x<<1)
	#define rs (ls|1)
	inline void pushup(int x){
		sum[x]=sum[ls]+sum[rs];
	}
	inline void pushdown(int x,int l,int r){
		if (tag[x]){
			tag[ls]+=tag[x];
			tag[rs]+=tag[x];
			sum[ls]+=tag[x]*(mid-l+1);
			sum[rs]+=tag[x]*(r-mid);
			tag[x]=0;
		}	
	}
	void add(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R){
			tag[x]+=k;
			sum[x]+=1ll*k*(r-l+1);
			return;
		}
		pushdown(x,l,r);
		if (L<=mid) add(ls,l,mid,L,R,k);
		if (R>mid) add(rs,mid+1,r,L,R,k);
		pushup(x);
	}
	ll query(int x,int l,int r,int L,int R){
		if (L<=l && r<=R) return sum[x];
		pushdown(x,l,r);
		ll res=0;
		if (L<=mid) res+=query(ls,l,mid,L,R);
		if (R>mid) res+=query(rs,mid+1,r,L,R);
		return res;
	}
}
using namespace segment;
namespace bit{
	#define lowbit(i) (i&(-i))
	int s[N];
	inline void init(){
		for (int i=1;i<=n;++i)
			s[i]=-n-1;
	}
	inline void chkmax(int x,int k){
		for (int i=x;i<=n;i+=lowbit(i))
			s[i]=max(s[i],k);
	}
	inline int getmax(int x){
		int res=-n-1;
		for (int i=x;i;i-=lowbit(i))
			res=max(res,s[i]);
		return res;
	}
}	
using namespace bit;
struct node{
	int l,r,w;
};
ll ans[N];
vector<node>p[N];
vector<node>q[N];
int pre[N],nxt[N];
int main(){
	freopen("4826.in","r",stdin);
	freopen("4826.out","w",stdout);
	n=read(),m=read();
	p1=read(),p2=read();
	for (int i=1;i<=n;++i) a[i]=n-read()+1;
	for (int i=1;i<=m;++i){
		int l=read(),r=read();
		q[l-1].push_back((node){l,r,-i});
		q[r].push_back((node){l,r,i});
		ans[i]+=1ll*p1*(r-l);
	}
	for (int i=1;i<=n;++i){
		pre[i]=getmax(a[i]-1);
		chkmax(a[i],i);
	}
	init();
	for (int i=n;i;--i){
		nxt[i]=-getmax(a[i]-1);
		chkmax(a[i],-i);
	}
	for (int i=1;i<=n;++i){
		if (pre[i]<0) pre[i]=0;
		if (nxt[i]>n) nxt[i]=n+1;
		//printf("%d %d\n",pre[i],nxt[i]);
	}
	for (int i=1;i<=n;++i){
		if (pre[i]>0) p[nxt[i]].push_back((node){pre[i],pre[i],p1});	
		if (nxt[i]-1>=i+1) p[pre[i]].push_back((node){i+1,nxt[i]-1,p2});
		if (pre[i]+1<=i-1) p[nxt[i]].push_back((node){pre[i]+1,i-1,p2});
	}
	for (int i=1;i<=n;++i){
		for (int j=0,sz=p[i].size();j<sz;++j){
			add(1,1,n,p[i][j].l,p[i][j].r,p[i][j].w);
		//	printf("%d %d %d %d\n",i,p[i][j].l,p[i][j].r,p[i][j].w);	
		}
		//printf("%d %lld\n",i,query(1,1,n,1,n));
		for (int j=0,sz=q[i].size();j<sz;++j)
			if (q[i][j].w<0) ans[-q[i][j].w]-=query(1,1,n,q[i][j].l,q[i][j].r);
			else ans[q[i][j].w]+=query(1,1,n,q[i][j].l,q[i][j].r);
	}
	for (int i=1;i<=m;++i){
		Print(ans[i]);
		if (i==100000 || i==m) io::flush();	
	}
	return 0;
}
