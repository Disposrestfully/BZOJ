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
const int N=705;
const int M=1e5+5;
queue<int>q;
int n,m,tot,e,ans,tim;
int f[N],pre[N],col[N];
int vis[N],match[N];
struct edge{
	int next,to;
}a[M<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int find(int x){
	return f[x]==x?x:f[x]=find(f[x]);
}
inline int lca(int u,int v){
	for (++tim;;swap(u,v)){
		if (!u) continue;
		u=find(u);
		if (vis[u]==tim) return u;
		vis[u]=tim,u=pre[match[u]];
	}
}
inline void shrink(int u,int v,int fa){
	while (find(u)!=fa){
		pre[u]=v,v=match[u];
		if (col[v]==2) col[v]=1,q.push(v);
		if (find(u)==u) f[u]=fa;
		if (find(v)==v) f[v]=fa;
		u=pre[v];
	}
}
inline bool bfs(int S){
	q=queue<int>();
	for (int i=1;i<=tot+n;++i)
		f[i]=i,pre[i]=col[i]=0;
	col[S]=1,q.push(S);
	while (!q.empty()){
		int x=q.front();
		q.pop();
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (find(x)==find(y) || col[y]==2) continue;
			if (!col[y]){
				pre[y]=x,col[y]=2;
				if (!match[y]){
					for (int now=y,las;now;now=las){
						las=match[pre[now]];
						match[pre[now]]=now,match[now]=pre[now];
					}
					return 1;
				}
				col[match[y]]=1,q.push(match[y]);
			}else{
				int z=lca(x,y);
				shrink(x,y,z),shrink(y,x,z);
			}
		}
	}
	return 0;
}
int main(){
	freopen("4405.in","r",stdin);
	freopen("4405.out","w",stdout);
	int T=read();
	while (T--){
		for (int i=1;i<=tot+n;++i)
			head[i]=match[i]=0;
		cnt=tot=ans=0;
		n=read(),m=read(),e=read();
		for (int i=1;i<=m;++i){
			tot+=3;
			add(tot,tot-1),add(tot-1,tot);
			add(tot-2,tot-1),add(tot-1,tot-2);
			add(tot,tot-2),add(tot-2,tot);
		}
		for (int i=1;i<=e;++i){
			int u=read(),v=read();
			for (int j=1;j<=3;++j)
				add(tot+u,(v-1)*3+j),add((v-1)*3+j,tot+u);
		}
		for (int i=1;i<=n;++i)
			if (!match[i+tot] && bfs(i+tot)) ++ans;
		for (int i=1;i<=tot;++i)
			if (!match[i] && bfs(i)) ++ans;
		printf("%d\n",ans-n);
		for (int i=1;i<=n;++i)
			printf("%d ",(match[i+tot]-1)/3+1);
		printf("\n");
	}
	return 0;
}
