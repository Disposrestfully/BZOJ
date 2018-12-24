#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=2e5+5;
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
struct Set{
	priority_queue<int>q1,q2;
	inline void ins(int x){
		q1.push(x);
		//while (!q2.empty() && !q1.empty() && q1.top()==q2.top()) q1.pop(),q2.pop();
	}
	inline void del(int x){
		q2.push(x);
		//while (!q2.empty() && !q1.empty() && q1.top()==q2.top()) q1.pop(),q2.pop();
	}
	inline int get_top(){
		while (!q2.empty() && !q1.empty() && q1.top()==q2.top()) q1.pop(),q2.pop();
		if (q1.empty()) return -1;
		return q1.top();
	}
};
struct node{
	int l,r;
	inline bool operator < (const node &u)const{
		return r<u.r;
	}
};
vector<node>path;
namespace seg{
	Set s[N<<2];
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	void update(int x,int l,int r,int L,int R,int k,int opt){
		if (L>R) return; 
		if (L<=l && r<=R){
			if (!opt) s[x].ins(k);
			else s[x].del(k);
			return;
		}
		if (L<=mid) update(ls,l,mid,L,R,k,opt);
		if (R>mid) update(rs,mid+1,r,L,R,k,opt);
	}
	int query(int x,int l,int r,int pos){
		if (l==r) return s[x].get_top();
		if (pos<=mid) return max(s[x].get_top(),query(ls,l,mid,pos));
		return max(s[x].get_top(),query(rs,mid+1,r,pos));
	}
}
using namespace seg;
struct edge{
	int next,to,w;
}a[N<<1];
int head[N],cnt;
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int n,m,tim;
int son[N],top[N],dep[N];
int dfn[N],sz[N],fa[N];
int p[N][2],w[N];
void dfs1(int x){
	dep[x]=dep[fa[x]]+1;
	sz[x]=1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa[x]) continue;
		fa[y]=x,dfs1(y);
		sz[x]+=sz[y];
		if (sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs2(int x){
	dfn[x]=++tim;
	if (x==son[fa[x]]) top[x]=top[fa[x]];
	else top[x]=x;
	if (son[x]) dfs2(son[x]);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa[x] || y==son[x]) continue;
		dfs2(y);
	}
}
inline void work(int u,int v,int k,int opt){
	path=vector<node>();
	while (top[u]!=top[v]){
		if (dep[top[u]]<dep[top[v]]) swap(u,v);
		path.push_back((node){dfn[top[u]],dfn[u]});
		//printf("%d %d %d\n",dfn[top[u]],dfn[u],k);
		u=fa[top[u]];
	}
	if (dep[u]>dep[v]) swap(u,v);
	path.push_back((node){dfn[u],dfn[v]});
	path.push_back((node){0,0});
	path.push_back((node){n+1,n+1});
	sort(path.begin(),path.end());
	for (int i=0,ssz=path.size();i<ssz-1;++i)
		if (path[i].r+1<=path[i+1].l-1)
			update(1,1,n,path[i].r+1,path[i+1].l-1,k,opt);
	//printf("%d %d %d\n",dfn[u],dfn[v],k);
}	
int main(){
	freopen("4538.in","r",stdin);
	freopen("4538.out","w",stdout);
	n=read(),m=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs1(1),dfs2(1);
	/*for (int i=1;i<=n;++i)
		printf("%d ",dfn[i]);
	printf("\n");*/
	for (int i=1;i<=m;++i){
		int opt=read();
		if (opt==2){
			int x=read();
			printf("%d\n",query(1,1,n,dfn[x]));
		}else if (opt==1){
			int x=read();
			work(p[x][0],p[x][1],w[x],opt);
		}else{
			p[i][0]=read();
			p[i][1]=read(),w[i]=read();
			work(p[i][0],p[i][1],w[i],opt);
		}
	}
	return 0;
}
