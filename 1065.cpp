#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef double ll;
const int N=70;
int n,m,s[N],len;
ll k,c[N],ans=-1,p[N],g[N];
ll dp[N][N][N],f[N][N][N];
void dfs(int x,int dep){
	for (int i=2;i<=n;++i)
		if (s[i]==x) dfs(i,dep+1);
	for (int d=min(2,dep);d<=dep;++d){
		for (int j=0;j<=m;++j) g[j]=0;
		for (int i=2;i<=n;++i){
			if (s[i]==x){
				for (int j=m;~j;--j)
					for (int k=j;~k;--k)
						g[j]=max(g[j],g[k]+f[i][j-k][d]);
			}
		}
		for (int j=0;j<=m;++j)
			dp[x][j][d]=g[j]+p[d]*c[x];
	}
	if (dep>1){
		for (int j=0;j<=m;++j) g[j]=0;
		for (int i=2;i<=n;++i)
			if (s[i]==x){
				for (int j=m;~j;--j)
					for (int k=j;~k;--k)
						g[j]=max(g[j],g[k]+f[i][j-k][1]);
			}
		for (int j=1;j<=m;++j)
			dp[x][j][1]=g[j-1]+k*c[x];
	}
	for (int j=0;j<=m;++j)
		for (int k=0;k<dep;++k)
			f[x][j][k]=max(dp[x][j][k+1],dp[x][j][1]);
}
void solve(int tmp){
	for (int i=0;i<=n;++i)
		for (int j=0;j<=m;++j)
			for (int k=0;k<=n;++k)
				dp[i][j][k]=0;
	for (int i=1;i<=n;++i)
		if (s[i]==1) dfs(i,1);
	for (int i=0;i<=m;++i) g[i]=0;
	for (int i=1;i<=n;++i)
		if (s[i]==1){
			for (int j=m;~j;--j)
				for (int k=j;~k;--k)
					g[j]=max(g[j],g[k]+dp[i][j-k][1]);
		}
	ll mx=-1;
	for (int i=0;i<=m-tmp;++i)
		mx=max(mx,g[i]);
	ans=max(ans,(mx+c[1])/(1-p[len]));
}
int main(){
	//freopen("1.in","r",stdin);
	scanf("%d%d%lf",&n,&m,&k);
	p[0]=1.0;
	for (int i=1;i<=n;++i) p[i]=p[i-1]*k;
	for (int i=1;i<=n;++i) scanf("%d",&s[i]);
	for (int i=1;i<=n;++i) scanf("%lf",&c[i]);
	len=2;	
	for (int i=s[1];i!=1;i=s[i]){
		int fa=s[i];
		s[i]=1;
		solve(fa!=1);
		s[i]=fa;
		++len;
	}
	printf("%.2lf\n",ans);
	return 0;
}
