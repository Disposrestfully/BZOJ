#include<cstdio>
#include<algorithm>
#include<cstring>
using namespace std;
long long read(){
	long long x=0;
	char ch=0;
	while (ch<'0' || ch>'9')
		ch=getchar();
	while (ch>='0' && ch<='9'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x;
}
const int N=50010;
struct node{
	long long next,to,w;
}a[N<<2];
long long head[N],cnt;
void add(long long u,long long v,long long w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
long long s[100];
void insert(long long x){
	for (int i=60;i>=0;--i){
		if (!(x&((long long)1<<i))) continue;
		if (!s[i]){
			s[i]=x;
			return;
		}else x^=s[i];
	}
}
long long n,m,ans=0;
bool vis[N];
long long p[N];
void dfs(long long x){
	for (long long i=head[x];i;i=a[i].next){
		long long y=a[i].to;
		if (!vis[y]){
			p[y]=p[x]^a[i].w;
			vis[y]=1;
			dfs(y);
		}else{
			long long t=a[i].w^p[x]^p[y];
			if (t) insert(t);
		}
	}
}
long long find_max(long long &x){
	for (int i=60;i>=0;--i)
		x=max(x,x^s[i]);
}
int main(){
	n=read();m=read();
	for (int i=1;i<=m;++i){
		long long u=read(),v=read(),w=read();
		add(u,v,w);add(v,u,w);
	}
	vis[1]=1;p[1]=0;
	dfs(1);
	ans=p[n];
	find_max(ans);
	printf("%lld\n",ans);
	return 0;
}
