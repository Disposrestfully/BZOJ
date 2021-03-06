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
const int N=2000+5;
int n,Mod;
int f[N],dp[N];
int c[N][N];
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
inline void init(){
	for (int i=0;i<=n;++i)
		c[i][i]=c[i][0]=1;
	for (int i=1;i<=n;++i)
		for (int j=1;j<i;++j)
			c[i][j]=(c[i-1][j]+c[i-1][j-1])%Mod;
}
int main(){
	freopen("5305.in","r",stdin);
	freopen("5305.out","w",stdout);
	n=read(),Mod=read();
	init();
	dp[0]=0,f[0]=1;
	dp[1]=n-1,f[1]=1;
	for (int i=2;i<=n;++i){
		for (int j=0;j<i;++j){
			int cnt=1ll*f[j]*f[i-j-1]%Mod;
			cnt=1ll*cnt*c[i-1][j]%Mod;
			ad(f[i],cnt);
			int now=((1ll*dp[j]*f[i-j-1]%Mod)+(1ll*dp[i-j-1]*f[j]%Mod))%Mod;
			now=1ll*now*c[i-1][j]%Mod;
			ad(dp[i],now);
		}
		ad(dp[i],1ll*f[i]*i*(n-i)%Mod);
	}
	printf("%d\n",dp[n]);
	return 0;
}
