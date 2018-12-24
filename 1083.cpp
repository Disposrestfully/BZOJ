#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int f[310];
struct node{
	int x,y,w;
}a[10010];
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
}
int kru(int n){
	int max=0;
	for (int i=1;i<=n;i++){
		int fx=find(a[i].x),fy=find(a[i].y);
		if (fx!=fy){
			f[fy]=f[fx];
			max=a[i].w;	
		}
	}
	return max;
}
int cmp(node x,node y){
	return x.w<y.w;	
}
int main(){
	int i,j,k,m,n;
	scanf("%d%d",&n,&m);
	for (i=1;i<=n;i++) f[i]=i;
	for (i=1;i<=m;i++)
		scanf("%d%d%d",&a[i].x,&a[i].y,&a[i].w);
	sort(a+1,a+m+1,cmp);
	printf("%d %d\n",n-1,kru(m));
	return 0;
}

