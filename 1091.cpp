#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef double ll;
const int N=1e5+5;
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
int n,m,tot,ls,id[15];
struct point{
	ll x,y;
	point operator - (point u){
		return (point){x-u.x,y-u.y};
	}
	point operator * (double u){
		return (point){x*u,y*u};
	}
	ll operator * (point u){
		return x*u.y-y*u.x;
	}
	ll abs(){
		return sqrt(x*x+y*y);
	}
}p[15],p1,p2,p3,p4;
ll mx,mn,ans=1e10;
struct line{
	point a,b;
	void chk(line w){
		ll c=w.b*b;
		if (c==0) return;
		c=(a*w.b+w.b*w.a)/c;
		if (c>0.5) c<mx&&(mx=c); 
		else c>mn&&(mn=c); 
	}
}l[15],l0[15];
int main(){
	//freopen("1.in","r",stdin);
	n=read();m=read();tot=read();
	p1=(point){0,0};p2=(point){n,0};
	p3=(point){n,m};p4=(point){0,m};
	l[ls++]=(line){p1,p2-p1};
	l[ls++]=(line){p2,p3-p2};
	l[ls++]=(line){p3,p4-p3};
	l[ls++]=(line){p4,p1-p4};
	for (int i=1;i<=tot;++i){
		p[i].x=read();p[i].y=read();
		id[i]=i;
	}
	p[tot+1]=p[1];
	for (int i=1;i<=tot;++i)
		l0[i]=(line){p[i],p[i+1]-p[i]};
	do{
		ls=4;
		ll s=0;
		for (int i=1;i<=tot;++i){
			int w=id[i];
			mn=-1e10;mx=1e10;
			for (int j=0;j<ls;++j) l0[w].chk(l[j]);
			l[ls++]=l0[w];
			s+=(mx-mn)*l0[w].b.abs();
		}
		if (s<ans) ans=s;
	}while (std::next_permutation(id+1,id+tot+1));
	printf("%.3lf\n",ans);
	return 0;
}
