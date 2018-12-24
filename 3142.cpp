#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+5;
inline ll read(){
	ll x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		ch=getchar();
		if (ch=='-') w=-1;	
	}
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x*w;
}
ll n,m,k,Mod,ans,s;
inline int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
int main(){
	n=read(),k=read();
	m=read(),Mod=read();
	if (k==1){
		printf("%lld\n",n%Mod);
		return 0;
	}
	s=Pow(m,k-2);
	ans=(Pow(m,k-1)*(n%Mod))%Mod;
	m=((m+1)*m/2)%Mod;
	m=m*(k-1)%Mod;
	m=m*s%Mod;
	ans=(ans-m+Mod)%Mod;
	printf("%lld\n",ans);
	return 0;
}
