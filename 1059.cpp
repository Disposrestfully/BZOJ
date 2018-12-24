#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[210][210]={0},f[210]={0},p[210]={0},n;
int dfs(int x){
	for (int i=1;i<=n;i++){
		if (a[x][i]==1 && p[i]==0){
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
	int i,j,k,m;
	int T;
	scanf("%d",&T);
	while (T--){
		scanf("%d",&n);
		memset(a,0,sizeof(a));
		memset(f,0,sizeof(f));
		for (i=1;i<=n;i++){
			for (j=1;j<=n;j++){
				scanf("%d",&k);	
				a[i][j]=k;
			}
		}
		for (i=1;i<=n;i++){
			memset(p,0,sizeof(p));	
			dfs(i);
		}
		int flag=1;
		for (i=1;i<=n;i++){
			if (f[i]==0){
				flag=0;
				break;	
			}
		}
		if (flag) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}

