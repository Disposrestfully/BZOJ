#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
using namespace std;
const double eps=1e-4;
const int N=105;
const int M=1e6+5;
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
int n,m;
double ans;
struct point{
	double x,y;
}a[N];
struct line{
	point p1,p2;
};
struct disp{
	point p;
	double d;
};
point operator - (point u,point v){
	u.x-=v.x;u.y-=v.y;
	return u;
}
double dot(point u,point v){
	return u.x*v.x+u.y*v.y;
}
double cross(point u,point v){
	return u.x*v.y-u.y*v.x;
}	
double dist(point u,point v){
	return sqrt(dot(u-v,u-v));
}
bool upon(point u,point v,point w){
	return !cross(v-u,w-u) && (u.x-v.x)*(u.x-w.x)<=0 && (u.y-v.y)*(u.y-w.y)<=0;
}
bool hav(point u,point v,point s,point t){
	return cross(v-u,s-u)*cross(v-u,t-u)<=0 && cross(t-s,u-s)*cross(t-s,v-s)<=0;
}
point getitr(point u,point s,point v,point t){
	double tmp=cross(t,u-v)/cross(s,t);
	u.x+=s.x*tmp;u.y+=s.y*tmp;
	return u;
}
disp Min(disp x,disp y){
	return (x.d<y.d)?x:y;
}
struct land{
	int tot;
	point p[N];
	void init(){
		tot=read();
		for (int i=1;i<=tot;++i){
			p[i].x=read();
			p[i].y=read();
		}
		p[tot+1]=p[1];
	}
	bool inside(point t){
		int sum=0;
		for (int i=1;i<=tot;++i)
			if (upon(t,p[i],p[i+1])) return 1;
		point s=t; 
		s.x=1e5;
		for (int i=1;i<=tot;++i)
			if (hav(s,t,p[i],p[i+1])) ++sum;
		return sum&1;
	}
}b[N];
disp near(point u,point v,point w){
	disp t;
	if (v.x==w.x && v.y==w.y) t.p=v;
	else if (dot(u-v,w-v)<=0) t.p=v;
	else if (dot(u-w,v-w)<=0) t.p=w;
	else{
		point s=v-w;
		swap(s.x,s.y);
		s.x=-s.x;
		t.p=getitr(u,s,v,w-v);
	}
	t.d=dist(t.p,u);
	return t;
}
point update(point t){
	disp tmp;
	for (int i=1;i<=m;++i)
		if (b[i].inside(t)) return t;
	tmp.d=1e20;
	for (int i=1;i<=m;++i)
		for (int j=1;j<=b[i].tot;++j)
			tmp=Min(tmp,near(t,b[i].p[j],b[i].p[j+1]));
	ans=max(ans,tmp.d);
	return tmp.p;
}
queue<line>q;
int main(){
	m=read();n=read();
	for (int i=1;i<=n;++i){
		a[i].x=read();
		a[i].y=read();
	}
	for (int i=1;i<=m;++i)
		b[i].init();
	for (int i=1;i<n;++i){
		line l;
		l.p1=a[i];l.p2=a[i+1];
		q.push(l);
		update(a[i]);
	}
	update(a[n]);
	while (!q.empty()){
		point l=q.front().p1,r=q.front().p2;
		point u=update(l),v=update(r),mid;
		while (dist(l,r)>eps){
			mid.x=(l.x+r.x)/2;
			mid.y=(l.y+r.y)/2;
			if (dist(mid,u)<dist(mid,v)) l=mid;
			else r=mid;
		}
		double tmp=dist(l,u);
		update(l);
		if (tmp>ans+eps){
			line L;
			L.p1=q.front().p1;L.p2=mid;
			q.push(L);
			L.p2=q.front().p2;L.p1=mid;
			q.push(L);
		}
		 q.pop();
	}
	printf("%.2lf\n",ans);
	return 0;
}
