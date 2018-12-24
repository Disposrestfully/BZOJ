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
const double inf=2100000000;
int a[15][15],s[15][15];
double f[15][15][15][15][15],x; 
int n,m,k;
double sqr(double x){
	return x*x;	
}
double min(double x,double y){
	return x<y?x:y;
}
double solve(int lx,int ly,int rx,int ry,int cnt){
	if (f[lx][ly][rx][ry][cnt]!=inf) return f[lx][ly][rx][ry][cnt];
	if (cnt==0){
		int sum=s[rx][ry]-s[lx-1][ry]-s[rx][ly-1]+s[lx-1][ly-1];
		f[lx][ly][rx][ry][cnt]=(sqr(sum*1.0-x))/(k*1.0); 
		return f[lx][ly][rx][ry][cnt];
	}
	double ans=inf;
	for (int i=lx;i<rx;++i)
		for (int j=0;j<=cnt-1;++j)
			ans=min(ans,solve(lx,ly,i,ry,j)+solve(i+1,ly,rx,ry,cnt-j-1));	
	for (int i=ly;i<ry;++i)
		for (int j=0;j<=cnt-1;++j)
			ans=min(ans,solve(lx,ly,rx,i,j)+solve(lx,i+1,rx,ry,cnt-j-1));
	f[lx][ly][rx][ry][cnt]=ans;
	return ans;
}
int main(){
	n=read();m=read();k=read();
	for (int i=1;i<=n;++i){
		for (int j=1;j<=m;++j){
			a[i][j]=read();
			s[i][j]=s[i-1][j]+s[i][j-1]+a[i][j]-s[i-1][j-1]; 
		}	
	}
	for (int lx=1;lx<=n;++lx)
		for (int ly=1;ly<=m;++ly)
			for (int rx=1;rx<=n;++rx)
				for (int ry=1;ry<=m;++ry)
					for (int cnt=0;cnt<=k;++cnt)
						f[lx][ly][rx][ry][cnt]=inf;
	x=(s[n][m]*1.0)/(k*1.0);
	printf("%.2lf\n",sqrt(solve(1,1,n,m,k-1)));
	return 0;
}

