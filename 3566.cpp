#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=5e5+5;
int n;
double ans;
double f[N],g[N];
struct edge{
	int next,to;
	double w;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v,double w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
void dfs1(int x,int fa){
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dfs1(y,x);
		f[x]*=(f[y]+((1.0-f[y])*(1.0-a[i].w)));
	}
}
void dfs2(int x,int fa,double las){
	if (fa){
		double t=g[fa]*f[fa]/(f[x]+((1.0-f[x])*(1.0-las)));
		g[x]=t+(1.0-t)*(1.0-las);
	}
	ans+=1.0-f[x]*g[x];
	//printf("%.6lf %.6lf\n",f[x],g[x]);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dfs2(y,x,a[i].w);
	}
}
int main(){
	freopen("3566.in","r",stdin);
	freopen("3566.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		double w=(double)read()/100.0;
		add(u,v,w),add(v,u,w);
	}
	for (int i=1;i<=n;++i)
		f[i]=(double)(100-read())/100.0;
	dfs1(1,0),g[1]=1,dfs2(1,0,0);
	printf("%.6lf\n",ans);
	return 0;
}
