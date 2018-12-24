#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
using namespace std;
#define read Read<int>
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
int n,m,cnt;
int t,tot,top;
struct node{
	int to,next;
}a[50010];
int c[10010],w[10010];
int head[10010],d[10010];
int q[100010],p[10010];
int dfn[10010],low[10010];
void init(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;	
} 
void dfs(int x){
	dfn[x]=low[x]=++t;
	q[++top]=x;
	p[x]=1;
	for (int i=head[x];i;i=a[i].next){
		int y=a[i].to;
		if (p[y]) low[x]=low[x]<dfn[y]?low[x]:dfn[y];
		else if (!dfn[y]){
			dfs(y);	
			low[x]=low[x]<low[y]?low[x]:low[y];
		} 
	}
	if (low[x]==dfn[x]){
		tot++;
		while (q[top]!=x){
			c[q[top]]=tot;
			p[q[top]]=0;
			w[tot]++;
			top--;
		}
		c[q[top]]=tot;
		w[tot]++;
		p[q[top]]=0;
		top--;
	}
}
int main(){
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		init(u,v);
	}
	for (int i=1;i<=n;++i)
		if (!dfn[i]){
			t=top=0;
			dfs(i);	
		}
	for (int i=1;i<=n;++i)
		for (int j=head[i];j;j=a[j].next)
			if (c[i]!=c[a[j].to])
				d[c[i]]++;
	int ans=0,flag=0;
	for (int i=1;i<=tot;++i)
		if (!d[i]){
			if (!flag){
				ans+=w[i];
				flag=1;
			}else{
				ans=0;
				break;	
			}
		}
	printf("%d\n",ans);
	return 0;
}

