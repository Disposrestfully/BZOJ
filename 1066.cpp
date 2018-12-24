#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
int read(){
	int x=0;
	char ch=0;
	while (ch<'0' || ch>'9') ch=getchar();
	while (ch<='9' && ch>='0'){
		x=(x<<1)+(x<<3)+ch-'0';
		ch=getchar();
	}
	return x;
}
const int inf=1e9;
const int N=10010;
struct node{
	int next,to,w;
}a[N<<1];
int head[N],cnt=1;
void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
void Add(int u,int v,int w){
	add(u,v,w);
	add(v,u,0);
}	
int n,m,d;
char s[30];
int T;
int getid(int x,int y){
	return (x-1)*m+y+1;
}
int lv[N<<3],q[N];
bool bfs(){
	memset(lv,0,sizeof(lv));
	int f=0,l=1;
	q[1]=lv[1]=1;
	int now=lv[T];
	while (f<l){
		int x=q[++f];
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (!lv[y] && a[i].w){
				lv[y]=lv[x]+1;
				q[++l]=y;
			}
		}
	}
	return lv[T]!=now;  	
}
int flow(int s,int f){
	if (s==T || !f) return f;
	int res=0;
	for (int i=head[s];i;i=a[i].next){
		int y=a[i].to;
		if (a[i].w && lv[y]==lv[s]+1){
			int x=flow(y,min(f,a[i].w));
			if (x){
				f-=x;res+=x;
				a[i].w-=x;a[i^1].w+=x;
				if (!f) return res;
			}else lv[y]=-1;
		}
	}
	return res;
}
int dist(int lx,int ly,int rx,int ry){
	return (lx-rx)*(lx-rx)+(ly-ry)*(ly-ry);
}
int mp[30][30];
void solve(int x,int y){
	for (int i=max(x-d,1);i<=x+d && i<=n;++i)
		for (int j=max(y-d,1);j<=y+d && j<=m;++j)
			if (dist(i,j,x,y)<=d*d && (i!=x || j!=y) && mp[i][j]) 
				Add(getid(x,y)+n*m,getid(i,j),inf);
}
int main(){
	n=read();m=read();d=read();
	int id=1;T=2*n*m+2;
	for (int i=1;i<=n;++i){
		scanf("%s",s+1);
		for (int j=1;j<=m;++j){
			++id;
			mp[i][j]=s[j]-'0';
			if (mp[i][j]) Add(id,id+n*m,mp[i][j]);
		}
	}
	for (int i=1;i<=d;++i)
		for (int j=d+1;j<=n-d;++j){
			Add(getid(j,i)+n*m,T,inf);
			Add(getid(j,m-i+1)+n*m,T,inf);
		}
	for (int i=1;i<=d;++i)
		for (int j=1;j<=m;++j){
			Add(getid(i,j)+n*m,T,inf);
			Add(getid(n-i+1,j)+n*m,T,inf);
		}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			if (mp[i][j]) solve(i,j);
	int ans=0;
	for (int i=1;i<=n;++i){
		scanf("%s",s+1);
		for (int j=1;j<=m;++j){
			if (s[j]=='.') continue;
			++ans;
			Add(1,getid(i,j),1);
		}
	}
	while (bfs()){
		ans-=flow(1,inf);
	}
	printf("%d\n",ans);
	return 0;
}
