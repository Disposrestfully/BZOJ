#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
struct node{
	int x,y;
}a[150010];
int cmp(node u,node v){
	return u.y<v.y;
}
int p[150010];
int ans=0,t=0;
int main(){
	int i,k,n;
	scanf("%d",&n);
	for (i=1;i<=n;i++)
		scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+n+1,cmp);
	for (i=1;i<=n;i++){
		if (t+a[i].x<a[i].y){
			t+=a[i].x;
			p[++ans]=a[i].x;
			int u=ans,v=ans/2;	
			while (v>0 && p[u]>p[v]){
				k=p[u];p[u]=p[v];p[v]=k;
				u=v;v=u/2;	
			}
		}else{
			if (p[1]>a[i].x && ans>=1){
				t=t-p[1]+a[i].x;
				p[1]=a[i].x;
				int u=1,v=2;
				while ((p[u]<p[v] && v<=ans) || (p[u]<p[v+1] && v+1<=ans)){
					if (p[v]<p[v+1] && v+1<=ans) v++;
					k=p[u];p[u]=p[v];p[v]=k;
					u=v;v*=2;
				}
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

