#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
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
int gcd(int x,int y){
	if (!y) return x;
	return gcd(y,x%y);
}
const int N=2e4+5;
int n,rt,sum[5];
int f[N],vis[N],sz[N];
struct edge{
	int next,to,w;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
void find_root(int x,int fa,int size){
	sz[x]=1,f[x]=0;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa || vis[y]) continue;
		find_root(y,x,size);
		f[x]=max(f[x],sz[y]),sz[x]+=sz[y];
	}
	f[x]=max(f[x],size-sz[x]);
	if (!rt || f[x]<f[rt]) rt=x;
}
void dfs(int x,int fa,int dep){
	++sum[dep];
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa || vis[y]) continue;
		dfs(y,x,(dep+a[i].w)%3);
	}
}
inline int calc(int x,int d){
	memset(sum,0,sizeof(sum));
	dfs(x,0,d%3);
	return (sum[1]*sum[2])*2+sum[0]*sum[0];
}
inline int solve(int x){
	vis[x]=1;
	int res=calc(x,0);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (vis[y]) continue;
		res-=calc(y,a[i].w);
		rt=0;
		find_root(y,0,sz[y]);
		res+=solve(rt);
	}
	return res;
}
int main(){
	freopen("2152.in","r",stdin);
	freopen("2152.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
	}	
	rt=0;
	find_root(1,0,n);
	int ans=solve(rt),d=gcd(ans,n*n);
	printf("%d/%d\n",ans/d,n*n/d);
	return 0;
}
