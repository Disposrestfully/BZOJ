#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
namespace pb_ds{   
    namespace io{
        const int MaxBuff=1<<15;
        const int Output=1<<23;
        char B[MaxBuff],*S=B,*T=B;
		#define getc() ((S==T)&&(T=(S=B)+fread(B,1,MaxBuff,stdin),S==T)?0:*S++)
        char Out[Output],*iter=Out;
        inline void flush(){
            fwrite(Out,1,iter-Out,stdout);
            iter=Out;
        }
    }
    template<class Type> inline Type Read(){
        using namespace io;
        register char ch;
        register Type ans=0; 
        register bool neg=0;
        while(ch=getc(),(ch<'0' || ch>'9') && ch!='-');
        ch=='-'?neg=1:ans=ch-'0';
        while(ch=getc(),'0'<= ch && ch<='9') ans=ans*10+ch-'0';
        return neg?-ans:ans;
    }
    template<class Type> inline void Print(register Type x,register char ch='\n'){
        using namespace io;
        if(!x) *iter++='0';
        else{
            if(x<0) *iter++='-',x=-x;
            static int s[100]; 
            register int t=0;
            while(x) s[++t]=x%10,x/=10;
            while(t) *iter++='0'+s[t--];
        }
        *iter++=ch;
    }
}
using namespace pb_ds;
int s[10][10],q[10][10];
int dx[4]={0,1,0,-1},dy[4]={1,0,-1,0};
int flag,tot,sur,now;
struct ant{
	int x,y,flag,time;
	int l,lf,px,py,lev,alive;
}a[10];
int cmp(ant u,ant v){
	return u.time>v.time;	
}
struct point{
	int x,y;
};
struct line{
	point a,b;
}l;
struct tower{
	int x,y;
}p[30];
int n,m,t,d,r,cnt,end;
int chs[5];
int mult(point u,point v){
	return u.x*v.y-u.y*v.x;	
}
point sub(point u,point v){
	point p;
	p.x=u.x-v.x;
	p.y=u.y-v.y;
	return p;	
}
int calc(point a,point b,point c){
	return mult(sub(b,a),sub(c,a));
}
int ok(int x,int y,int px,int py){
	if (x>n || x<0 || y<0 || y>m || q[x][y]) return 0;
	if (x==px && y==py) return 0;
	return 1;	
}
int move(int x){
	int mx=-0x7fffffff;
	for (int i=0;i<4;++i){
		int lx=a[x].x+dx[i],ly=a[x].y+dy[i];
		if (ok(lx,ly,a[x].px,a[x].py) && mx<s[lx][ly])
			mx=s[lx][ly];
	}
	int res=-1;
	for (int i=0;i<4;++i){
		int lx=a[x].x+dx[i],ly=a[x].y+dy[i];
		if (ok(lx,ly,a[x].px,a[x].py) && mx==s[lx][ly]){
			res=i;
			break;	
		}
	}
	if (res==-1 || (a[x].time+1)%5!=0)
		return res;
	for (int i=(res+3)%4;;i=(i+3)%4){
		int lx=a[x].x+dx[i],ly=a[x].y+dy[i];
		if (ok(lx,ly,a[x].px,a[x].py)) return i;
	}
}
int dist(int sx,int sy,int tx,int ty){
	return (sx-tx)*(sx-tx)+(sy-ty)*(sy-ty);	
}
int goal(int x){	
	int pos=-1,mn=0x7fffffff;
	for (int i=1;i<=6;++i){
		if (a[i].alive){
			int d=dist(a[i].x,a[i].y,p[x].x,p[x].y);
			if (d<=r*r){
				if (a[i].flag && flag){
					return i;	
				}else if (!a[i].flag && mn>d){
					mn=d;
					pos=i;
				}
			}
		}
	}
	return pos;
}
int point_line(int x,int y){
	double d=sqrt(dist(l.a.x,l.a.y,l.b.x,l.b.y));
	point p;p.x=x;p.y=y;
	//printf("%d %d %d\n",p.x,p.y,now);
	if ((x==l.a.x && y==l.a.y) || (x==l.b.x && y==l.b.y)) return 1;
	int maxx=l.a.x>l.b.x?l.a.x:l.b.x,minx=l.a.x<l.b.x?l.a.x:l.b.x;
	int maxy=l.a.y>l.b.y?l.a.y:l.b.y,miny=l.a.y<l.b.y?l.a.y:l.b.y;
	if (x>maxx || x<minx || y>maxy || y<miny) return 0;
	if (fabs(calc(l.a,l.b,p))/d<=0.5) return 1;
	return 0;
}
int main(){
	//freopen("ant.in","r",stdin);
//	freopen("ant.out","w",stdout);
	n=read();m=read();
	cnt=read();d=read();r=read();
/*	for (int i=1;i<=6;++i){
		a[i].time=-1;
		a[i].alive=0;	
	}*/
	for (int i=1;i<=cnt;++i){
		p[i].x=read();p[i].y=read();	
		q[p[i].x][p[i].y]=1;
	}
	t=read();
	now=0;
	while (now<t){
		now++;
		if (sur<6 && !q[0][0]){
			tot++;sur++;
			for (int i=1;i<=6;++i){
				if (!a[i].alive){
					a[i].time=0;
					a[i].x=a[i].y=0;
					a[i].flag=0;
					a[i].alive=1;
					a[i].px=a[i].py=0;
					a[i].lev=(tot-1)/6+1;
					double c=4.0;
					for (int j=1;j<=a[i].lev;++j)
						c*=1.1;
					a[i].lf=a[i].l=int(c);
					q[0][0]=1;                                                                                                                                                                                                                                                                           
					break;
				}
			}
		}
		sort(a+1,a+7,cmp);
		/*for (int i=1;i<=6;++i)
			printf("%d %d %d %d %d %d %d\n",a[i].time,a[i].lev,a[i].lf,a[i].x,a[i].y,a[i].flag,now);
		printf("\n");*/
		for (int i=1;i<=6;++i)
			if (a[i].alive){
				if (a[i].flag) s[a[i].x][a[i].y]+=5;
				else s[a[i].x][a[i].y]+=2;
			}
		for (int i=1;i<=6;++i){
			if (a[i].alive){
				int dir=move(i);
				a[i].px=a[i].x;
				a[i].py=a[i].y;
				if (dir!=-1){
					//printf("%d %d %d %d\n",a[i].time,i,dir,now);
					q[a[i].x][a[i].y]=0;
					a[i].x+=dx[dir];
					a[i].y+=dy[dir];
					q[a[i].x][a[i].y]=1;
				}
			}
		}
		//printf("\n");
		if (!flag){
			for (int i=1;i<=6;++i)
				if (a[i].x==n && a[i].y==m && a[i].alive){
					flag=1;
					a[i].flag=1;
					a[i].lf+=a[i].l/2;
					if (a[i].lf>a[i].l) a[i].lf=a[i].l;
					break;
				}
		}
		for (int i=1;i<=cnt;++i){
			int tar=goal(i);
			if (tar==-1) continue;
			//printf("%d %d %d\n",i,tar,now);
			l.a.x=p[i].x;l.a.y=p[i].y;
			l.b.x=a[tar].x;l.b.y=a[tar].y;
		//	printf("%d %d %d %d %d\n",l.a.x,l.a.y,l.b.x,l.b.y,now);
			for (int j=1;j<=6;++j){
				if (a[j].alive)
					if (point_line(a[j].x,a[j].y)){
						a[j].lf-=d;
						//printf("%d ",j);
					}
			}
		//	printf("\n");
		}
		for (int i=1;i<=6;++i){
			if (a[i].alive && a[i].lf<0){
			//	printf("%d %d\n",i,now);
				a[i].alive=0;
				q[a[i].x][a[i].y]=0;
				sur--;
				if (a[i].flag)
					flag=a[i].flag=0;
			}
		}
		if (flag){
			for (int i=1;i<=6;++i)
				if (a[i].x==0 && a[i].y==0 && a[i].flag==1 && a[i].alive){
					end=1;
					break;
				}
		}
		if (end) break;
		for (int i=0;i<=n;++i)
			for (int j=0;j<=m;++j)
				if (s[i][j]>0)
					s[i][j]--;
		for (int i=1;i<=6;++i)
			if (a[i].alive)
				a[i].time++;
	}
	if (end) printf("Game over after %d seconds\n",now);
	else printf("The game is going on\n");
	printf("%d\n",sur);
	sort(a+1,a+7,cmp);
	for (int i=1;i<=6;++i)
		if (a[i].alive)
			printf("%d %d %d %d %d\n",a[i].time,a[i].lev,a[i].lf,a[i].x,a[i].y);
	return 0;
}

