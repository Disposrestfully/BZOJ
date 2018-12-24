#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define read() Re.read()
#define lowbit(i) i&(-i)
//#define Get_Char() getchar()
using namespace std;
typedef long long ll;
const int N=1e5+5;
int dp[15][15][2][2];
int s[15],tot;
void calc(int x){
	tot=0;
	while (x){
		s[++tot]=x%10;
		x/=10;
	}
	for (int i=1;i<tot-i+1;++i)
		swap(s[i],s[tot-i+1]);
}
int solve(int x){
	calc(x);
	memset(dp,0,sizeof(dp));
	for (int i=1;i<=tot;++i){
		if (i==1){
			dp[1][0][0][0]=1;
			for (int j=1;j<s[1];++j)
				dp[1][j][0][1]=1;
			dp[1][s[1]][1][1]=1;
			continue;
		}
		for (int j=0;j<=9;++j){
			if (dp[i-1][j][0][1]){
				for (int k=0;k<=9;++k)
					if (k-j>=2 || j-k>=2) dp[i][k][0][1]+=dp[i-1][j][0][1];
			}
			if (dp[i-1][j][1][1]){
				for (int k=0;k<s[i];++k)
					if (k-j>=2 || j-k>=2) dp[i][k][0][1]+=dp[i-1][j][1][1];
				if (s[i]-j>=2 || j-s[i]>=2) dp[i][s[i]][1][1]+=dp[i-1][j][1][1];
			}
			if (dp[i-1][j][0][0]){
				dp[i][0][0][0]+=dp[i-1][j][0][0];
				for (int k=1;k<=9;++k)
					dp[i][k][0][1]+=dp[i-1][j][0][0];
			}
		}
	}	
	int res=0;
	for (int i=0;i<=9;++i)
		res+=dp[tot][i][1][1]+dp[tot][i][0][1];
	return res;
}
int main(){
	int n,m;
	scanf("%d%d",&n,&m);
	printf("%d\n",solve(m)-solve(n-1));
	return 0;
}
