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
int a[10010],s[10010];
int q[10010];
int n,m,top=0;
struct node{
	int id,w,s;
}f[10010];
int cmp(node x,node y){
	if (x.s<y.s || (x.s==y.s && x.id<y.id)) return 1;
	return 0;
}
void add(int x,int y){
	if (y<q[top]){
		q[++top]=y;
		f[x].w=top;
		return;
	}
	if (y>q[1]){
		q[1]=y;
		f[x].w=1;
		return;
	}	
	int l=1,r=top;
	while (l<=r){
		int mid=(l+r)>>1;	
		if (q[mid]<=y) r=mid-1;
		else l=mid+1;
	}
	q[r+1]=y;
	f[x].w=r+1;
}
int main(){
//	freopen("lis.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i)
		a[i]=s[n-i+1]=read();
	q[0]=1e9;
	for (int i=1;i<=n;++i){
		f[n-i+1].id=n-i+1;
		f[n-i+1].s=s[i];
		add(n-i+1,s[i]);
	}
	m=read();
	while (m--){
		int l=read();
		if (l>top){
			printf("Impossible\n");
			continue;
		}
		int now=0,t=0;
		for (int i=1;i<=n;++i){
			if (f[i].id>now && f[i].s>t && f[i].w>=l){
				l--;
				now=f[i].id;
				t=f[i].s;
				printf("%d",f[i].s);	
				if (l!=0) printf(" ");
				else break;
			}
		}
		printf("\n"); 
	}
	return 0;
}

