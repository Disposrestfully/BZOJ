#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define read() Re.Read()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=1e5+5;
const int M=2e6+5;
struct Readint{
	char buffer[1<<15],*S,*T; 
	inline char Get_Char(){  
    	if(S==T){  
     	   T=(S=buffer)+fread(buffer,1,1<<15,stdin);
      	  if(S==T) return EOF;  
    	}  
    	return *S++;  
	}
	int Read(){
	    char c;  
	    int re=0;  
	    for (c=Get_Char();c<'0'||c>'9';c=Get_Char()){
    		if (c==EOF) return -1;
    	}	
 	   	while(c>='0'&&c<='9')  
           	re=(re<<1)+(re<<3)+(c-'0'),c=Get_Char();  
    	return re;  
	}
}Re;
namespace print{
    static const int BUF=50000000;
    char buf[BUF],*h=buf;
    inline void put(char ch){
        h==buf+BUF?(fwrite(buf,1,BUF,stdout),h=buf):0;
        *h++=ch;
    }
    inline void putint(int num){
        static char _buf[30];
        sprintf(_buf,"%d",num);
        for (char *s=_buf;*s;s++)put(*s);
    }
    inline void finish(){
        fwrite(buf,1,h-buf,stdout);
    }
};
struct edge{
	int next,to;
}a[M<<1];
int head[N],cnt,n,m,tim;
int low[N],dfn[N],fa[N],ans;
int f[N],dep[N],s[N<<1],q[N];
inline void init(){
	memset(head,0,sizeof(head));
	memset(dfn,0,sizeof(dfn));
	memset(f,0,sizeof(f));
	cnt=tim=ans=0;
}
inline void add(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[++cnt].to=u;
	a[cnt].next=head[v];
	head[v]=cnt;
}
inline void insert_path(){
	int k=read();
	int now,lst=read();
	for (int i=2;i<=k;++i){
		add(lst,now=read());
		lst=now;
	}
}
inline void solve(int rt,int x){
	int tot=dep[x]-dep[rt]+1;
	for (int i=x;i!=rt;i=fa[i])
		s[tot--]=f[i];
	s[tot]=f[rt];
	tot=dep[x]-dep[rt]+1;
	for (int i=1;i<=tot;++i)
		s[i+tot]=s[i];
	q[1]=1;
	int l=1,r=1;
	for (int i=2;i<=tot<<1;++i){
		while (l<=r && i-q[l]>(tot>>1)) ++l;
		ans=max(ans,s[i]+i+s[q[l]]-q[l]);
		while (l<=r && s[q[r]]-q[r]<=s[i]-i) --r;
		q[++r]=i;
	}
	for (int i=2;i<=tot;++i)
		f[rt]=max(f[rt],s[i]+min(tot-i+1,i-1));
}
void tarjan(int x){
	dfn[x]=low[x]=++tim;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa[x]) continue;
		if (!dfn[y]){
			fa[y]=x;
			dep[y]=dep[x]+1;
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else low[x]=min(low[x],dfn[y]);
		if (dfn[x]<low[y]){
			ans=max(ans,f[x]+f[y]+1);
			f[x]=max(f[x],f[y]+1);
		}
	}
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (fa[y]!=x && dfn[x]<dfn[y]) solve(x,y);
	}
}
int main(){
	//freopen("2.in","r",stdin);
	while (1){
		n=read();
		if (n<0){
			print::finish();
			return 0;
		}
		m=read();
		init();
		for (int i=1;i<=m;++i) 
			insert_path();
		tarjan(1);
		print::putint(ans);
		print::put('\n');
	}	
	return 0;
}
