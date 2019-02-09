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
const int N=20;
const int M=1e5+5;
const int S=5005;
const int Mod=1e9+7;
int n,nn,tot,now,m,k1,k2,Ans=1;
int f[M],p[S],a[N],b[N],dp[2][S];
inline int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
}
inline bool chk(int x){
	for (int i=1;i<=17;++i)
		if ((x&(1<<i)) && (x&(1<<(i-1)))) return 0;
	return 1;
}
inline int solve(int x){
	tot=0;
	while (x<=n){
		int k=x;
		a[++tot]=0,x*=k1;
		while (k<=n) ++a[tot],k*=k2;
		b[tot]=1<<a[tot];
	}
	for (int i=1;p[i]<b[1] && i<=m;++i) dp[0][i]=1;
	now=0;
	for (int i=2;i<=tot;++i){
		now^=1;
		memset(dp[now],0,sizeof(dp[now]));
		for (int w1=1;p[w1]<b[i-1] && w1<=m;++w1){
			if (!dp[now^1][w1]) continue;
			for (int w2=1;p[w2]<b[i] && w2<=m;++w2)
				if (!(p[w1]&(p[w2]<<(a[i-1]-a[i])))) ad(dp[now][w2],dp[now^1][w1]);
		}
	}
	int ans=0;
	for (int i=1;p[i]<b[tot] && i<=m;++i)
		ad(ans,dp[now][i]);
	return ans;
}	
int main(){
	freopen("2734.in","r",stdin);
	freopen("2734.out","w",stdout);
	for (int i=0;i<(1<<17);++i)
		if (chk(i)) p[++m]=i;
	nn=read(),k1=read(),k2=read();
	for (int i=1;i<=nn;++i){
		n=now=i;
		while (!(now%k1)) now/=k1;
		while (!(now%k2)) now/=k2;
		if (now^i){
			Ans=1ll*Ans*Pow(f[now],Mod-2)%Mod;
			Ans=1ll*Ans*(f[now]=solve(now))%Mod;
		}else f[now]=2,Ans=2ll*Ans%Mod;
		Print(Ans);
	}
	io::flush();
	return 0;
}
