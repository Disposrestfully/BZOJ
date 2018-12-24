#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
using namespace std;
const int Mod=100003;
long long pow(long long x,long long y){
	long long s=1,base=x%Mod,k=y;	
	while (k>0){
		if (k%2==1){
			s=s*base;
			s%=Mod;
			s=(s+Mod)%Mod;
			k--;
		}
		base*=base;
		base%=Mod;
		base=(base+Mod)%Mod;
		k/=2;
	}
	return s;
}
int main(){
	long long i,j,k,m,n,ans;
	scanf("%lld%lld",&m,&n);
	k=pow(m,n);
	ans=k;
	k=pow(m-1,n-1);
	m=(m*k)%Mod;
	m=(m+Mod)%Mod;
	ans=(ans-m)%Mod;
	ans=(ans+Mod)%Mod;
	printf("%lld\n",ans);
	return 0;
}

