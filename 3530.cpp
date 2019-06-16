#include<bits/stdc++.h>
inline int read(){
	int x=0,w=1;
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
using namespace std;
typedef long long ll;
const int N=5005;
const int Mod=1e9+7;
inline void ad(int &x,int y){
	x+=y;
	if (x>=Mod) x-=Mod;
	if (x<0) x+=Mod;
}
inline int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=1ll*res*x%Mod;
		x=1ll*x*x%Mod;
		y>>=1;
	}
	return res;
}
int n,m,tot=1,ans;
int ch[N][10],fail[N];
int vis[N],dp[N][N][2][2];
char s[N],t[N];
queue<int>q;
inline void insert(){
	int len=strlen(t+1),now=1;
	for (int i=1;i<=len;++i){
		int x=t[i]-'0';
		if (!ch[now][x]) ch[now][x]=++tot;
		now=ch[now][x];
	}
	vis[now]=1;
}
inline void build(){
	q.push(1),fail[1]=0;
	for (int i=0;i<10;++i)
		ch[0][i]=1;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=0;i<10;++i){
			if (!ch[x][i]) ch[x][i]=ch[fail[x]][i];
			else fail[ch[x][i]]=ch[fail[x]][i],q.push(ch[x][i]);
			vis[ch[x][i]]|=vis[fail[ch[x][i]]];
		}
	}
}
int main(){
	freopen("3530.in","r",stdin);
	freopen("3530.out","w",stdout);
	scanf("%s",s+1);
	n=strlen(s+1),m=read();
	for (int i=1;i<=m;++i){
		scanf("%s",t+1);
		insert();
	}
/*	for (int i=1;i<=tot;++i){
		for (int j=0;j<=10;++j)
			if (ch[i][j]) printf("%d %d %d\n",i,j,ch[i][j]);
	}*/
	build();
	dp[0][1][0][0]=1;
	for (int i=0;i<n;++i){
		ad(dp[i+1][1][1][0],dp[i][1][1][0]);
		ad(dp[i+1][1][1][0],dp[i][1][0][0]);
		for (int j=0;j<=tot;++j){
			for (int k=0;k<10;++k){
				int nxt=ch[j][k];
				//printf("%d %d %d\n",j,k,nxt);
				if (vis[nxt]) continue;
				if (k+'0'<s[i+1]){
					ad(dp[i+1][nxt][1][1],dp[i][j][1][1]);
					ad(dp[i+1][nxt][1][1],dp[i][j][0][1]);
					if (k){
						ad(dp[i+1][nxt][1][1],dp[i][j][1][0]);
						ad(dp[i+1][nxt][1][1],dp[i][j][0][0]);
					}
				}else if (k+'0'==s[i+1]){
					ad(dp[i+1][nxt][1][1],dp[i][j][1][1]);
					ad(dp[i+1][nxt][0][1],dp[i][j][0][1]);
					if (k){
						ad(dp[i+1][nxt][1][1],dp[i][j][1][0]);
						ad(dp[i+1][nxt][0][1],dp[i][j][0][0]);
					}
				}else{
					ad(dp[i+1][nxt][1][1],dp[i][j][1][1]);
					ad(dp[i+1][nxt][1][1],dp[i][j][1][0]);
				}
			}
		}
	}
	for (int i=0;i<=tot;++i){
		ad(ans,dp[n][i][1][1]);
		ad(ans,dp[n][i][0][1]);
	}
	/*for (int i=1;i<=n;++i)
		for (int j=1;j<=tot;++j){
			printf("dp[%d][%d][0][0]=%d\n",i,j,dp[i][j][0][0]);
			printf("dp[%d][%d][0][1]=%d\n",i,j,dp[i][j][0][1]);
			printf("dp[%d][%d][1][0]=%d\n",i,j,dp[i][j][1][0]);
			printf("dp[%d][%d][1][1]=%d\n",i,j,dp[i][j][1][1]);
		}*/
	printf("%d\n",ans);
	return 0;
}
