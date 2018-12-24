#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=6005;
const int Mod=10007;
int p[N],fail[N],tot=1;
int next[N][26],n,m;
int q[N<<4],dp[105][N];
char s[N];
void insert(){
	int k=strlen(s);
	int now=1;
	for (int i=0;i<k;++i){
		int x=s[i]-'A';
		if (!next[now][x]) next[now][x]=++tot;
		now=next[now][x];
	}
	p[now]=1;
}
void build(){
	fail[1]=0;
	int f=0,l=1;
	q[0]=1;
	while (f<l){
		int x=q[f++];
		for (int i=0;i<26;++i){
			if (!next[x][i]) continue;
			int k=fail[x];
			while (!next[k][i]) k=fail[k];
			fail[next[x][i]]=next[k][i];
			if (p[next[k][i]]) p[next[x][i]]=1;
			q[l++]=next[x][i];
		}
	}
}
void solve(int x){
	for (int i=1;i<=tot;++i){
		if (p[i] || !dp[x-1][i]) continue;
		for (int j=0;j<26;++j){
			int k=i;
			while (!next[k][j]) k=fail[k];
			dp[x][next[k][j]]+=dp[x-1][i];
			if (dp[x][next[k][j]]>=Mod) dp[x][next[k][j]]-=Mod;
		}
				
	}
}
int main(){
	for (int i=0;i<26;++i) next[0][i]=1;
	dp[0][1]=1;
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i){
		scanf("%s",s);
		insert();
	}
	//printf("Go\n");
	build();
	//printf("Go\n");
	for (int i=1;i<=m;++i) solve(i);
	int ans=1;
	for (int i=1;i<=m;++i)
		ans=(ans*26)%Mod;
	for (int i=1;i<=tot;++i)
		if (!p[i]){
			ans-=dp[m][i];
			if (ans<0) ans+=Mod;
		}
	printf("%d\n",ans);
	return 0;
}
