#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
long long read(){
	long long x=0,w=1;
	char ch=0;
	while (ch<'0' || ch>'9'){
		  if (ch=='-') w=-1;
		  ch=getchar();
	}
	while (ch<='9' && ch>='0'){
		  x=(x<<1)+(x<<3)+ch-'0';
		  ch=getchar();
	}
	return x*w;
}
const long long N=5e4+5;
long long n,k,f,l;
long long dp[N],s[N]={0},q[N]={0};  
double gety(long long x){
	return dp[x]+(s[x]+k)*(s[x]+k);
}
double getk(long long x,long long y){
	return (gety(y)-gety(x))/(s[y]-s[x]);
}
int main(){
	//freopen("toy.in","r",stdin);
	n=read();k=read();
	for (long long i=1;i<=n;++i)
		s[i]=s[i-1]+read();
	for (long long i=1;i<=n;++i)
		s[i]+=i;
	f=1;l=1;
	for (long long i=1;i<=n;++i){
		while (f<l && getk(q[f],q[f+1])<2*s[i]) ++f;
		long long p=q[f];
		dp[i]=dp[p]+(s[i]-s[p]-k-1)*(s[i]-s[p]-k-1);
		while (f<l && getk(q[l],q[l-1])>getk(q[l],i)) --l;
		q[++l]=i;
	}
	printf("%lld\n",dp[n]);
	return 0;
}

