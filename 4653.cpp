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
int n,m,tot,mx,ans=-1;
int val[N];
struct node{
	int l,r,len;
	inline bool operator < (const node &u)const{
		return len<u.len;	
	}
}a[N];
inline void chkmin(int &x,int y){
	if (x<0) x=y;
	else x=min(x,y);
}
namespace seg{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	int tag[N<<2],s[N<<2];
	void clear(int x,int l,int r){
		tag[x]=s[x]=0;
		if (l==r) return;
		clear(ls,l,mid),clear(rs,mid+1,r);
	}
	inline void Add(int x,int w){
		tag[x]+=w,s[x]+=w;	
	}
	inline void pushdown(int x){
		if (!tag[x]) return;
		Add(ls,tag[x]),Add(rs,tag[x]);
		tag[x]=0;
	}
	inline void pushup(int x){
		s[x]=max(s[ls],s[rs]);
	}
	void update(int x,int l,int r,int L,int R,int k){
		if (L<=l && r<=R){
			Add(x,k);
			return;
		}
		pushdown(x);
		if (L<=mid) update(ls,l,mid,L,R,k);
		if (R>mid) update(rs,mid+1,r,L,R,k);
		pushup(x);
	}
	int query(){
		return s[1];
	}
}
using namespace seg;
int main(){
	freopen("4653.in","r",stdin);
	freopen("4653.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i){
		a[i].l=read(),a[i].r=read();
		a[i].len=a[i].r-a[i].l;
		val[++tot]=a[i].l;
		val[++tot]=a[i].r;
	}	
	sort(val+1,val+tot+1);
	tot=unique(val+1,val+tot+1)-val-1;
	for (int i=1;i<=n;++i){
		a[i].l=lower_bound(val+1,val+tot+1,a[i].l)-val;
		a[i].r=lower_bound(val+1,val+tot+1,a[i].r)-val;
		mx=max(mx,a[i].r);
	}
	sort(a+1,a+n+1);
	int now=1;
	for (int i=1;i<=n;++i){
		update(1,1,mx,a[i].l,a[i].r,1);
		while (query()>=m){
			chkmin(ans,a[i].len-a[now].len);
			update(1,1,mx,a[now].l,a[now].r,-1);
			++now;
		}
	}
	printf("%d\n",ans);
	return 0;
}
