#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[10010],s[10010],n;
int dfs(int x){
	s[1]=x;
	s[2]=a[1]-s[1];
	if (s[2]<0) return 0;
	for (int i=2;i<=n;i++){
		s[i+1]=a[i]-s[i]-s[i-1];
		if (s[i+1]<0) return 0;
	}
	if (s[n+1]==1) return 0;
	return 1;
}
int main(){
	int i,j,k,m,ans;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
		scanf("%d",&a[i]);	
	ans+=dfs(1);
	ans+=dfs(0);
	printf("%d\n",ans);
	return 0;
}

