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
int n,m;
struct node{
	int next,to,w;
}a[2000010],e[2000010];
int h[100010],f[100010];
int cmp(node x,node y){
	return h[x.to]>h[y.to] || (h[x.to]==h[y.to] && x.w<y.w);	
}
int head[100010],cnt;
void init(int u,int v,int w){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	e[cnt].w=w;
	head[u]=cnt;
	a[cnt].to=v;
	a[cnt].next=u;
	a[cnt].w=w;	
}
int vis[100010],sum;
void dfs(int x){
	for (int i=head[x];i;i=e[i].next)
		if (!vis[e[i].to]){
			vis[e[i].to]=1;
			sum++;
			dfs(e[i].to);	
		}
}
long long ans=0;
int find(int x){
	if (x==f[x]) return x;
	return f[x]=find(f[x]);
} 
void link(int x,int y,int w){
	int fx=find(x),fy=find(y);
	if (fx!=fy){
		ans+=w;
		f[fx]=fy;	
	}
}
void mst(){
	for (int i=1;i<=cnt;++i)
		if (vis[a[i].to] && vis[a[i].next])
			link(a[i].next,a[i].to,a[i].w);
}
int main(){
	n=read();m=read();
	for (int i=1;i<=n;++i){
		h[i]=read();
		f[i]=i;	
	}
	for (int i=1;i<=m;++i){
		int u,v,k;
		u=read();v=read();k=read();
		if (h[u]>=h[v]) init(u,v,k);
		if (h[u]<=h[v]) init(v,u,k);
	}
	sum=1;vis[1]=1;
	dfs(1);
	printf("%d ",sum);
	sort(a+1,a+cnt+1,cmp);
	mst();
	printf("%lld\n",ans);
	return 0;
}

