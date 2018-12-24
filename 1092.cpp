#include<bits/stdc++.h>
#include<sys/mman.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
using namespace std;
typedef long long ll;
const int N=105;
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
int p[N],s[N],h[N];
int x[N],pos[N],y[N];
int n,m,tx,ty;
struct edge{
	int next,to,w;
}a[N<<1];
int head[N],cnt;
void add(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
int main(){
	//freopen("1.in","r",stdin);
	n=read();
	for (int i=1;i<=n;++i){
		pos[x[i]=read()]=i;
		y[i]=read();h[i]=read();
		s[i]=h[i]+y[i];
	}	
	m=read();
	for (int i=1;i<=m;++i){
		int lx=read(),ly=read(),d=read();
		//printf("%d %d",y[pos[lx]]+h[pos[lx]]-ly,y[pos[lx+d]]+h[pos[lx+d]]-ly);
		add(pos[lx-1],pos[lx+d],ly);
		add(pos[lx+d],pos[lx-1],ly);
	}
	tx=read();ty=read();
	p[1]=1;
	int ans=0;
	while (1){
		bool flag=1;
		while (flag){
			flag=0;
			for (int i=1;i<=n;++i)
				if (p[i]){
					for (int j=head[i];j;j=a[j].next)
						if (s[i]<=a[j].w && !p[a[j].to]) p[a[j].to]=flag=1;
				}
		}
		int mx=0;
		for (int i=1;i<=n;++i)
			if (p[i]) mx=max(mx,s[i]);
		if (p[tx] && mx==ty){
			printf("%d\n",ans);
			return 0;
		}
		for (int i=1;i<=n;++i)
			if (p[i] && s[i]==mx && s[i]==y[i]){
				puts("-1");
				return 0;
			}
		for (int i=1;i<=n;++i)
			if (p[i] && s[i]==mx)
				--s[i],++ans;
		/*for (int i=1;i<=n;++i)
			printf("%d ",s[i]);
		printf("\n");*/
	}
	return 0;
}
