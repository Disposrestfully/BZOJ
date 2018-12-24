#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<vector>
#include<map>
typedef long long ll;
using namespace std;
const int N=1e5+5;
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
	int sum,mx;
}a[N<<2];
struct edge{
	int next,to;
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int n,q;
int sz[N],dep[N],fa[N];
int son[N],top[N],w[N];
int dfn[N],rk[N],tot;
void dfs1(int x){
	sz[x]=1;
	son[x]=0;
	dep[x]=dep[fa[x]]+1; 
	for (int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if (y==fa[x]) continue;
		fa[y]=x;
		dfs1(y);
		sz[x]+=sz[y];
		if (sz[y]>sz[son[x]]) son[x]=y;
	}	
}
void dfs2(int x){
	dfn[++tot]=x;
	rk[x]=tot;
	if (son[x]){
		top[son[x]]=top[x];
		dfs2(son[x]);
	}else return;
	for (int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if (y==fa[x] || y==son[x]) continue;
		top[y]=y;
		dfs2(y);
	}
}
void pushup(int x){
	a[x].sum=a[x<<1].sum+a[(x<<1)+1].sum;
	a[x].mx=max(a[x<<1].mx,a[(x<<1)+1].mx);
}
void build(int x,int l,int r){
	if (l==r){
		a[x].sum=w[l];
		a[x].mx=w[l];
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build((x<<1)+1,mid+1,r);
	pushup(x);
}
int query_sum(int x,int l,int r,int L,int R){
	if (L<=l && r<=R)
		return a[x].sum;
	int mid=(l+r)>>1;
	int res=0;
	if (L<=mid) res+=query_sum(x<<1,l,mid,L,R);
	if (R>mid) res+=query_sum((x<<1)+1,mid+1,r,L,R);
	return res; 	
}
int query_max(int x,int l,int r,int L,int R){
	if (L<=l && r<=R)
		return a[x].mx;
	int mid=(l+r)>>1;
	int res=-1e9;
	if (L<=mid) res=max(res,query_max(x<<1,l,mid,L,R));
	if (R>mid) res=max(res,query_max((x<<1)+1,mid+1,r,L,R));
	return res; 	
}
int solve_sum(int u,int v){
	int res=0;
	while (top[u]!=top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		res+=query_sum(1,1,n,rk[top[u]],rk[u]);
		u=fa[top[u]];
	}
	if (rk[u]>rk[v]) swap(u,v);
	res+=query_sum(1,1,n,rk[u],rk[v]);
	return res;
}
int solve_max(int u,int v){
	int res=-1e9;
	while (top[u]!=top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		res=max(res,query_max(1,1,n,rk[top[u]],rk[u]));
		u=fa[top[u]];
	}
	if (rk[u]>rk[v]) swap(u,v);
	res=max(res,query_max(1,1,n,rk[u],rk[v]));
	return res;
}
void update(int x,int l,int r,int pos){
	if (l==r){
		a[x].sum=w[l];
		a[x].mx=w[l];
		return;
	}
	int mid=(l+r)>>1;
	if (pos<=mid) update(x<<1,l,mid,pos);
	else update((x<<1)+1,mid+1,r,pos);
	pushup(x);
}
int main(){
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v);add(v,u);	
	}
	dfs1(1);
	top[1]=1;
	dfs2(1);
	for (int i=1;i<=n;++i)
		w[rk[i]]=read();
	build(1,1,n);
	q=read();
	while (q--){
		char ch=0;
		while (ch!='C' && ch!='U' & ch!='X') ch=getchar();
		if (ch=='C'){
			int u=read(),k=read();
			w[rk[u]]=k;
			update(1,1,n,rk[u]);	
		}else if (ch=='U'){
			int u=read(),v=read();
			printf("%d\n",solve_sum(u,v));
		}else{
			int u=read(),v=read();
			printf("%d\n",solve_max(u,v));
		}
	}
	return 0;
}

