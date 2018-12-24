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
const int N=1e5+5;
struct node{
	int next,to,w;
}a[N*20];
int head[N],cnt;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;	
}
int n,m,mx,sum=0;
int q[N],d[N],vis[N];
int gcd(int x,int y){
	if (!y) return x;
	if (!x) return y;
	return gcd(y,x%y);
}
void bfs(int x){
	int f=0,l=1;
	int mxl=0,mnl=0;
	q[1]=x;d[x]=0;
	vis[x]=1;
	while (f!=l){
		int p=q[++f];
		if (f>N) f%=N;
		for (int i=head[p];i;i=a[i].next){
			int y=a[i].to;
			if (vis[y]){
				int	k=d[p]+a[i].w-d[y];
				mx=gcd(mx,k);
			}else{
				vis[y]=1;
				d[y]=d[p]+a[i].w;
				q[++l]=y;
				if (l>N) l%=N;
				mxl=max(d[y],mxl);
				mnl=min(d[y],mnl);
			}
		}
	}
	sum+=mxl-mnl+1;
}
int main(){
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		init(u,v,1);
		init(v,u,-1);	
	}
	memset(d,-1,sizeof(d));
	memset(vis,0,sizeof(vis));
	for (int i=1;i<=n;++i)
		if (!vis[i])
			bfs(i);
	if (mx<0) mx=-mx;
	if (mx){
		if (mx<3) printf("-1 -1\n");
		else{
			int ans=3;
			while (ans<=mx && mx%ans!=0) ++ans;
			printf("%d %d\n",mx,ans);
		}
		return 0;
	}
	if (sum<3) printf("-1 -1\n");
	else printf("%d 3\n",sum);
	return 0;
}

