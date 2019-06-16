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
const int N=2e5+5;
const double inf=(double)1e12;
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
int n,tot,L,R,rt,mxdep;
double lll,rrr;
double mp[N],d[N],mx[N];
int dep[N],dfn[N],lg[N];
int mn[N][21],pos[N],g[N];
int sz[N],f[N],vis[N],mx_dep[N];
inline bool cmp(int x,int y){
	return mx_dep[x]<mx_dep[y];
}
struct node{
	int d1;
	double d2;
	inline bool operator < (const node &u)const{
		return d1>u.d1;
	}
};
vector<node>p[N];
vector<int>ch[N];
struct Set{
	priority_queue<double>q1,q2;
	inline void clear(){
		q1=q2=priority_queue<double>();
	}
	inline void ins(double w){
		q1.push(w);
	}
	inline void del(double w){
		q2.push(w);
	}
	inline double top(){
		if (!q2.empty() && !q1.empty() && q1.top()==q2.top()) q1.pop(),q2.pop();
		if (q1.empty()) return -inf;
		return q1.top();
	}
}S;
void dfs_init(int x,int fa){
	dep[x]=dep[fa]+1;
	dfn[pos[x]=++tot]=x;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		d[y]=d[x]+a[i].w;
		dfs_init(y,x);
		dfn[++tot]=x;
	}
}
inline void RMQ(){
	for (int i=1;i<=(n<<1);++i)
		lg[i]=i==1?0:lg[i>>1]+1,mn[i][0]=dfn[i];
	for (int j=1;j<=18;++j)
		for (int i=1;i+(1<<j)-1<=(n<<1);++i)
			mn[i][j]=dep[mn[i][j-1]]<dep[mn[i+(1<<(j-1))][j-1]]?mn[i][j-1]:mn[i+(1<<(j-1))][j-1];
}
inline int lca(int l,int r){
	l=pos[l],r=pos[r];
	if (r<l) swap(l,r);
	int k=lg[r-l+1];
	return dep[mn[l][k]]<dep[mn[r-(1<<k)+1][k]]?mn[l][k]:mn[r-(1<<k)+1][k];
}
inline int dist1(int u,int v){
	//printf("%d %d %d\n",u,v,lca(u,v));
	return dep[u]+dep[v]-(dep[lca(u,v)]<<1);
}
inline double dist2(int u,int v){
	return d[u]+d[v]-(d[lca(u,v)]*2);
}
void find_root(int x,int fa,int size){
	sz[x]=1,g[x]=0;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa || vis[y]) continue;
		find_root(y,x,size),sz[x]+=sz[y];
		g[x]=max(g[x],sz[y]);
	}
	g[x]=max(g[x],size-sz[x]);
	if (!rt || g[rt]>g[x]) rt=x;
}
void build(int x,int fa){
	f[x]=fa,vis[x]=1;
	for (int i=x;f[i];i=f[i]) ch[i].push_back(x);
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa || vis[y]) continue;
		rt=0,find_root(y,x,sz[y]);
		build(rt,x);
	}
}
void init(){
	for (int x=1;x<=n;++x){
		if (!f[x]) continue;
		for (int i=0,csz=ch[x].size();i<csz;++i){
			int y=ch[x][i];
			int k1=dist1(f[x],y);
			double k2=dist2(f[x],y);
			if (k1<=R) mx[k1]=max(mx[k1],k2),mx_dep[x]=max(mx_dep[x],k1);
			if (k1<=R && k1>=L) lll=max(lll,k2/(double)k1);
		}
		for (int i=0,csz=ch[x].size();i<csz;++i){
			int y=ch[x][i];
			int k1=dist1(f[x],y);
			if (k1<=R && mx[k1]!=-inf) 
				p[x].push_back((node){k1,mx[k1]}),mx[k1]=-inf;
		}
		ch[x]=vector<int>();
		sort(p[x].begin(),p[x].end());
		/*for (int j=0,psz=p[x].size();j<psz;++j)
			printf("(%d,%d,%d,%d) ",x,f[x],p[x][j].d1,(int)p[x][j].d2);
		puts("");*/
	}
	for (int i=1;i<=n;++i)
		if (f[i]) ch[f[i]].push_back(i);
	for (int i=1;i<=n;++i)
		sort(ch[i].begin(),ch[i].end(),cmp);
		
}
inline void update(double w){
	for (int i=1;i<=n;++i){
		for (int j=0,psz=p[i].size();j<psz;++j)
			p[i][j].d2-=w*(double)p[i][j].d1;
	}
}
inline bool chk(){
	for (int x=1;x<=n;++x){
		mxdep=0;
		for (int i=0,csz=ch[x].size();i<csz;++i){
			int y=ch[x][i],nowl=0,nowr=0;
			S.clear();
			for (int j=1;j<=mxdep;++j){
				while (nowr<p[y].size() && p[y][nowr].d1+j<=R && p[y][nowr].d1+j>=L) S.ins(p[y][nowr].d2),++nowr;
				while (nowl<p[y].size() && p[y][nowl].d1+j>R) S.del(p[y][nowl].d2),++nowl;
				//printf("now==(%d,%d) %d %.3lf %.3lf\n",x,y,j,mp[j],S.top());
				if (S.top()+mp[j]>=0){
					for (int t=1;t<=mxdep;++t) mp[t]=-inf;
					return 1;
				}
			}
			for (int j=0,psz=p[y].size();j<psz;++j){
				mp[p[y][j].d1]=max(mp[p[y][j].d1],p[y][j].d2);
				//printf("%d ",p[y][j].d1);
				//printf("%d %d %d %.3lf\n",x,y,p[y][j].d1,p[y][j].d2);
			}
			mxdep=mx_dep[y];
		}
		for (int i=1;i<=mxdep;++i) mp[i]=-inf;
		//printf("\nmxdep==%d\n",mxdep);
	}
	//printf("%.3lf\n",mx);
	return 0;
}
int main(){
	freopen("1758.in","r",stdin);
	freopen("1758.out","w",stdout);
	n=read(),L=read(),R=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read(),w=read();
		add(u,v,w),add(v,u,w);
		if (w>0) rrr+=w;
	}
	for (int i=1;i<=n;++i) mx[i]=-inf,mp[i]=-inf;
	dfs_init(1,0),RMQ();
	find_root(1,0,n);
	build(rt,0),init();
	rrr/=(double)L;
	/*update(821216.312);
	chk();*/
//	lll=-inf,rrr=inf;
	while (lll+0.0001<=rrr){
		double mid=(lll+rrr)/2.0;
		//printf("%.3lf %.3lf\n",lll,rrr);
		update(mid);
		if (chk()) lll=mid;
		else rrr=mid;
		update(-mid);
	}
	printf("%.3lf\n",lll);
	return 0;
}
