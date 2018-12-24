#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector>
#include<map>
#include<queue>
#include<cmath>
#include<sys/mman.h>
#define read() Inputs::Read()
using namespace std;
typedef long long ll;
const int N=1e5+5;
namespace Inputs{
    char* s;
    int a[24];
    void io(){s=(char*)mmap(NULL,1 << 26 ,PROT_READ,MAP_PRIVATE,fileno(stdin),0);}
    void scan(char* u){
        while(*s<48)
            ++s;
        while(*s>32)
            *u++=*s++;
        *u=0;
    }
    int Read(){
        int Hibiki=0,v=1;
        while(*s<48)
            v=*s++^45?1:-1;
        while(*s>32)
            Hibiki=Hibiki*10+*s++-48;
        return Hibiki*v;
    }
};
struct node{
	int next,to,w,c;
}a[N<<1];
int t[1000][1000];
int head[N],cnt=1;
void add(int u,int v,int w,int c){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
	a[cnt].c=c;
}
queue<int>q;
int vis[N],pre[N],d[N];
int S,T,n,m;
double ans;
bool spfa(){
	while (!q.empty()) q.pop();
	memset(pre,0,sizeof(pre));
	memset(d,127,sizeof(d));
	memset(vis,0,sizeof(vis));
	q.push(S);d[S]=0;vis[S]=1;
	while (!q.empty()){
		int x=q.front();
		q.pop();
		vis[x]=0;
		for (int i=head[x];i;i=a[i].next){
			if (!a[i].w) continue;
			int y=a[i].to;
			if (d[y]>d[x]+a[i].c){
				pre[y]=i^1;
				d[y]=d[x]+a[i].c;
				if (!vis[y]){
					vis[y]=1;
					q.push(y);
				}
			}
		}
	}
	return pre[T];
}
double flow(){
	int res=1e9;
	for (int i=pre[T];i;i=pre[a[i].to]){
		res=min(res,a[i^1].w);
		//printf("%d %d %d\n",i,a[i].c,a[i].to);	
	}
	for (int i=pre[T];i;i=pre[a[i].to]){
		a[i^1].w-=res;
		a[i].w+=res;
	}
	return (double)res*(double)d[T];
}
int main(){
	//freopen("6.in","r",stdin);
	Inputs::io();
	m=read();n=read();
	S=1;T=n*(m+1)+2;	
	for (int i=2;i<=n+1;++i){
		add(S,i,1,0);
		add(i,S,0,0);
	}
	for (int i=n+2;i<T;++i){
		add(i,T,1,0);
		add(T,i,0,0);	
	}
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m;++j)
			t[i][j]=read();
	for (int i=2;i<=n+1;++i){
		for (int j=1;j<=m;++j){
			for (int k=1;k<=n;++k){
				add(i,k+j*n+1,1,t[i-1][j]*k);
				add(k+j*n+1,i,0,-t[i-1][j]*k);
			}
		}
	}
	while (spfa()) ans+=flow();
	printf("%.2lf\n",ans/n);
	return 0;
}
