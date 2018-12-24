#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int a[110][110],s[110],p[110];
int n;
int dfs(int x){
	for (int i=1;i<=n;i++){
		if (a[x][i]==1 && !p[i]){
			p[i]=1;
			if (s[i]==0 || dfs(s[i])==1){
				s[i]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int i,j,k,m;
	scanf("%d%d",&n,&m);
	for (i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[x][y]=1;
	}
	for (k=1;k<=n;k++)
		for (i=1;i<=n;i++)
			for (j=1;j<=n;j++)
				if (a[i][k] && a[k][j])
					a[i][j]=1;
	for (i=1;i<=n;i++){
		memset(p,0,sizeof(p));
		dfs(i);
	}
	int ans=n;
	for (i=1;i<=n;i++)
		if (s[i]!=0) ans--;
	printf("%d\n",ans);
	return 0;
}
