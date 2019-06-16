#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define read() Read<int>()
#define int ll
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
const int N=1e5+5;
const int B=223;
int n,m,tot,L,R,now;
int cl[N],cr[N];
int a[N],ans[N];
struct node{
	int l,r,id,opt;
	inline bool operator < (const node &u)const{
		if ((l/B)==(u.l/B)) return r<u.r;
		return l<u.l;
	}
}q[N<<1];
signed main(){
	freopen("5016.in","r",stdin);
	freopen("5016.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	m=read();
	for (int i=1;i<=m;++i){
		int l1=read()-1,r1=read();
		int l2=read()-1,r2=read();
		q[++tot]=(node){r1,r2,i,1};
		q[++tot]=(node){l1,r2,i,-1};
		q[++tot]=(node){r1,l2,i,-1};
		q[++tot]=(node){l1,l2,i,1};
	}
	for (int i=1;i<=tot;++i)
		if (q[i].l>q[i].r) swap(q[i].l,q[i].r);
	sort(q+1,q+tot+1);
	for (L=1;L<=q[1].l;++L) ++cl[a[L]];
	for (R=1;R<=q[1].r;++R) ++cr[a[R]],now+=cl[a[R]];
	--L,--R;
	ans[q[1].id]+=now*q[1].opt;
	//printf("%d %d %d\n",L,R,now);
	for (int i=2;i<=tot;++i){
		while (L<q[i].l) ++L,++cl[a[L]],now+=cr[a[L]];
		while (L>q[i].l) --cl[a[L]],now-=cr[a[L]],--L;
		while (R<q[i].r) ++R,++cr[a[R]],now+=cl[a[R]];
		while (R>q[i].r) --cr[a[R]],now-=cl[a[R]],--R;
		ans[q[i].id]+=now*q[i].opt;
		//printf("%d %d %d\n",L,R,now);
	}
	for (int i=1;i<=m;++i) Print(ans[i]);
	io::flush();
	return 0;
}
