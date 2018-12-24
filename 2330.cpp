#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
const int N=100010;
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
struct node{
	int next,to,w;
}a[4*N];
int head[N],cnt;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
int n,k;
int dis[N],p[N],s[N],q[N];
int spfa(){
	int f=0,l=1,now;
	p[0]=1;dis[0]=0;s[0]=1;
	while (f!=l){
		now=q[f++];
		if (f>=N) f=0;
		for (int i=head[now];i;i=a[i].next){
			int x=a[i].to;
			if (dis[x]<dis[now]+a[i].w){
				dis[x]=dis[now]+a[i].w;
				if (++s[x]>=n) return 0;
				if (!p[x]){
					p[x]=1;
					q[l++]=x;	
					if (l>=N) l=0;
				}
			}
		}
		p[now]=0;
	}
	return 1; 
}
int main(){
	n=read();k=read();
	while (k--){
		int u,v,t;
		t=read();u=read();v=read();
		if (t==1){
			init(u,v,0);
			init(v,u,0);
		}else if (t==2){
			if (u==v){
				printf("-1\n");
				return 0;	
			}
			init(u,v,1);
		}else if (t==3){
			init(v,u,0);	
		}else if (t==4){
			if (u==v){
				printf("-1\n");	
				return 0;
			}
			init(v,u,1);
		}else init(u,v,0);
	}
	for (int i=n;i>=1;--i)
		init(0,i,1);
	if (!spfa())
		printf("-1\n");
	else{
		long long ans=0;
		for (int i=1;i<=n;++i)
			ans+=dis[i];	
		printf("%lld\n",ans);	
	}
	return 0;
}

