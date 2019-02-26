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
const int N=1e6+5;
ll n,ans;
ll sz[N],f[N],dep[N];
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
void dfs_init(int x,int fa){
	sz[x]=1,dep[x]=dep[fa]+1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dfs_init(y,x),sz[x]+=sz[y];
	}
}
void dfs(int x,int fa){
	if (fa) f[x]=f[fa]+n-(sz[x]<<1);
	else{
		for (int i=1;i<=n;++i)
			f[x]+=dep[i];	
	}
	ans=max(ans,f[x]);
	for (int i=head[x];i;i=a[i].next)
		if (a[i].to!=fa) dfs(a[i].to,x);
}
int main(){
	freopen("1131.in","r",stdin);
	freopen("1131.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs_init(1,0),dfs(1,0);
	for (int i=1;i<=n;++i)
		if (f[i]==ans){
			printf("%d\n",i);
			return 0;
		}
	return 0;
}
