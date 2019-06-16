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
const int N=1e5+5;
struct edge{
	int next,to;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int n,m,tot;
int anc[N][20],dep[N];
int dfn[N],sz[N],p[N];
int s[N];
inline bool chk(int u,int v){
	return (dfn[u]<=dfn[v] && dfn[v]<=dfn[u]+sz[u]-1);
}
inline void get_fa(int x,int fa){
	anc[x][0]=fa;
	for (int i=1;i<=19;++i)
		anc[x][i]=anc[anc[x][i-1]][i-1];
	dep[x]=dep[fa]+1;
}
inline int find(int x,int fa){
	for (int i=19;~i;--i)
		if (dep[anc[x][i]]>dep[fa])
			x=anc[x][i];
	return x;
}
void dfs(int x,int fa){
	dfn[x]=++tot;
	get_fa(x,fa);
	sz[x]=1,dep[x]=dep[fa]+1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dfs(y,x),sz[x]+=sz[y];
	}
}
int d[N];
queue<int>q;
inline bool check(){
	int tt=0;
	for (int i=1;i<=n;++i)
		if (!d[i])
			q.push(i),++tt;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (!(--d[y])) q.push(y),++tt;
		}
	}
	return (tt==n);
}
int main(){
//	freopen("5485.in","r",stdin);
//	freopen("5485.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<=n;++i) p[i]=1;
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(1,0);	
	memset(head,0,sizeof(head));
	cnt=0;
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		add(u,v),++d[v];
		p[u]=0;
		if (!chk(u,v)){
			int l=dfn[u],r=dfn[u]+sz[u]-1;
			++s[l],--s[r+1];
		}else{
			v=find(v,u);
			int l=dfn[v],r=dfn[v]+sz[v]-1;
			if (l-1>=1) ++s[1],--s[l];
			if (r+1<=n) ++s[r+1];
		}
	}
	if (!check()){
		for (int i=1;i<=n;++i)
			puts("0");
		return 0;
	}
	for (int i=1;i<=n;++i)
		s[i]+=s[i-1];
	for (int i=1;i<=n;++i)
		printf("%d\n",(p[i]&(s[dfn[i]]==0)));
	return 0;
}
