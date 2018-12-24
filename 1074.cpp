#include<bits/stdc++.h>
#include<sys/mman.h>
#define y1 Y1
using namespace std;
typedef double ll;
const int N=15;
const ll eps=1e-6;
int n,m;
ll px[N],py[N],qx[N],qy[N];
inline int dcmp(ll x,ll y){
	if (fabs(x-y)<eps) return 0;
	return x<y?-1:1;
}
inline ll cross(ll x1,ll y1,ll x2,ll y2){
	return x1*y2-x2*y1;
}
inline void calc(ll x1,ll y1,ll x0,ll y0,ll &retx,ll &rety){
	retx=(x0*(x1*x0+y1*y0)+y0*(x0*y1-x1*y0))/(x0*x0+y0*y0);
	rety=(y0*(x1*x0+y1*y0)-x0*(x0*y1-x1*y0))/(x0*x0+y0*y0);
}
inline int dp(ll x,ll y,int t){
	if (!t){
		if (dcmp(x,100.0)<0 && dcmp(x,0.0)>0 && dcmp(y,100.0)<0 && dcmp(y,0.0)>0) return 1;
		return 0;
	}
	if (dcmp(cross(x-px[t],y-py[t],qx[t]-px[t],qy[t]-py[t]),0.0)>=0) return 0;
	ll retx,rety;
	calc(x-px[t],y-py[t],qx[t]-px[t],qy[t]-py[t],retx,rety);
	retx+=px[t];rety+=py[t];
	return dp(x,y,t-1)+dp(retx,rety,t-1);
}
int main(){
	freopen("1074.in","r",stdin);
	freopen("1074.out","w",stdout);
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%lf%lf%lf%lf",&px[i],&py[i],&qx[i],&qy[i]);
	scanf("%d",&m);
	while (m--){
		ll x,y;
		scanf("%lf%lf",&x,&y);
		printf("%d\n",dp(x,y,n));
	}
	return 0;
}
