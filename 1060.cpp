#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define read Read<int>
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
const int N=5e5+5;
struct node{
	int next,to,w;
}a[N<<1];
int head[N],cnt=0;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
struct point{
	long long w;
	int dep,x;
}p[N];
int cmp(point x,point y){
	return x.dep>y.dep;
}
int n,s,q[N];
long long ans=0;
void dfs(int x,int fa){
	p[x].x=x;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y!=fa){
			p[y].w=a[i].w;
			p[y].dep=p[x].dep+1;
			dfs(y,x);	
		}
	}
}
void solve(){
	for (int i=1;i<=n;++i){
		int x=p[i].x,mx=0;
		for (int j=head[x];j;j=a[j].next){
			int y=a[j].to;
			if (p[q[y]].dep>p[i].dep)
				mx=mx>p[q[y]].w?mx:p[q[y]].w;
		}
		for (int j=head[x];j;j=a[j].next){
			int y=a[j].to;
			if (p[q[y]].dep>p[i].dep && p[q[y]].w<mx)
				ans+=mx-p[q[y]].w;
		}
		p[i].w+=mx;
	}
}
int main(){
	n=read();s=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		init(u,v,w);init(v,u,w);	
	}
	p[s].dep=1;p[s].w=0;
	dfs(s,0);
	sort(p+1,p+n+1,cmp);
	for (int i=1;i<=n;++i)
		q[p[i].x]=i;
	solve();
	printf("%lld\n",ans);
	return 0;
}

