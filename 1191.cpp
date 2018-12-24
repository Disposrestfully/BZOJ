#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[1010][1010]={0},p[1010],f[1010]={0};
int n,m;
int dfs(int x){
	int i;
	for (i=0;i<m;i++){
		if (a[x][i]==1 && !p[i]){
			p[i]=1;
			if (f[i]==0 || dfs(f[i])){
				f[i]=x;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	int i,j,k;
	scanf("%d%d",&m,&n);
	for (i=1;i<=n;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		a[i][x]=a[i][y]=1;
	}
	int ans=0;
	for (i=1;i<=n;i++){
		memset(p,0,sizeof(p));	
		if (dfs(i)) ans++;
		else break;
	}
	printf("%d\n",ans);
	return 0;
}

