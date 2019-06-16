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
}a[6*N];
int head[N],p[6*N],cnt=0;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;	
	p[cnt]=0;
}
int d[N],vis[N],dep[N],n,m,top=0;
int f[N][21],mx[N][21],sc[N][21];
struct st{
	int w,u;
}h[6*N];
int chk(st x,st y){
	return x.w<y.w;
}
void insert(int w,int u){
	h[++top].w=w;
	h[top].u=u;
	int p=top,q=top/2;
	while (q>0 && chk(h[p],h[q])){
		st temp=h[p];h[p]=h[q];h[q]=temp;
		p=q;q>>=1;	
	}
}
void del(){
	h[1]=h[top];
	--top;
	int p=1,q=2;
	while ((q<=top && chk(h[q],h[p])) || (q+1<=top && chk(h[q+1],h[p]))){
		if (q+1<=top && chk(h[q+1],h[q])) ++q;
		st temp=h[q];h[q]=h[p];h[p]=temp;
		p=q;q<<=1;	
	}
}
void update(int x){
	for (int i=1;i<=20;++i){
		f[x][i]=f[f[x][i-1]][i-1];
		mx[x][i]=max(mx[x][i-1],mx[f[x][i-1]][i-1]);
		sc[x][i]=min(mx[x][i-1],mx[f[x][i-1]][i-1]);
		if (mx[x][i]==sc[x][i]) sc[x][i]=-1;
		sc[x][i]=max(sc[x][i-1],sc[x][i]);
		sc[x][i]=max(sc[x][i],sc[f[x][i-1]][i-1]);
		//printf("%d %d %d %d %d\n",x,i,f[x][i],mx[x][i],sc[x][i]);
	}
}
long long mst(){
	long long res=0;
	int left=n-1;
	for (int i=0;i<=n;++i){
		f[i][0]=i;
		vis[i]=dep[i]=0;
		for (int j=0;j<=20;++j)
			mx[i][j]=sc[i][j]=-1;
		d[i]=1e9;	
	}
	vis[1]=1;d[1]=dep[1]=1;f[1][0]=0;
	for (int i=head[1];i;i=a[i].next){
		int y=a[i].to;
		d[y]=min(d[y],a[i].w);
		insert(a[i].w,a[i].to);
		f[y][0]=1;
		mx[y][0]=max(mx[y][0],a[i].w);
		dep[y]=dep[1]+1;
	}
	while (top && left){
		int x=1,k;
		while (vis[x]){
			x=h[1].u;
			k=h[1].w;
			del();	
		}
		res+=k;
		left--;
		update(x);
		vis[x]=1;
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (y==f[x][0] && a[i].w==d[x]){
				p[i]=1;
				p[i^1]=1;	
				//printf("%d %d %d\n",a[i].to,x,i);
			}
			if (!vis[y] && d[y]>a[i].w){
				f[y][0]=x;
				mx[y][0]=a[i].w;
				d[y]=a[i].w;
				dep[y]=dep[x]+1;
				insert(a[i].w,y);
			}
		}
	}
	return res;
}
int Max,Sec;
void work(int &u,int &v){
	if (dep[u]==dep[v]) return;
	for (int i=20;i>=0;--i){
		if (dep[f[u][i]]>dep[v]){
			if (Max<=mx[u][i]){
				if (Max<mx[u][i]) Sec=Max;
				Max=mx[u][i];
				Sec=max(Sec,sc[u][i]);
			}else{
				Sec=max(Sec,sc[u][i]);
				Sec=max(Sec,mx[u][i]);	
			}
			u=f[u][i];
		}
	}
	if (Max<=mx[u][0]){
		if (Max<mx[u][0]) Sec=Max;
		Max=mx[u][0];
		Sec=max(Sec,sc[u][0]);
	}else{
		Sec=max(Sec,sc[u][0]);
		Sec=max(Sec,mx[u][0]);	
	}
	u=f[u][0];
}
void solve(int u,int v){
	Max=Sec=-1;
	if (dep[u]>dep[v]) work(u,v);
	else work(v,u);
	if (u==v) return;
	for (int i=20;i>=0;--i){
		if (f[u][i]!=f[v][i]){
			int x=max(mx[u][i],mx[v][i]);
			if (Max>x)
				Sec=max(x,Sec);
			else{
				if (Max<x) Sec=Max; 
				Max=x;
				int y=min(mx[u][i],mx[v][i]);
				if (x!=y) Sec=max(Sec,y);
				Sec=max(Sec,sc[u][i]);
				Sec=max(Sec,sc[v][i]);
			}
			u=f[u][i];v=f[v][i];	
		}
	}
	int i=0;
	int x=max(mx[u][i],mx[v][i]);
	if (Max>x)
		Sec=max(x,Sec);
	else{
		if (Max<x) Sec=Max; 
		Max=x;
		int y=min(mx[u][i],mx[v][i]);
		if (x!=y) Sec=max(Sec,y);
			Sec=max(Sec,sc[u][i]);
			Sec=max(Sec,sc[v][i]);
	}
}
int main(){
	freopen("1977.in","r",stdin);
	freopen("1977.out","w",stdout);
	n=read();m=read();
	init(0,0,0);
	for (int i=1;i<=m;++i){
		int u=read(),v=read(),w=read();
		init(u,v,w);init(v,u,w);
	}
	long long len=mst(),Ans=1e15;
	/*for (int i=1;i<=n;++i)
		printf("%d ",f[i][0]);
	printf("\n");*/
	for (int i=1;i<=n;++i){
		for (int j=head[i];j;j=a[j].next)
			if (!p[j]){
				solve(i,a[j].to);
				p[j]=1;p[j^1]=1;
				long long num=len+a[j].w;
				if (num-Max!=len && Max!=-1) Ans=min(num-Max,Ans);
				if (num-Sec!=len && Sec!=-1) Ans=min(num-Sec,Ans);
			//	printf("%d %d %d %d %d\n",i,a[j].to,Max,Sec,a[j].w);
			}
	}
	printf("%lld\n",Ans);
	return 0;
}

