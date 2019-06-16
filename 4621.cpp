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
const int N=505;
const int Mod=1e9+7;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
int n,k,ans;
int a[N],pre[N],nxt[N];
int dp[N][N];
vector<int>g[N];
int main(){
	freopen("4621.in","r",stdin);
	freopen("4621.out","w",stdout);
	n=read(),k=read();
	for (int i=1;i<=n;++i) a[i]=read();
	for (int i=1;i<=n;++i){
		for (pre[i]=i;pre[i] && a[pre[i]]<=a[i];--pre[i]) g[pre[i]].push_back(i);
		for (nxt[i]=i;nxt[i]<=n && a[nxt[i]]<=a[i];++nxt[i]);
	}
	dp[0][0]=1;
	for (int i=1;i<=n;++i){
		ad(dp[i][k],dp[i-1][k]);
		for (int j=k;j;--j){
			int res=dp[pre[i]][j-1];
			for (int t=pre[i]+1;t<nxt[i];++t){
				ad(dp[t][j],res);
				ad(res,dp[t][j-1]);
			}
			ad(dp[i][j-1],dp[i-1][j-1]);
			ad(dp[i][j],Mod-dp[i-1][j-1]);
		}
	}
	for (int i=0;i<=k;++i)
		ad(ans,dp[n][i]);
	printf("%d\n",ans);
	return 0;
}
