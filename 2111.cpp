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
int n,p,l,r,tot;
int f[1000010];
int c[1000010],rev[1000010];
int mult(int x,int y){
	x%=p;y%=p;
	return (int)((long long)x*(long long)y%(long long)p);
}
int add(int x,int y){
	x%=p;y%=p;
	return ((x+y)%p+p)%p;
}
int Pow(int x,int y){
	int res=1;
	while (y){
		if (y&1) res=mult(res,x);	
		x=mult(x,x);
		y>>=1;
	}
	return res;
}
int C(int x,int y){
	if (y>x) return 0;
	return mult(c[x],mult(rev[y],rev[x-y]));	
}
int lucas(int x,int y){
	if (y==0) return 1;
	return mult(lucas(x/p,y/p),C(x%p,y%p));	
}
int main(){
	freopen("2111.in","r",stdin);
	freopen("2111.out","w",stdout);
	n=read();p=read();
	c[0]=rev[0]=1;
	for (int i=1;i<=n;++i){
		c[i]=mult(c[i-1],i);
		rev[i]=Pow(c[i],p-2);	
	}
	f[0]=f[1]=1;
	tot=2;l=r=0;
	for (int i=2;i<=n;++i){
		if (l==r) tot*=2;
		if (l*2<tot-2) l++;
		else r++;
		int k;
		if (n>p) k=lucas(i-1,l);
		else k=C(i-1,l);
		f[i]=mult(k,mult(f[l],f[r]));	
	}
	printf("%d\n",f[n]);
	return 0;
}

