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
const int Mod=31011;
struct node{
	int u,v,w;
}a[1010];
struct rng{
	int l,r;
}s[1010];
int p[1010];
int cmp(node x,node y){
	return x.w<y.w;	
}
int f[110],n,m,ed;
void clean(){
	for (int i=1;i<=n;++i)
		f[i]=i;
} 
int find1(int x){
	if (f[x]==x) return x;
	return f[x]=find1(f[x]);
}
int find2(int x){
	if (f[x]==x) return x;
	return find2(f[x]);	
}
int cnt;
void mst(){
	clean();
	cnt=1;
	int l=1;
	for (int i=1;i<=m;++i){
		if (a[i].w!=a[i-1].w && i!=1){
			s[cnt].l=l;
			s[cnt].r=i-1;
			l=i;++cnt;
		}
		int fx=find1(a[i].u),fy=find1(a[i].v);
		if (fx!=fy){
			f[fx]=fy;
			++p[cnt];
			++ed;
		}
	}
	s[cnt].l=l;
	s[cnt].r=m;
}
int sum,ans=1;
void dfs(int x,int now,int c){
	//printf("%d %d %d\n",x,now,c);
/*	for (int i=1;i<=n;++i)	
		printf("%d ",f[i]);
	printf("\n");*/
	if (x>s[c].r){
		sum+=(now==p[c]);
		sum%=Mod;
		return;	
	}
	int fx=find2(a[x].u),fy=find2(a[x].v);
	//printf("%d %d %d %d\n",a[x].u,a[x].v,fx,fy);
	if (fx!=fy){
		f[fx]=fy;
		dfs(x+1,now+1,c);
		f[fx]=fx;f[fy]=fy;
	}
	dfs(x+1,now,c);
}
int main(){
//	freopen("award.in","r",stdin);
//	freopen("award.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=m;++i){
		a[i].u=read();
		a[i].v=read();
		a[i].w=read();	
	}
	sort(a+1,a+m+1,cmp);
	mst();
	if (ed!=n-1){
		printf("0\n");
		return 0;	
	}
	clean();
	for (int i=1;i<=cnt;++i){
		sum=0;
		if (p[i]!=0){
			dfs(s[i].l,0,i);
			ans=(ans*sum)%Mod;	
			for (int j=s[i].l;j<=s[i].r;++j){
				int fx=find2(a[j].u),fy=find2(a[j].v);
				if (fx!=fy)
					f[fx]=fy;	
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}

