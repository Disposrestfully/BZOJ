#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=55;
const int inf=2000000;
const int M=2005;
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
    using namespace io;
    inline char get_char(){
    	return getc();
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
int n,m,fa[N],ans;
struct edge{
	int next,to,w;
}a[100010];
int head[N],cnt;
void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
int lim[N],mon[N],w[N];
int f[N][N<<1][M],g[N][M];
int flag[N],h[N][M];
void dfs(int x){
//	printf("%d\n",x);
	if (!head[x]){
		lim[x]=min(lim[x],m/mon[x]);
		for (int i=0;i<=lim[x];++i)
			for (int j=i;j<=lim[x];++j)
				f[x][i][j*mon[x]]=(j-i)*w[x];
		return;
	}
	lim[x]=inf;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		dfs(y);
		mon[x]+=a[i].w*mon[y];
		lim[x]=min(lim[x],lim[y]/a[i].w);	
	}
	lim[x]=min(lim[x],m/mon[x]);
	memset(g,-0x3f3f3f3f,sizeof(g));
	g[0][0]=0;
	for (int l=lim[x];l>=0;--l){
		int y=0;
		for (int i=head[x];i;i=a[i].next){
			++y;
			for (int j=0;j<=m;++j)
				for (int k=0;k<=j;++k)
					g[y][j]=max(g[y][j],g[y-1][j-k]+f[a[i].to][l*a[i].w][k]);
		}
		for (int j=0;j<=l;++j)
			for (int k=0;k<=m;++k)
				 f[x][j][k]=max(f[x][j][k],g[y][k]+w[x]*(l-j));
	}
}
int main(){
	freopen("1017.in","r",stdin);
	freopen("1017.out","w",stdout);
	n=read();m=read();
	memset(f,-0x3f3f3f3f,sizeof(f));
	for (int i=1;i<=n;++i){
		w[i]=read();
		char ch=0;
		while (ch!='A' && ch!='B') ch=get_char();
		if (ch=='A'){
			int c=read();
			for (int j=1;j<=c;++j){
				int v=read(),w=read();
				add(i,v,w);
				++fa[v];
			}
			flag[i]=1;
		}else{
			mon[i]=read();
			lim[i]=read();	
		}
	}
	int tot=0;
	for(int x=1;x<=n;++x)
		if(!fa[x]){
			dfs(x);
			++tot;
			for(int i=0;i<=m;++i)
				for(int j=0;j<=i;++j)
					for(int k=0;k<=lim[x];++k)
						h[tot][i]=max(h[tot][i],h[tot-1][j]+f[x][k][i-j]);
		}
	for(int i=0;i<=m;++i)
        ans=max(ans,h[tot][i]);
	printf("%d\n",ans);
	return 0;
}
