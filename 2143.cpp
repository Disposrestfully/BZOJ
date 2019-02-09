#include<bits/stdc++.h>
#define read() Read<int>()
#define mp make_pair
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
typedef pair<int,int> pr;
const int N=1e6+5;
const int E=1e7+5;
const int M=155;
const int inf=1e9;
int n,m,tot,ans,s1,s2,s3,l1,l2,l3;
int w1[M][M],w2[M][M],d[N],vis[N];
priority_queue<pr,vector<pr>,greater<pr> >q;
struct edge{
	int next,to,w;
}a[E<<1];
int head[N],cnt;
inline void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
struct node{
	#define ls (x<<1)
	#define rs (ls|1)
	#define mid ((l+r)>>1)
	int id[M<<2];
	int build(int x,int l,int r){
		id[x]=++tot;
		if (l==r) return id[x];
		int L=build(ls,l,mid),R=build(rs,mid+1,r);
		add(id[x],L,0),add(id[x],R,0);	
		return id[x];
	}
	void insert(int x,int l,int r,int L,int R,int s,int w){
		if (L<=l && r<=R){
			add(s,id[x],w);
			return;
		}
		if (L<=mid) insert(ls,l,mid,L,R,s,w);
		if (R>mid) insert(rs,mid+1,r,L,R,s,w);
	}
	int find(int x,int l,int r,int pos){
		if (l==r) return id[x];
		if (pos<=mid) return find(ls,l,mid,pos);
		return find(rs,mid+1,r,pos);
	}
}p[M];
inline int getid(){
	int x=read(),y=read();
	return p[x].find(1,1,m,y);
}
inline void dij(int S){
	q=priority_queue<pr,vector<pr>,greater<pr> >();
	for (int i=1;i<=tot;++i)
		vis[i]=0,d[i]=inf;
	q.push(mp(d[S]=0,S));
	while (!q.empty()){
		int x=q.top().second;
		q.pop();
		if (vis[x]) continue;
		vis[x]=1;
		for (int i=head[x];i;i=a[i].next){
			int y=a[i].to;
			if (d[y]>d[x]+a[i].w){
				d[y]=d[x]+a[i].w;
				if (!vis[y]) q.push(mp(d[y],y));
			}
		}
	}
}
int main(){
	//freopen("2143.in","r",stdin);
	n=read(),m=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			w1[i][j]=read();
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			w2[i][j]=read();
	for (int i=1;i<=n;++i)
		p[i].build(1,1,m);
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j){
			int id=p[i].find(1,1,m,j);
			for (int k=1;k<=n;++k){
				int d=max(k-i,i-k);
				if (d>w1[i][j]) continue;
				int l=max(1,j-w1[i][j]+d),r=min(m,j+w1[i][j]-d);
				p[k].insert(1,1,m,l,r,id,w2[i][j]);
			}
		}
	s1=getid(),s2=getid(),s3=getid();
	dij(s1),l2+=d[s2],l3+=d[s3];
	dij(s2),l1+=d[s1],l3+=d[s3];
	dij(s3),l2+=d[s2],l1+=d[s1];
	ans=min(l1,min(l2,l3));
	if (ans>=inf){
		printf("NO\n");
		return 0;
	}
	if (ans==l1) printf("X\n%d\n",ans);
	else if (ans==l2) printf("Y\n%d\n",ans);
	else printf("Z\n%d\n",ans);
	return 0;
}
