#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
int read(){
	int x=0,w=1;
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
struct node{
	int to,next;
}a[200010];
int head[100010];
int d[100010],sz[100010];
int n,m,cnt=0,ans=0;
void init(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;	
}
void dfs(int x,int fa){
	sz[x]=0;
	if (head[x]==0 && fa!=0){
		sz[x]=1;
		return;	
	}
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (!sz[y]) dfs(y,i);
		sz[x]+=sz[y];	
	}
	if (fa==0) ans+=sz[x];
}
int main(){
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		init(v,u);d[u]++;
	}
	for (int i=1;i<=n;++i)
		if (!d[i]) dfs(i,0);
	printf("%d\n",ans);
	return 0;
}

