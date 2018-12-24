#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
using namespace std;
typedef long long ll;
const int N=2e5+5;
int n,r,p1,p2,q[N];
struct point{
	double x,y;
	bool operator < (const point &u)const{
		return x==u.x?y<u.y:x<u.x;
	}
	point operator - (const point &u)const{
		return (point){x-u.x,y-u.y};
	}
	double operator * (const point &u)const{
		return x*u.y-y*u.x;
	}
}a[N];
double ans=0;
double mul(point x,point y,point z){
	return (x-y)*(z-y);
}	
int main(){
	scanf("%d",&n);
	for (int i=1;i<=n;++i)
		scanf("%lf%lf",&a[i].x,&a[i].y);
	sort(a+1,a+n+1);
	for (int i=1;i<=n;++i){
		while (r>1 && mul(a[q[r]],a[q[r-1]],a[i])>=0) --r;
		q[++r]=i;
	}
	int rr=r;
	for(int i=n-1;i;--i){
		while (r>rr && mul(a[q[r]],a[q[r-1]],a[i])>=0) --r;
		q[++r]=i;
    }
    for (int i=1;i<r;++i){
    	p1=i+1,p2=i+3;
    	for (int j=i+2;j<r-1;++j){
    		while (p1<j-1 && mul(a[q[j]],a[q[i]],a[q[p1]])<=mul(a[q[j]],a[q[i]],a[q[p1+1]])) ++p1;
    		while (p2<=j || (p2<r-1 && mul(a[q[p2]],a[q[i]],a[q[j]])<=mul(a[q[p2+1]],a[q[i]],a[q[j]]))) ++p2;
    		ans=max(ans,mul(a[q[j]],a[q[i]],a[q[p1]])+mul(a[q[p2]],a[q[i]],a[q[j]]));
    	}
    }
    printf("%.3lf\n",ans/2);
	return 0;
}
