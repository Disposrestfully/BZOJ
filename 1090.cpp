#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define read() Re.Read()
#define lowbit(i) i&(-i)
//#define Get_Char() getchar()
using namespace std;
typedef long long ll;
const int N=105;
int dp[N][N],p[N][N],n;
char s[N];
bool chk(int l1,int r1,int l2,int r2){
	if ((r1-l1+1)%(r2-l2+1)) return 0;
	for (int i=l1;i<=r1;++i)
		if (s[i]!=s[(i-l1)%(r2-l2+1)+l2]) return 0;
	return 1;
}
int get(int x){
	int res=0;
	while (x){
		x/=10;
		++res;
	}
	return res;
}
int solve(int l,int r){
	if (l==r) return 1;
	if (p[l][r]) return dp[l][r];
	p[l][r]=1;
	int res=r-l+1;
	for (int i=l;i<r;++i){
		res=min(res,solve(l,i)+solve(i+1,r));
		if (chk(i+1,r,l,i)) res=min(res,solve(l,i)+2+get((r-i)/(i-l+1)+1));
	}
	dp[l][r]=res;
	return res;
}
int main(){
	scanf("%s",s+1);
	n=strlen(s+1);
	printf("%d\n",solve(1,n));
	return 0;
}
