#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=1e5+5;
const double esp=1e-14;
double a[N],s[N],k;
int n,m;
int main(){
	scanf("%d%lf",&n,&k);
	for (int i=1;i<=n;++i){
		scanf("%lf",&a[i]);
		s[i]=s[i-1]+a[i];	
	}
	int m=min(n,1000);
	for (int i=1;i<=m;++i){
		int x=(int)(k*i+esp);
		double ans=0;
		for (int j=1;j<=x;++j)
			ans+=(a[i]*a[j])/(i-j);
		printf("%.6lf\n",ans);
	}
	for (int i=m+1;i<=n;++i){
		int x=(int)(k*i+esp);
		double y=i-(k*i)/2;
		printf("%.6lf\n",(s[x]*a[i])/y);
	}
	return 0;
}

