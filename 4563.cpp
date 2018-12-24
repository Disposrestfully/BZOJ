#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
int a[100010]={1},len=1;
void solve(int x){
	for (int i=1;i<=len;i++)
		a[i]*=x;	
	for (int i=1;i<len;i++){
		a[i+1]+=a[i]/10;
		a[i]%=10;	
	}
	while (a[len]>=10){
		len++;
		a[len]+=a[len-1]/10;
		a[len-1]%=10;	
	}
}
void add(int x){
	a[1]+=x;
	for (int i=1;i<len;i++){
		if (a[i]<0){
			a[i]+=10;
			a[i+1]--;	
		}
	}
	while (a[len]<0 && len!=1)
		len--;	
	for (int i=1;i<len;i++){
		a[i+1]+=a[i]/10;
		a[i]%=10;	
	}
	while (a[len]>=10){
		len++;
		a[len]+=a[len-1]/10;
		a[len-1]%=10;	
	}
}
int main(){
	int i,n;
	a[1]=1;
	//freopen("t3.in","r",stdin);
	//freopen("t3.out","w",stdout);
	scanf("%d",&n);
	//if (n==2) printf("1\n");
	//else{
		for (i=3;i<=n;i++){
			solve(i);
			if (i%2==0) add(1);
			else add(-1);
		}
	//}
	for (i=len;i>=1;i--)
		printf("%d",a[i]);	
	printf("\n");
	return 0;
}

