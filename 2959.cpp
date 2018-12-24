#include<cstdio>
#include<algorithm>
#include<cstring>
#define get(x) (next[f[x]][1]==x)
#define isroot(x) (next[f[x]][1]!=x && next[f[x]][0]!=x)
#define max(a,b) a>b?a:b
using namespace std;
typedef long long ll;
const int N=1e5+5e4+5;
namespace pb_ds
{   
    namespace io
    {
        const int MaxBuff = 1 << 15;
        const int Output = 1 << 22;
        char B[MaxBuff], *S = B, *T = B;
        #define getc() ((S == T) && (T = (S = B) + fread(B, 1, MaxBuff, stdin), S == T) ? 0 : *S++)
        char Out[Output], *iter = Out;
        inline void flush()
        {
            fwrite(Out, 1, iter - Out, stdout);
            iter = Out;
        }
    }
    template<class Type> inline Type read()
    {
        using namespace io;
        register char ch; register Type ans = 0; register bool neg = 0;
        while(ch = getc(), (ch < '0' || ch > '9') && ch != '-')     ;
        ch == '-' ? neg = 1 : ans = ch - '0';
        while(ch = getc(), '0' <= ch && ch <= '9') ans = ans * 10 + ch - '0';
        return neg ? -ans : ans;
    }

    template<class Type> inline void Print(register Type x, register char ch = '\n')
    {
        using namespace io;
        if(!x) *iter++ = '0';
        else
        {
            if(x < 0) *iter++ = '-', x = -x;
            static int s[100]; register int t = 0;
            while(x) s[++t] = x % 10, x /= 10;
            while(t) *iter++ = '0' + s[t--];
        }
        *iter++ = ch;
    }
};
using namespace pb_ds;
int n,m,opt,a,b,top;
int f[N],next[N][2],w[N],val[N];
int sum[N],rev[N],sta[N],q[N];
namespace F1{
	int f[N];
	int find(int x){
		if (f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	inline void link(int x,int y){
		int fx=find(x),fy=find(y);
		f[fx]=fy;
	}
	inline void clear(){
		for (int i=1;i<=n;++i)
			f[i]=i;
	}
};
namespace F2{
	int f[N];
	int find(int x){
		if (f[x]==x) return x;
		return f[x]=find(f[x]);
	}
	inline void link(int x,int y){
		int fx=find(x),fy=find(y);
		f[fx]=fy;
	}
	inline void clear(){
		for (int i=1;i<=n;++i) f[i]=i;
	}
};
inline void pushup(int x){
	sum[x]=val[x];
	sum[x]+=sum[next[x][1]];
	sum[x]+=sum[next[x][0]];
}
inline void pushdown(int x){
	if (!x) return;
	if (rev[x]){
		rev[next[x][1]]^=1;
		rev[next[x][0]]^=1;
		swap(next[x][1],next[x][0]);
		rev[x]=0;
	}
}
inline void rotate(int x){
	int y=f[x],z=f[y],k=get(x);
	if (z && !isroot(y)) next[z][get(y)]=x;
	f[x]=z;f[y]=x;
	next[y][k]=next[x][k^1];
	if (next[y][k]) f[next[y][k]]=y;
	next[x][k^1]=y;
	pushup(y);pushup(x);
}
inline void splay(int x){
	x=F1::find(x);f[x]=F1::find(f[x]);
	top=0,sta[++top]=x;
	for (int i=x;!isroot(i);i=f[i]){
		f[i]=F1::find(f[i]);
		sta[++top]=f[i];
		f[f[i]]=F1::find(f[f[i]]);
	}
	for (int i=top;i;--i) pushdown(sta[i]);
	for (int fa;!isroot(x);rotate(x)){
		fa=f[x];
		if (!isroot(fa))
			rotate((get(fa)==get(x))?fa:x); 
	}
}
inline void access(int x){
	int t=0;
	for (;x;t=x,x=f[x]){
		x=F1::find(x);
		splay(x);
		next[x][1]=t;
		pushup(x);
	}	
}
inline void reverse(int x){
	access(x);
	splay(x);
	rev[x]^=1;
}
inline int find(int x){
    access(x);
    splay(x);
    while (next[x][0]) x=next[x][0];
    return x;
}
inline void un(int x,int y){
    reverse(y);
    access(x);
    splay(x);
    int now=sum[x];
    int l=0,r=0;
    q[++r]=x;
    while (l<r){
        x=q[++l];
        if (next[x][0]) q[++r]=next[x][0];
        if (next[x][1]) q[++r]=next[x][1];
        F1::link(x,y);
        val[x]=sum[x]=f[x]=next[x][0]=next[x][1]=0;
    }
    val[y]=sum[y]=now;
    f[y]=0;
}
inline void link(int x,int y){
    reverse(x);
    f[x]=y;
}
inline void update(int x,int y,int v){
    access(x);
    splay(x);
    sum[x]+=v-w[y];
    val[x]+=v-w[y];
    pushup(x);
}
inline int query(int x,int y){
    reverse(x);
    access(y);
    splay(y);
    return sum[y];
}
int main(){
	//freopen("graph.in","r",stdin);
	//freopen("graph.out","w",stdout);
	n=read<int>();m=read<int>();
	for (int i=1;i<=n;++i) sum[i]=val[i]=w[i]=read<int>();
	F1::clear();
	F2::clear();
	while (m--){
		opt=read<int>(),a=read<int>(),b=read<int>();
		switch(opt){
			case 1:{
				a=F1::find(a),b=F1::find(b);
				if (a==b) break;
				int fx=F2::find(a),fy=F2::find(b);
				(fx==fy)?un(a,b):link(a,b),F2::f[fx]=fy;;
				break;
			}
			case 2:{
				int c=F1::find(a);
                if (w[a]!=b) update(c,a,b),w[a]=b;
				break;
			}
			case 3:{
				a=F1::find(a),b=F1::find(b);
				Print(F2::find(a)!=F2::find(b)?-1:query(a,b));
				break;
			}
		}
	}
	io::flush();
	return 0;
}

