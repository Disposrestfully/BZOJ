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
const int N=2005;
const int M=2000;
int n,m,now,ans;
int dp[2][N],vis[2][N];
struct node{
	int w,v;
};
vector<node>g[35];
inline void solve(){
	memset(dp[0],0,sizeof(dp[0]));
	memset(vis[0],0,sizeof(vis[0]));
	now=ans=0,vis[0][0]=1;
	for (int i=30;~i;--i){
		now^=1;
		memset(dp[now],0,sizeof(dp[now]));
		memset(vis[now],0,sizeof(vis[now]));
		for (int j=0;j<=M;++j){
			if (!vis[now^1][j]) continue;
			int k=min(M,(j<<1)+((m&(1<<i))!=0));
			dp[now][k]=max(dp[now][k],dp[now^1][j]),vis[now][k]=1;
		}
		for (int j=0,sz=g[i].size();j<sz;++j){
			for (int k=g[i][j].w;k<=M;++k){
				if (!vis[now][k]) continue;
				vis[now][k-g[i][j].w]=1;
				dp[now][k-g[i][j].w]=max(dp[now][k-g[i][j].w],dp[now][k]+g[i][j].v);
			}
		}
	}
	for (int i=0;i<=M;++i)
		ans=max(ans,dp[now][i]);
	Print(ans);
}
int main(){
	freopen("1190.in","r",stdin);
	freopen("1190.out","w",stdout);
	while (1){
		n=read(),m=read();
		if (n==-1) break;
		for (int i=0;i<=30;++i)
			g[i]=vector<node>();
		for (int i=1;i<=n;++i){
			int w=read(),v=read(),c=0;
			while (!(w&1)) w>>=1,++c;
			g[c].push_back((node){w,v});
		}
		solve();
	}
	io::flush();
	return 0;
}
