#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#define pi acos(-1.0)
using namespace std;
struct circle{
    double x,y,r;
    circle(){}
    circle(double a,double b)   {x=a,y=b;}
    circle operator + (circle a)    {return circle(x+a.x,y+a.y);}
    circle operator - (circle a)    {return circle(x-a.x,y-a.y);}
    circle operator * (double a)    {return circle(x*a,y*a);}
    circle operator / (double a)    {return circle(x/a,y/a);}
}c[1010];
struct node
{
    double x;
    int v;
}p[2010];
double ans;
double dist(circle a,circle b)  {return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}
int n,tot,sum,flag;
bool cmp(node a,node b)
{
    return a.x<b.x;
}
int main()
{
    scanf("%d",&n);
    int i,j;
    for(i=1;i<=n;i++)    scanf("%lf%lf%lf",&c[i].r,&c[i].x,&c[i].y);
    for(i=1;i<=n;i++)
    {
        tot=sum=flag=0;
        for(j=i+1;j<=n;j++)
        {
            double dis=dist(c[i],c[j]);
            if(dis<=c[j].r-c[i].r)
            {
                flag=1;
                break;
            }
            if(dis>fabs(c[i].r-c[j].r)&&dis<=c[i].r+c[j].r)
            {
                double a=acos((c[i].r*c[i].r+dis*dis-c[j].r*c[j].r)/(2*c[i].r*dis));
                double b=atan2(c[j].y-c[i].y,c[j].x-c[i].x);
                p[++tot].x=b-a,p[tot].v=1,p[++tot].x=b+a,p[tot].v=-1;
                if(p[tot-1].x<0) p[tot-1].x+=2*pi;
                if(p[tot].x<0)   p[tot].x+=2*pi;
                if(p[tot-1].x>=2*pi) p[tot-1].x-=2*pi;
                if(p[tot].x>=2*pi)   p[tot].x-=2*pi;
                if(p[tot-1].x>p[tot].x)  sum++;
            }
        }
        if(flag)    continue;
        ans+=c[i].r*2*pi;
        if(!tot)    continue;
        sort(p+1,p+tot+1,cmp);
        for(j=1;j<=tot;j++)
        {
            if(sum) ans-=c[i].r*(p[j].x-p[j-1].x);
            sum+=p[j].v;
        }
        if(sum) ans-=c[i].r*(2*pi-p[tot].x);
    }
    printf("%.3lf",ans);
    return 0;
}
