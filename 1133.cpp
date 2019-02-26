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
const int N=605;
int n,k,ans,pos;
int dp[N][N],pre[N][N];
int a[N][N],s[N],p[N];
void print(int x,int now){
	if (!now) return;
	print(pre[x][now],now-1);
	printf("%d%c",x,now==k?'\n':' ');
}
int main(){
	freopen("1133.in","r",stdin);
	freopen("1133.out","w",stdout);
	n=read(),k=read();
	for (int i=1;i<n;++i){
		for (int j=i+1;j<=n;++j){
			a[i][j-1]=read();
			for (int t=i;t<j;++t)
				s[t]+=a[i][j-1];
		}
	}
	for (int i=1;i<=n;++i){
		p[i]=s[i];
		for (int j=1;j<i;++j)
			for (int t=j;t<i;++t)
				p[t]-=a[j][i-1];
		for (int j=0;j<i;++j){
			for (int t=0;t<=j && t<k;++t){
				if (dp[i][t+1]<dp[j][t]-p[j]+s[i])	pre[i][t+1]=j;
				dp[i][t+1]=max(dp[i][t+1],dp[j][t]-p[j]+s[i]);
			}
		}
		if (ans<dp[i][k]) pos=i;
		ans=max(ans,dp[i][k]);
	}
	print(pos,k);
	return 0;
}
