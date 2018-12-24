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
const double esp=1e-14;
struct node{
	double k,b;
	int id;
}a[50010];
int cmp(node x,node y){
	if (x.k==y.k) return x.b>y.b;
	return x.k<y.k;
}
node q[50010];
int n,top,p[50010];
double point(node x,node y){
	return (y.b-x.b)/(x.k-y.k);	
}
int main(){
	n=read();
	for (int i=1;i<=n;++i){
		scanf("%lf%lf",&a[i].k,&a[i].b);
		a[i].id=i;	
	}
	sort(a+1,a+n+1,cmp);
	q[1]=a[1];top=1;
	for (int i=2;i<=n;++i){	
		if (a[i].k-q[top].k<=esp) continue;
		while (top>1 && point(q[top],a[i])<=point(q[top],q[top-1])) --top;
		q[++top]=a[i];
	}
	for (int i=1;i<=top;++i)
		p[q[i].id]=1;
	for (int i=1;i<=n;++i)
		if (p[i])
			printf("%d ",i);
	printf("\n");
	return 0;
}

