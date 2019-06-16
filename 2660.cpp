#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
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
const int N=1e5+5;
ll n,tot=2,tt;
ll f[N],p[N];
ll dp[N][2];
int main(){
	freopen("2660.in","r",stdin);
	freopen("2660.out","w",stdout);
	n=read(),f[1]=1,f[2]=2;
	while (f[tot]+f[tot-1]<=n){
		f[tot+1]=f[tot]+f[tot-1];
		++tot;
	}
	for (int i=tot;i;--i)
		if (n>=f[i]){
			n-=f[i];
			p[++tt]=i;
		}
	reverse(p+1,p+tt+1);
	dp[1][1]=1,dp[1][0]=(p[1]-1)>>1ll;
	for (int i=2;i<=tt;++i){
		dp[i][1]=dp[i-1][0]+dp[i-1][1];
        dp[i][0]=dp[i-1][0]*((p[i]-p[i-1])>>1ll)+dp[i-1][1]*((p[i]-p[i-1]-1)>>1);
	}
	printf("%lld\n",dp[tt][1]+dp[tt][0]);
	return 0;
}
