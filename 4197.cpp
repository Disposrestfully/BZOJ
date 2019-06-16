#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
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
            static int a[100]; 
            register int t=0;
            while(x) a[++t]=x%10,x/=10;
            while(t) *iter++='0'+a[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
const int N=505;
int n,all,Mod,ans;
int dp[N][N],f[2][N][N],g[2][N][N];
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
int isprime[N],prime[N],ptot;
inline void get_prime(int prange){
	isprime[1]=1;
	for (int i=2;i<=prange;++i){
		if (!isprime[i]) prime[++ptot]=i;
		for (int j=1;j<=ptot && prime[j]*i<=prange;++j){
			isprime[i*prime[j]]=1;
			if (!(i%prime[j])) break;	
		}
	}
}
struct node{
	int s,mx;
	inline bool operator < (const node &u)const{
		return mx<u.mx;
	}
}a[N];
signed main(){
	freopen("4197.in","r",stdin);
	freopen("4197.out","w",stdout);
	get_prime(20),all=(1<<ptot)-1;
	n=read()-1,Mod=read();
	for (int i=1;i<=n;++i){
		int now=i+1;
		for (int j=1;j<=ptot;++j){
			if (now%prime[j]==0){
				a[i].s|=(1<<(j-1));
				while (now%prime[j]==0) now/=prime[j];	
				a[i].mx=max(a[i].mx,prime[j]);
			}
		}
		a[i].mx=max(a[i].mx,now);
	}
	sort(a+1,a+n+1);
	dp[0][0]=1;
	for (int i=1,j=1;i<=n;i=j+1){
		while (j+1<=n && a[j+1].mx==a[i].mx) ++j;
		for (int k1=0;k1<=all;++k1)
			for (int k2=0;k2<=all;++k2)
				f[0][k1][k2]=g[0][k1][k2]=dp[k1][k2];
		int now=0;
		for (int k=i;k<=j;++k){
			now^=1;
			memset(f[now],0,sizeof(f[now]));
			memset(g[now],0,sizeof(g[now]));
			for (int k1=0;k1<=all;++k1)
				for (int k2=0;k2<=all;++k2){
					if (!(a[k].s&k2)) ad(f[now][k1|a[k].s][k2],f[now^1][k1][k2]);
					if (!(a[k].s&k1)) ad(g[now][k1][k2|a[k].s],g[now^1][k1][k2]);
					ad(f[now][k1][k2],f[now^1][k1][k2]);
					ad(g[now][k1][k2],g[now^1][k1][k2]);
				}
		}
		for (int k1=0;k1<=all;++k1)
			for (int k2=0;k2<=all;++k2){
				dp[k1][k2]=Mod-dp[k1][k2];
				ad(dp[k1][k2],f[now][k1][k2]);	
				ad(dp[k1][k2],g[now][k1][k2]);	
			}
	}
	for (int k1=0;k1<=all;++k1)
		for (int k2=0;k2<=all;++k2)
			if (!(k1&k2)) ad(ans,dp[k1][k2]);
	printf("%lld\n",ans);
	return 0;
}
