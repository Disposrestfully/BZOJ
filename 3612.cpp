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
const int N=1e5+5;
int n,m,ans,Mod;
int dp[N][15];
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
}
int main(){
	freopen("3612.in","r",stdin);
	freopen("3612.out","w",stdout);
	int T=read();
	while (T--){
		n=read(),m=read(),Mod=read();
		dp[0][0]=1,ans=0;
		for (int i=1;i<=n*m;++i)
			for (int j=1;j<=m;++j){
				dp[i][j]=0;
				if (i>=j){
					ad(dp[i][j],dp[i-j][j]);
					ad(dp[i][j],dp[i-j][j-1]);
				}
				if (i>n) ad(dp[i][j],Mod-dp[i-n-1][j-1]);
			}
		for (int i=1;i<=n*m;++i)
			for (int j=1;j<=m;++j){
				ad(ans,1ll*dp[i][j]*dp[i][m-j]%Mod);
				if (j^m) ad(ans,1ll*dp[i][j]*dp[i][m-j-1]%Mod);
			}
		ad(ans,m==1);
		Print(ans);
	}	
	io::flush();
	return 0;
}
