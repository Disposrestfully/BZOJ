#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
int read(){
	int x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		  if (ch=='-') w=-1;
		  ch=getchar();
	}
	while (ch<='9' && ch>='0'){
		  x=(x<<1)+(x<<3)+ch-'0';
		  ch=getchar();
	}
	return x*w;
}
const int N=70;
int sr,sb,sg,m,p,n,ans;
int f[N],vis[N],dp[N][N][N];
int c[N],r[N],s[N],tot;
int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=(res*x)%p;
		x=(x*x)%p;
		y>>=1;
	}
	return res;
}
void dfs(int x,int cnt){
	if (vis[x]){
		s[++tot]=cnt;
		return;	
	}
	vis[x]=1;
	dfs(f[x],cnt+1);
}
int main(){
	sr=read();sb=read();sg=read();
	n=sr+sb+sg;
	m=read();p=read();
	c[0]=r[0]=1;
	for (int i=1;i<=max(n,m+1);++i){
		c[i]=(c[i-1]*i)%p;
		r[i]=Pow(c[i],p-2);
	}
	for (int now=1;now<=m;++now){
		tot=0;
		memset(vis,0,sizeof(vis));
		for (int i=1;i<=n;++i)
			f[i]=read();
		for (int i=1;i<=n;++i)
			if (!vis[i])
				dfs(i,0);
		memset(dp,0,sizeof(dp));
		dp[0][0][0]=1;
		int sum=0;
		for (int i=0;i<tot;++i){
			sum+=s[i];
			for (int x=0;x<=sr;++x){
				if (x>sum) break;
				for (int y=0;y<=sb;++y){
					if (sum<x+y) break;
					if (sum-x-y<=sg) dp[i+1][x][y]=(dp[i][x][y]+dp[i+1][x][y])%p;
					if (x+s[i]<=sr) dp[i+1][x+s[i]][y]=(dp[i+1][x+s[i]][y]+dp[i][x][y])%p;
					if (y+s[i]<=sb) dp[i+1][x][y+s[i]]=(dp[i+1][x][y+s[i]]+dp[i][x][y])%p;
				}
			}
		}
		ans=(ans+dp[tot][sr][sb])%p;
	}
	int l=(c[n]*r[sr]*r[sb]*r[sg])%p;
	ans=(ans+l)%p;
	ans=(ans*Pow(m+1,p-2))%p;
	printf("%d\n",ans);
	return 0;
}

