#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=5e5+5;
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
struct node{
	int u,v,c1,c2,f,id;
}a[N];
bool cmp1(node x,node y){
	if (x.c1==y.c1) return x.c2>y.c2;
	return x.c1<y.c1;
}
bool cmp2(node x,node y){
	return x.c2<y.c2;
}
bool cmp3(node x,node y){
	return x.id<y.id;
}
int n,m,k;
int f[N],ans=0;
int find(int x){
	if (x==f[x]) return f[x];
	return f[x]=find(f[x]);
}
int main(){
	n=read();k=read();m=read();
	for (int i=1;i<m;++i){
		a[i].u=read();a[i].v=read();
		a[i].c1=read();a[i].c2=read();
		a[i].f=0;a[i].id=i;
	}
	for (int i=1;i<=n;++i) f[i]=i;
	sort(a+1,a+m,cmp1);
	for (int i=1;i<m;++i){
		if (!k) break;
		int fx=find(a[i].u),fy=find(a[i].v);
		if (fx!=fy){
			a[i].f=1;
			f[fx]=fy;
			--k;
			ans=max(ans,a[i].c1);
		}
	}
	sort(a+1,a+m,cmp2);
	for (int i=1;i<m;++i){
		int fx=find(a[i].u),fy=find(a[i].v);
		if (fx!=fy){
			ans=max(ans,a[i].c2);
			f[fx]=fy;
			a[i].f=2;
		}
	}
	sort(a+1,a+m,cmp3);
	printf("%d\n",ans);
	return 0;
}
