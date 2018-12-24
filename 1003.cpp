#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define read Read<int>
using namespace std;
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
}a[1010];
int head[50],cnt;
void init(int u,int v,int w){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
	a[cnt].w=w;
}
int t,n,m,k,d;
struct ride{
	int l[110],r[110],p;
}s[50];
int dist[50],cost[110][110];
int f[110],p[50];
int jud(int x,int l,int r){
	for (int i=1;i<=s[x].p;++i){
		if ((s[x].l[i]<=r && s[x].l[i]>=l) || (s[x].r[i]<=r && s[x].r[i]>=l))
			return 0;
		if ((r<=s[x].r[i] && r>=s[x].l[i]) || (l<=s[x].r[i] && l>=s[x].l[i]))
			return 0;	
		}
	return 1;
}
int main(){
	//freopen("tran.in","r",stdin);
	//freopen("tran.out","w",stdout);
	t=read();n=read();
	k=read();m=read();
	for (int i=1;i<=m;++i){
		int u,v,w;
		u=read();v=read();w=read();
		init(u,v,w);init(v,u,w);
	}
	d=read();
	for (int i=1;i<=d;++i){
		int u,l,r;
		u=read();l=read();r=read();
		s[u].p++;
		s[u].l[s[u].p]=l;
		s[u].r[s[u].p]=r;
	}
	for (int l=1;l<=t;++l){
		for (int r=l;r<=t;++r){
			for (int i=1;i<=n;++i){
				p[i]=0;
				dist[i]=2e9;
			}
			dist[1]=0;p[1]=1;
			for (int i=head[1];i;i=a[i].next){
				int y=a[i].to;
				if (jud(y,l,r)) dist[y]=dist[y]<a[i].w?dist[y]:a[i].w;	
			}
			while (1){
				int pos=-1,mn=2e9;
				if (p[n]) break;
				for (int i=1;i<=n;++i)
					if (jud(i,l,r) && !p[i] && mn>dist[i]){
						mn=dist[i];
						pos=i;
					}
				if (pos==-1) break;
				p[pos]=1;
				for (int i=head[pos];i;i=a[i].next){
					int y=a[i].to;
					if (jud(y,l,r)) dist[y]=dist[y]<dist[pos]+a[i].w?dist[y]:dist[pos]+a[i].w;	
				}
			}
			if (dist[n]!=2e9)
				cost[l][r]=dist[n]*(r-l+1);
			else cost[l][r]=2e9;
			//printf("%d %d %d\n",l,r,cost[l][r]);
		}
	}
	for (int i=1;i<=t;++i)
		f[i]=cost[1][i];
	for (int i=1;i<=t;++i)
		for (int j=1;j<i;++j)
			if (cost[j+1][i]!=2e9)
				f[i]=f[i]<(f[j]+cost[j+1][i]+k)?f[i]:(f[j]+cost[j+1][i]+k);
	printf("%d\n",f[t]);
	return 0;
}

