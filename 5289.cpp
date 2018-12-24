#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e6+5;
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
int n,flag,tot;
int w[N],fa[N];
struct node{
	int sz,x;
	ll w;
	inline bool operator < (const node &u)const{
		if (w*u.sz!=u.w*sz) return w*u.sz<u.w*sz;
		return x<u.x;
	}
}s[N<<1];
int f[N],p[N<<1];
int find(int x){
	if (f[x]==x) return x;
	return f[x]=find(f[x]);
}
ll ans;
set<node>q;
int main(){
	//freopen("5289.in","r",stdin);
	//freopen("5289.out","w",stdout);
	tot=n=read();
	for (int i=1;i<=n;++i) f[i]=i;
	for (int i=1;i<=n;++i){
		int x=read();
		fa[i]=x;
		int fx=find(x),fy=find(i);
		if (fx==fy) flag=1;
		f[fx]=fy;	
	}
	for (int i=1;i<=n;++i) ans+=(w[i]=read());
	if (flag){
		puts("-1");
		return 0;
	}
	for (int i=1;i<=n;++i)
		f[i]=i,s[i]=(node){1,i,(ll)w[i]},q.insert(s[i]);
	f[0]=0;
	while (!q.empty()){
		node x=*q.begin();
		q.erase(x);
		int y=find(fa[x.x]);
		ans+=x.w*s[y].sz;
		if (y){
			q.erase(s[y]);
			node now=x;
			now.x=++tot;
			now.w+=s[y].w;
			now.sz+=s[y].sz;
			q.insert(s[tot]=now);
			f[find(x.x)]=f[y]=f[tot]=tot;
			fa[fa[x.x]=tot]=fa[y];
		}else f[find(x.x)]=0,s[0].sz+=x.sz;
	}
	printf("%lld\n",ans);
	return 0;
}
