#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=505;
int read(){
	long long x=0,w=1;
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
	double x,y;
}a[N],b[N];
int n,m;
int map[N][N],inf;
node sub(node u,node v){
	node res;
	res.x=u.x-v.x;
	res.y=u.y-v.y;
	return res;	
}
double mult(node u,node v){
	return (u.x*v.y)-(u.y*v.x);
}
double dmult(node u,node v){
	return (u.x*v.x)+(u.y*v.y);
}
int floyd(){
	for (int k=1;k<=n;++k)
		for (int i=1;i<=n;++i)
			if (map[i][k]<inf)
				for (int j=1;j<=n;++j)
					map[i][j]=min(map[i][j],map[i][k]+map[k][j]);
	int ans=inf;
	for (int i=1;i<=n;++i)
		ans=min(ans,map[i][i]);
	return ans;
}
int main(){
	n=read();m=read();
	for (int i=1;i<=n;++i){
		double t;
		scanf("%lf%lf%lf",&a[i].x,&a[i].y,&t);	
	}
	for (int i=1;i<=m;++i){
		double t;
		scanf("%lf%lf%lf",&b[i].x,&b[i].y,&t);	
	}
	memset(map,127,sizeof(map));
	inf=map[1][1];
	for (int i=1;i<=n;++i){
		for (int j=1;j<=n;++j){
			int flag=1;
			for (int k=1;k<=m;++k){
				double c1=mult(sub(a[i],b[k]),sub(a[j],b[k]));
				double c2=dmult(sub(a[i],b[k]),sub(a[j],b[k]));
				if (c1>1e-14 || (fabs(c1)<1e-14 && c2>1e-14)){
					flag=0;
					break;	
				}
			}
			if (flag) map[i][j]=1;
		}
	}
	int ans=floyd();
	if (ans==inf) ans=-1;
	printf("%d\n",ans);
	return 0;
}

