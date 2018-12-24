#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
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
const int Mod=12345678;
int n,m,k;
int dp[160][160][25][25]; 
int max(int x,int y){
	return x>y?x:y;
}
int main(){
	n=read();m=read();
	k=read();
	dp[0][0][0][0]=1;
	for (int i=0;i<=n;++i)
		for (int j=0;j<=m;++j)
			for (int l=0;l<=k;++l)
				for (int r=0;r<=k;++r){
					if (i+1<=n && l+1<=k){
						dp[i+1][j][l+1][max(r-1,0)]+=dp[i][j][l][r];
						dp[i+1][j][l+1][max(r-1,0)]%=Mod;
					}
					if (j+1<=m && r+1<=k){
						dp[i][j+1][max(l-1,0)][r+1]+=dp[i][j][l][r];
						dp[i][j+1][max(l-1,0)][r+1]%=Mod;
					}
				}
	int ans=0;
	for (int i=0;i<=k;++i)
		for (int j=0;j<=k;++j)
			ans=(ans+dp[n][m][i][j])%Mod;
	printf("%d\n",ans);
	return 0;
}

