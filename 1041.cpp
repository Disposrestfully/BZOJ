#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[1000010],c[1000010];
int main(){
	int i,j,k,m,n;
	long long tot=0;
	scanf("%d",&n);
	for (i=1;i<=n;i++){
		scanf("%d",&a[i]);
		tot+=a[i];	
	}
	tot/=n;
	for (i=2;i<=n;i++)
		c[i]=c[i-1]+a[i]-tot;
	sort(c+1,c+n+1);
	long long ans=0;
	k=c[(n+1)/2];
	for (i=1;i<=n;i++)
		ans+=abs(k-c[i]);
	printf("%lld\n",ans);
	return 0;
}

