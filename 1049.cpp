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
const long long INF=2100000000000000000;
const int inf=2100000000;
int a[35010],f[35010];
int q[35010],top,n; 
struct node{
	int next,to;
}s[100010];
int head[35010],cnt;
long long s1[35010],s2[35010],dp[35010];
void add(int x,int y){
	if (x>=q[top]){
		q[++top]=x;
		f[y]=top;
		return;	
	}
	int l=1,r=top;
	while (l<=r){
		int mid=(l+r)>>1;	
		if (q[mid]<=x) l=mid+1;
		else r=mid-1;
	}
	q[l]=x;f[y]=l;
}	
void init(int u,int v){
	s[++cnt].to=v;
	s[cnt].next=head[u];
	head[u]=cnt;
}
int Abs(int x){
	return x>0?x:(-x);	
}
long long min(long long x,long long y){
	return x<y?x:y; 
} 
int main(){
	//freopen("seq.in","r",stdin);
	n=read();q[0]=-inf;
	for (int i=1;i<=n;++i)
		a[i]=read()-i;	
	a[++n]=inf;q[0]=-inf;
	for (int i=1;i<=n;++i)
		add(a[i],i);
	printf("%d\n",n-top);
	for (int i=n;i>=0;--i){
		init(f[i],i);
		dp[i]=INF;	
	}
	dp[0]=0;a[0]=-inf;
	for (int i=1;i<=n;++i){
		for (int j=head[f[i]-1];j;j=s[j].next){
			int now=s[j].to;
			if (now>i) break;
			if (a[now]>a[i]) continue;
			s1[now-1]=s2[now-1]=0;
			for (int k=now;k<=i;++k){
				s1[k]=s1[k-1]+Abs(a[k]-a[now]);
				s2[k]=s2[k-1]+Abs(a[k]-a[i]);
			}
			for (int k=now;k<=i;++k)
				dp[i]=min(dp[i],dp[now]+s1[k]-s1[now]+s2[i]-s2[k]);
		}
	}
	printf("%lld\n",dp[n]);
	return 0;
}

