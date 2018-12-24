#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=105;
const int S=(1<<15)+5;
int n,k,s;
double dp[N][S];
int p[N],w[N];
int main(){
	scanf("%d%d",&n,&k);
	s=(1<<k)-1;
	for (int i=1;i<=k;++i){
		int x;
		scanf("%d%d",&w[i],&x);
		while (x){
			p[i]+=(1<<(x-1));
			scanf("%d",&x);
		}
	}
	for (int i=n;i;--i){
		for (int j=0;j<=s;++j){
			for (int t=1;t<=k;++t){
				if ((j&p[t])==p[t])
					dp[i][j]+=max(dp[i+1][j],dp[i+1][j|(1<<(t-1))]+w[t]);
				else dp[i][j]+=dp[i+1][j];	
			}
			dp[i][j]/=k;
		}
	}
	printf("%.6lf\n",dp[1][0]);
	return 0;
}
