#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#define y1 Y1
#define lc next[x][0]
#define rc next[x][1]
#define read() Re.Read()
#define lowbit(i) i&(-i)
#define which(x) (next[fa[x]][1]==x)
//#define Get_Char() getchar()
using namespace std;
typedef unsigned long long ll;
const int N=1e5+5e4;
const ll S=131;
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
int next[N][2],rt,m,n;
int fa[N],sz[N],tot;
ll hash[N],p[N];
char s[N],s1[N];
void pushup(int x){
	if (!x) return;
	sz[x]=sz[lc]+sz[rc]+1;
	hash[x]=hash[lc]+p[sz[lc]]*s[x]+hash[rc]*p[sz[lc]+1];
}
void rotate(int x,int k){
	int y=fa[x],z=fa[y];
	next[y][!k]=next[x][k];
	if (next[x][k]) fa[next[x][k]]=y;
	fa[x]=z;fa[y]=x;
	if (z) next[z][next[z][1]==y]=x;
	next[x][k]=y;
	sz[x]=sz[y];hash[x]=hash[y];
	pushup(y);pushup(x);
}	
void splay(int x,int tar){
	while (fa[x]!=tar){
		int y=fa[x],z=fa[y];
		//printf("%d %d %d\n",x,y,z);
		if (z==tar) rotate(x,next[y][0]==x);
		else{
			int k=next[z][0]==y;
			if (next[y][k]==x){
				rotate(x,!k);
				rotate(x,k);
			}else{
				rotate(y,k);
				rotate(x,k);
			}
		}
	}
	pushup(x);
	if (!tar) rt=x;
}
int get_kth(int x,int k){
	if (sz[lc]+1==k) return x;
	if (sz[lc]+1>k) return get_kth(lc,k);
	return get_kth(rc,k-sz[lc]-1);
}
int build(int f,int l,int r){
	if (l>r) return 0;
	int x=++tot,mid=(l+r)>>1;
	fa[x]=f;
	s[x]=s1[mid];
	lc=build(x,l,mid-1);
	rc=build(x,mid+1,r);
	pushup(x);
	//printf("%d %lld\n",x,hash[x]);
	return x;
}
void insert(int k,char x){
	int l=get_kth(rt,k),r=get_kth(rt,k+1);
	splay(l,0);splay(r,l);
	s[++tot]=x;
	fa[tot]=r;
	next[r][0]=tot;
	pushup(tot);
	pushup(r);
	pushup(l);
}
void update(int k,char x){
	k=get_kth(rt,k);
	splay(k,0);
	s[k]=x;
	pushup(k);
}
int query(int x1,int x2){
	int l=0,r=n;
	while (l<=r){
		int mid=(l+r)>>1;
		if (mid+x2>n+2){
			r=mid-1;
			continue;
		}
		int L=get_kth(rt,x1-1),R=get_kth(rt,x1+mid);
		splay(L,0);splay(R,L);
		ll tmp=hash[next[R][0]];
		L=get_kth(rt,x2-1),R=get_kth(rt,x2+mid);
		splay(L,0);splay(R,L);
		if (tmp==hash[next[R][0]]) l=mid+1;
		else r=mid-1;
	}
	return r;
}	
int main(){
	p[0]=1;
	for (int i=1;i<N;++i)
		p[i]=p[i-1]*S;
	scanf("%s%d",s1+1,&m);
	n=strlen(s1+1);
	rt=build(0,0,n+1);
	/*for (int i=1;i<=tot;++i)
		printf("%d ",fa[i]);
	printf("\n");*/
	while (m--){
		char ch=0,c[10];
		int x,y;
		while (ch>'Z' || ch<'A') ch=getchar();
		if (ch=='R'){
			scanf("%d%s",&x,c);
			update(x+1,c[0]);
		}else if (ch=='Q'){
			scanf("%d%d",&x,&y);
			if (x>y) swap(x,y);
			if (x!=y) print::putint(query(x+1,y+1));
			else print::putint(n-x+1);
			print::put('\n');
		}else{
			scanf("%d%s",&x,c);
			insert(x+1,c[0]);
			++n;
		}
	}
	print::finish();
	return 0;
}
