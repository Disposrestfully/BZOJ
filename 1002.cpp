#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
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
struct node{
	int l,s[100010];
}a,b,c;
int n;
void print(node x){
	for (int i=x.l;i>=1;--i)
		printf("%d",x.s[i]);
	printf("\n");
}
node mult(node x,int y){
	for (int i=1;i<=x.l;++i)
		x.s[i]*=y;
	for (int i=1;i<x.l;++i)
		if (x.s[i]>=10){
			x.s[i+1]+=x.s[i]/10;
			x.s[i]%=10;
		}
	while (x.s[x.l]>=10){
		x.s[x.l+1]+=x.s[x.l]/10;
		x.s[x.l]%=10;
		++x.l;	
	}
	return x;
}
node sub(node x,node y){
	for (int i=1;i<=x.l;++i)
		x.s[i]-=y.s[i];
	for (int i=1;i<x.l;++i)
		if (x.s[i]<0){
			x.s[i]+=10;
			--x.s[i+1];	
		}
	while (x.s[x.l]<=0 && x.l>1)
		--x.l;
	return x;
}
node add(node x,int y){
	x.s[1]+=y;
	for (int i=1;i<x.l;++i)
		if (x.s[i]>=10){
			x.s[i+1]+=x.s[i]/10;
			x.s[i]%=10;
		}
	while (x.s[x.l]>=10){
		x.s[x.l+1]+=x.s[x.l]/10;
		x.s[x.l]%=10;
		++x.l;	
	}
	return x;
}
int main(){
	n=read();
	a.s[1]=1;b.s[1]=5;
	a.l=b.l=1;
	if (n==1) print(a);
	else if (n==2) print(b);
	else{
		for (int i=3;i<=n;++i){
			c=sub(mult(b,3),a);	
			c=add(c,2);
			a=b;b=c;
		}
		print(c);
	}
	return 0;
}

