#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=1005;
const double inf=1e18;
const double eps=1e-8;
int n,m;
double a[N*10][N],b[N*10],c[N],ans;
void pivot(int l,int e){
	for (int i=1;i<=n;++i)
		if (i!=e) a[l][i]/=a[l][e];
	b[l]/=a[l][e];a[l][e]=1/a[l][e];
	for (int i=1;i<=m;++i){
		if (i!=l && fabs(a[i][e])>eps){
			b[i]-=b[l]*a[i][e];
			for (int j=1;j<=n;++j)
				if (j!=e) a[i][j]-=a[i][e]*a[l][j];
			a[i][e]=-a[i][e]*a[l][e];
		}
	}
	ans+=c[e]*b[l];
	for (int i=1;i<=n;++i)
		if (i!=e) c[i]-=c[e]*a[l][i];
	c[e]=-c[e]*a[l][e];
}
double simplex(){
	while (1){
		int e=0,l;
		for (int i=1;i<=n;++i)
			if (c[e=i]>eps) break;
		if (c[e]<eps) return ans;
		double tmp=inf;
		for (int i=1;i<=m;++i)
			if (b[i]/a[i][e]<tmp && a[i][e]>eps){
				l=i;
				tmp=b[i]/a[i][e];
			}
		pivot(l,e);
	}
}
int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;++i) scanf("%lf",&c[i]);
	for (int i=1;i<=m;++i){
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);
		for (int j=x;j<=y;++j) a[i][j]=1;
		b[i]=z;
	}
	double ans=simplex();
	printf("%d\n",(int)(ans+0.5));
	return 0;
}
