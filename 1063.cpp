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
const int N=1e5+5;
const int M=10;
struct Readint{
	char buffer[1<<15],*S,*T; 
	inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}
	ll Read(){
	    char c;  
	    ll re=0;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    	}	
 	   	while(c>='0'&&c<='9')  
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re;  
	}
}Re;
struct edge{
	ll next,to;
}e[N<<1];
ll head[N],cnt;
void add(ll u,ll v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
ll n,m,Mod;
ll dp[N][12][3];
ll get(ll x){
	if (!x) return 0;
	return x%Mod?x%Mod:Mod;
}
void dfs(ll x,ll fa){
	ll sz=0;
	for (ll i=head[x];i;i=e[i].next){
		ll y=e[i].to;
		if (y!=fa){
			dfs(y,x);
			++sz;	
		} 
	}
	for (ll i=0;i<=M;++i) dp[x][i][0]=1;
	if (!sz) return;
	for (ll i=head[x];i;i=e[i].next){
		ll y=e[i].to;
		if (y==fa) continue;
		for (ll j=0;j<=M;++j){
			ll t,f1=!j?0:dp[y][j-1][0]+dp[y][j-1][1]+dp[y][j-1][2],f2=dp[y][j][0]+dp[y][j][1];
			t=dp[x][j][2]*f1+dp[x][j][1]*f2;
			dp[x][j][2]=get(t);
			t=dp[x][j][1]*f1+dp[x][j][0]*f2;
			dp[x][j][1]=get(t);
			t=dp[x][j][0]*f1;
			dp[x][j][0]=get(t);
		}
	}
}
int main(){
	//freopen("a.in","r",stdin);
	n=read();m=read();Mod=read();
	//printf("Go\n");
	for (ll i=1;i<=m;++i){
		ll u=read(),v=read();
		add(u,v);add(v,u);
	}
	if (m<n-1){
		printf("-1\n-1\n");
		return 0;
	}
	dfs(1,0);
	for (ll i=0;i<=M;++i){
		ll s=dp[1][i][0]+dp[1][i][1]+dp[1][i][2];
		if (s){
			printf("%lld\n%lld\n",i,s%Mod);
			return 0;
		}
	}
	return 0;
}
