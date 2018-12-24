#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
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
int n,m,k;
int ans=-1e9;
void solve1(){
	int s[105],dp[105][15]={0};
	for (int i=1;i<=n;++i)
		s[i]=s[i-1]+read();
	for (int i=1;i<=n;++i)
		for (int t=1;t<=k;++t) 
			for (int j=0;j<i;++j)
				for (int tmp=j+1;tmp<=i;++tmp)
					dp[i][t]=dp[i][t]>(dp[j][t-1]+s[i]-s[tmp-1])?dp[i][t]:(dp[j][t-1]+s[i]-s[tmp-1]);
	for (int i=1;i<=n;++i)
		ans=ans>dp[i][k]?ans:dp[i][k];	
}
void solve2(){
	int s1[105],s2[105];
	int dp[105][105][15];
	for (int i=1;i<=n;++i){
		s1[i]=s1[i-1]+read();
		s2[i]=s2[i-1]+read();	
	}
	for (int t=1;t<=k;++t){
		for (int i=1;i<=n;++i){
			for (int j=1;j<=n;++j){
				dp[i][j][t]=dp[i][j-1][t]>dp[i-1][j][t]?dp[i][j-1][t]:dp[i-1][j][t];	
				for (int l=0;l<i;++l) dp[i][j][t]=dp[i][j][t]>dp[l][j][t-1]+s1[i]-s1[l]?dp[i][j][t]:dp[l][j][t-1]+s1[i]-s1[l];
				for (int l=0;l<j;++l) dp[i][j][t]=dp[i][j][t]>dp[i][l][t-1]+s2[j]-s2[l]?dp[i][j][t]:dp[i][l][t-1]+s2[j]-s2[l];
				if (i==j){
					for (int l=0;l<i;++l)
						dp[i][j][t]=dp[i][j][t]>dp[l][l][t-1]+s1[i]-s1[l]+s2[j]-s2[l]?dp[i][j][t]:dp[l][l][t-1]+s1[i]-s1[l]+s2[j]-s2[l];
				}
			}
		}
	}
	ans=dp[n][n][k];
}
int main(){
	n=read();m=read();k=read();
	if (m==1) solve1();
	else solve2();
	printf("%d\n",ans);
	return 0;
}

