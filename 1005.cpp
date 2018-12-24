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
	int p[1010];
}a[1010],s[1010];
int n,sum,d[1010];
int ans[100010],l,cnt;
node sub(node x,node y){
	for (int i=1;i<=n;++i)
		x.p[i]-=y.p[i];
	return x;	
} 
node add(node x,node y){
	for (int i=1;i<=n;++i)
		x.p[i]+=y.p[i];
	return x;	
} 
void init(int x){
	if (x<=1) return;
	int pr=2,k=x;	
	while (x!=1){
		while (x%pr==0){
			++a[k].p[pr];
			x/=pr;
		}
		++pr;
	}
}
void mult(int x){
	for (int i=1;i<=l;++i)
		ans[i]*=x;
	for (int i=1;i<l;++i)
		if (ans[i]>=10){
			ans[i+1]+=ans[i]/10;
			ans[i]%=10;	
		}
	while (ans[l]>=10){
		ans[l+1]+=ans[l]/10;
		ans[l]%=10;
		++l;	
	}
} 
int main(){
	n=read();
	int flag=0;
	for (int i=1;i<=n;++i)
		s[0].p[i]=a[0].p[i]=0;
	for (int i=1;i<=n;++i){
		d[i]=read()-1;
		if (d[i]+1>=n || d[i]+1==0)
			flag=1;
		if (d[i]>=0){
			sum+=d[i];
			cnt++;
		}
		init(i);	
		s[i]=add(s[i-1],a[i]);
	}
	if (n==1){
		if (d[1]<0) printf("1\n");
		else printf("0\n");
		return 0;	
	}
	if (n==2){
		if (d[1]>0 || d[2]>0 || d[1]==-1 || d[2]==-1) printf("0\n");	
		else printf("1\n");
		return 0;
	} 
	if (flag || sum>n-2){
		printf("0\n");
		return 0;	
	}
	node x=sub(s[n-2],s[n-2-sum]); 
	for (int i=1;i<=n;++i)
		if (d[i]>0)
			x=sub(x,s[d[i]]);
	for (int i=1;i<=n;++i)
		x.p[i]+=a[n-cnt].p[i]*(n-2-sum);	
	l=ans[1]=1;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=x.p[i];++j)
			mult(i);
	for (int i=l;i>=1;--i)
		printf("%d",ans[i]);
	printf("\n");
	return 0;
}

