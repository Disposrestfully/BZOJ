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
const int N=3e5+5;
int n,m,pa,pb,mx,pos,mn,dis;
int s[N],t[N],d[N],dep[N];
int da[N],db[N],dd[N];
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
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dep[y]=dep[x]+1,dfs_init(y,x);
	}
}
void dfsa(int x,int fa){
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		da[y]=da[x]+1,dfsa(y,x);
	}
}
void dfsb(int x,int fa){
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		db[y]=db[x]+1,dfsb(y,x);
	}
}
void dfsp(int x,int fa){
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (y==fa) continue;
		dd[y]=dd[x]+1,dfsp(y,x);
	}
}
int main(){
	freopen("4151.in","r",stdin);
	freopen("4151.out","w",stdout);
	int T=read();
	while (T--){
		memset(head,0,sizeof(head));
		n=read(),m=read();
		mx=-1,pa=pb=cnt=0,mn=1e9;
		for (int i=1;i<n;++i){
			int u=read(),v=read();
			add(u,v),add(v,u);
		}
		dfs_init(1,0);
		for (int i=1;i<=m;++i){
			s[i]=read(),t[i]=read(),d[i]=read();
			int now=max(0,dep[s[i]]+dep[t[i]]-d[i]);
			if (now>mx) mx=now,pa=s[i],pb=t[i],dis=d[i];
		}
		da[pa]=db[pb]=0,pos=-1;
		dfsa(pa,0),dfsb(pb,0);
		for (int i=1;i<=n;++i)
			if (da[i]+db[i]<=dis)
				if (dep[i]<mn){
					mn=dep[i];
					pos=i;
				}
		if (pos==-1){
			puts("NIE");
			continue;
		}
		dd[pos]=0,dfsp(pos,0);
		for (int i=1;i<=m;++i)
			if (dd[s[i]]+dd[t[i]]>d[i]){
				pos=-1;
				break;
			}
		if (pos==-1) puts("NIE");
		else printf("TAK %d\n",pos);
	}
	return 0;
}
