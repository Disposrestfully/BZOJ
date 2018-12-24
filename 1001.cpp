#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<queue>
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
const int N=1e6+5;
struct node{
	int next,to,w;
}a[N*6];
int head[N],cnt=1;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
int q[6*N],lv[N];
int n,m,ans;
int bfs(){
	int f=0,l=1;
	q[0]=1;
	memset(lv,127,sizeof(lv));
	int s=lv[n*m];
	lv[1]=1;
	while (f<l){
		int x=q[f++];
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (a[i].w && lv[y]==s){
				lv[y]=lv[x]+1;
				q[l++]=y;
			}
		}
		if (lv[n*m]!=s) return 1;
	}
	return 0;
}
int dfs(int s,int flow){
	if (flow==0 || s==n*m) return flow;
	int res=0;
	for (int i=head[s];i;i=a[i].next){
		int y=a[i].to;
		if (lv[y]==lv[s]+1 && a[i].w){
			int f=dfs(y,min(flow,a[i].w));
			if (f){
				res+=f;flow-=f;
				a[i].w-=f;a[i^1].w+=f;
				if (!flow) return res;	
			}else lv[y]=-1;
		}
	}
	return res;
}
int main(){
	n=read();m=read();
	for (int i=0;i<n;++i){
		for (int j=1;j<m;++j){
			int w=read();
			init(i*m+j,i*m+j+1,w);	
			init(i*m+j+1,i*m+j,w);
		}
	}
	for (int i=0;i<n-1;++i){
		for (int j=1;j<=m;++j){
			int w=read();
			init(i*m+j,(i+1)*m+j,w);
			init((i+1)*m+j,i*m+j,w);
		}
	}
	for (int i=0;i<n-1;++i){
		for (int j=1;j<m;++j){
			int w=read();
			init(i*m+j,(i+1)*m+j+1,w);
			init((i+1)*m+j+1,i*m+j,w);
		}
	}
	while (bfs()){
		ans+=dfs(1,1<<30);
		//printf("%d\n",ans);	
	}
	printf("%d\n",ans);
	return 0;
}

