#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
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
long long dp[1010][1010]; 
long long prime[1010],tot=0;
long long p[1010];
void get_prime(long long mx){
	p[1]=1;
	for (long long i=2;i<=mx;++i){
		if (!p[i]) prime[++tot]=i;
		for (long long j=1;j<=tot && i*prime[j]<=mx;++j){
			p[i*prime[j]]=1;
			if (i%prime[j]==0) break;	
		}
	}
}
int main(){
	long long n=read();
	get_prime(n);
	dp[0][0]=1;
	for (long long i=1;i<=tot;++i){
		for (long long j=0;j<=n;++j) dp[i][j]=dp[i-1][j];
		for (long long j=prime[i];j<=n;j*=prime[i])	
			for (long long k=0;k<=n-j;++k)
				dp[i][k+j]+=dp[i-1][k];
	}
	long long ans=0;
	for (long long i=0;i<=n;++i)
		ans+=dp[tot][i];
	printf("%lld\n",ans);
	return 0;
}

