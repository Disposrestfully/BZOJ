#include<bits/stdc++.h>
#include<sys/mman.h>
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=55;
char s[N];
int dp[N][N][2],n;
inline int chk(int l,int r){
	int mid=(l+r)>>1;
	for (int i=l;i<=mid;++i)
		if (s[i]!=s[i-l+1+mid]) return 0;
	return 1;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	memset(dp,127,sizeof(dp));
	for (int i=1;i<=n;++i)
		dp[i][i][0]=1;
	for (int j=2;j<=n;++j){
		for (int l=1;l+j-1<=n;++l){
			int r=l+j-1;
			if (!(j&1) && chk(l,r)) dp[l][r][0]=min(dp[l][r][0],dp[l][(l+r)>>1][0]+1);
			for (int i=l;i<r;++i)
				dp[l][r][0]=min(dp[l][r][0],dp[l][i][0]+r-i);
			for (int i=l;i<r;++i)
				dp[l][r][1]=min(dp[l][r][1],min(dp[l][i][0],dp[l][i][1])+1+min(dp[i+1][r][0],dp[i+1][r][1]));		
		}
	}	
	printf("%d\n",min(dp[1][n][0],dp[1][n][1]));
	return 0;
}
