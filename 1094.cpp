#include<bits/stdc++.h>
#define N 105
using namespace std;
int n,m,k;double t1,t2,r,c[N][N];
struct point{
    double x,y;
    point operator + (const point &b)const{return (point){x+b.x,y+b.y};}
    point operator * (const double &b)const{return (point){x*b,y*b};}
    point operator - (const point &b)const{return (point){x-b.x,y-b.y};}
}o;
struct line{point p,v;}a[N][N];
double dot(point a,point b){return a.x*b.x+a.y*b.y;}
double crs(point a,point b){return a.x*b.y-a.y*b.x;}
double solve(int i,int j,int p1,int p2){
    point v1=a[i][p1].v-a[j][p2].v,v2=(a[i][p1].p-a[i][p1].v*c[i][p1])-(a[j][p2].p-a[j][p2].v*c[j][p2]);
    double u=dot(v1,v1),v=2*dot(v1,v2),w=dot(v2,v2),t;
    if(!u){
        if(v>0)t=t1;else t=t2;
        return sqrt(w+t*v);
    }
    else{
        t=-v/(2*u);
        if(t<t1)t=t1;if(t>t2)t=t2;
        return sqrt(t*t*u+v*t+w);
    }
}
int main(){
    scanf("%lf%lf%lf",&o.x,&o.y,&r);
    scanf("%d%d",&n,&m);
    double u,v,w,t;point p,q,nm;
    for(int i=1;i<=n;i++){
        scanf("%lf%lf%lf%lf",&a[i][0].p.x,&a[i][0].p.y,&a[i][0].v.x,&a[i][0].v.y);
        for(int j=1;j<=m;j++){
            p=a[i][j-1].p-o;q=a[i][j-1].v;
            u=dot(q,q);v=dot(p,q)*2;w=dot(p,p)-r*r;
            t=(sqrt(v*v-4*u*w)-v)/2/u;
            c[i][j]=c[i][j-1]+t;
            a[i][j].p=a[i][j-1].p+a[i][j-1].v*t;
            nm=a[i][j].p-o;swap(nm.x,nm.y);nm.x=-nm.x;
            a[i][j].v=nm*(dot(nm,a[i][j-1].v)/dot(nm,nm)*2)-a[i][j-1].v;
            line tmp=a[i][j];
      //      printf("%.2lf %.2lf %.2lf %.2lf\n",tmp.p.x,tmp.p.y,tmp.v.x,tmp.v.y);
        }
    }
    double ans=1e10;int p1,p2;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++){
            p1=p2=0;
            while(p1<m&&p2<m){
                t1=max(c[i][p1],c[j][p2]);
                t2=min(c[i][p1+1],c[j][p2+1]);
                ans=min(ans,solve(i,j,p1,p2));
                if(c[i][p1+1]<c[j][p2+1])p1++;
                else p2++;
            }
        }
    printf("%.3lf\n",ans);
    return 0;
}
