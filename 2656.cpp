#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
int f[N];
int main(){
	f[0]=0,f[1]=1;
	for (int i=1;i<=20;++i){
		if (i&1) f[i]=f[i>>1]+f[i-(i>>1)];
		else f[i]=f[i>>1];
		printf("%d ",f[i]);
	}
	printf("\n");
	return 0;
}
