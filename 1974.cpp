#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
const int N=505;
const int Mod=999911659;
int n,p,now,st;
int las[N],cnt[N],g[15];
int dp[2][N][N];
int c[N][N];
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
inline int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
inline void initc(){
	for (int i=0;i<p;++i){
		c[i][0]=1;
		for (int j=1;j<=9;++j){
			c[i][j]=1ll*c[i][j-1]*((cnt[i]+j-1)%Mod)%Mod;
			c[i][j]=1ll*c[i][j]*Pow(j,Mod-2)%Mod;
		}
	}
}
inline int C(int x,int y){
	return c[x][y];
}
signed main(){
	freopen("1974.in","r",stdin);
	freopen("1974.out","w",stdout);
	n=read(),p=read();
	for (int i=1;i<=n;++i){
		now=((now<<1)+(now<<3)+1)%p;
		if (i==n) st=now;
		if (!las[now]) las[now]=i,++cnt[now];
		else{
			int len=i-las[now];
			for (int j=0;j<p;++j)
				if (las[j]>=las[now]){
					cnt[j]=(n-las[j])/len+1;
					if ((n-las[j])%len==0) st=j;	
				}
			break;
		}
	}
	initc();
	dp[now=0][0][0]=1;
	for (int i=0;i<p;++i){
		if (!cnt[i]) continue;
		now^=1;
		memset(dp[now],0,sizeof(dp[now]));
		for (int t=0;t<p;++t){
			for (int j=8;~j;--j){
				if (!dp[now^1][j][t]) continue;
				for (int k=0;k+j<=8;++k){
					ad(dp[now][j+k][(t+i*k)%p],1ll*dp[now^1][j][t]*C(i,k)%Mod);
				}			
			}
		}
	}
	int ans=0;
	for (int i=0;i<=8;++i)
		ad(ans,dp[now][i][(p-st)%p]);
	printf("%lld\n",ans);
	return 0;
}
