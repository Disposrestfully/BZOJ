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
const int N=5e5+5;
const int inf=1e9;
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
int p[N];
struct node{
    int l1,l2,r1,r2,c1,c2,dis;
    void val(int x){
        c1=c2=0;
        l1=l2=r1=r2=dis=-inf;
        if(x==-1) c2=1;
        else if(x==-2) c1=1;
        else if(p[x]==1) l1=l2=r1=r2=0;
    }
   void pushup(node &a,node &b){
        c1=a.c1+max(0,b.c1-a.c2);
        c2=b.c2+max(0,a.c2-b.c1);
        dis=max(max(a.dis,b.dis),max(a.r1+b.l2,a.r2+b.l1));
        l1=max(a.l1,max(b.l1-a.c2+a.c1,b.l2+a.c2+a.c1));
        l2=max(a.l2,b.l2+a.c2-a.c1);
        r1=max(b.r1,max(a.r1-b.c1+b.c2,a.r2+b.c1+b.c2));
        r2=max(b.r2,a.r2+b.c1-b.c2);
    }
}s[N*3<<2];
int n,T,C=0;
struct edge{
	int next,to;
}e[N<<1];
int head[N],cnt;
void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}	
int val[N*3],tot;
int sz[N],f[N],pos[N],size[N],tim;
void dfs(int x,int fa){
	val[++tot]=-1;
	sz[x]=3;
	size[x]=1;
	val[++tot]=x;
	f[x]=tot;
	pos[x]=++tim;
	for (int i=head[x];i;i=e[i].next){
		int y=e[i].to;
		if (y==fa) continue;
		dfs(y,x);
		sz[x]+=sz[y];
		size[x]+=size[y];
	}
	val[++tot]=-2;
}
void build(int x,int l,int r){
	if (l==r){
		s[x].val(val[l]);
		return;
	}
	int mid=(l+r)>>1;
	build(x<<1,l,mid);
	build((x<<1)|1,mid+1,r);
	s[x].pushup(s[x<<1],s[(x<<1)|1]);
}
int ans;
vector<int>mer;
void query(int x,int l,int r,int L,int R){
	if (l>=L && r<=R){
		mer.push_back(x);
		return;
	}
	int mid=(l+r)>>1;
	if (L<=mid) query(x<<1,l,mid,L,R);
	if (R>mid) query((x<<1)|1,mid+1,r,L,R);
}
void update(int x,int l,int r,int k){
	if(l==r){
		s[x].val(val[k]);
		return;	
	}
	int mid=(l+r)>>1;
	if (k<=mid) update(x<<1,l,mid,k);
	else update((x<<1)|1,mid+1,r,k);
	s[x].pushup(s[x<<1],s[(x<<1)|1]);
}
int S[N];
void Add(int x,int k){
	for (int i=x;i<=n;i+=lowbit(i))
		S[i]+=k;
}
int sum(int x){
	int res=0;
	for (int i=x;i>=1;i-=lowbit(i))
		res+=S[i];
	return res;
}
int Cnt;
int main(){
	//freopen("practice.in","r",stdin);
	//freopen("practice.out","w",stdout);
	n=read();
	for (int i=1;i<n;++i){
		int u=read(),v=read();
		add(u,v);add(v,u);
	}
	for (int i=1;i<=n;++i) p[i]=1;
	dfs(1,0);
	build(1,1,tot);
	T=read();
	while (T--){
		char opt=0;
		while (opt!='C' && opt!='G') opt=Re.Get_Char();
		if (opt=='G'){
			//++C;
		//	printf("%d\n",c);
			if (Cnt==0) print::putint(-1);
			else if (Cnt==1) print::put('0');
			else print::putint(s[1].dis);
			print::put('\n');
		}else{		
			int u=read();			
			if (p[u]==1) Add(pos[u],-1);
			else Add(pos[u],1);
			p[u]*=-1;
			Cnt+=p[u];
			update(1,1,tot,f[u]);	
		}
	}
	print::finish();
	return 0;
}
