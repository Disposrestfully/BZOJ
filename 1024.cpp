#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
double min(double x,double y){
	return x<y?x:y;	
}
double max(double x,double y){
	return x>y?x:y;	
}
double dfs(double x,double y,double z){
	if (z==1){
		if (x<y){
			double k=x;x=y;y=k;	
		}
		return x/y;
	}
	double ans=1e7,mx=x/z,my=y/z,ans1,ans2;
	for (double i=1;i*2<=z;i++){
		ans1=max(dfs(mx*i,y,i),dfs(x-mx*i,y,z-i));	
		ans2=max(dfs(x,my*i,i),dfs(x,y-my*i,z-i));
		ans=min(ans,min(ans1,ans2));	
	}
	return ans;
}
int main(){
	double x,y,n;
	scanf("%lf%lf%lf",&x,&y,&n);
	printf("%.6lf\n",dfs(x,y,n));
	return 0;
}

