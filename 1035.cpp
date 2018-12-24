#include<bits/stdc++.h>
#define read() Read<int>()
#define lowbit(i) i&(-i)
#define anti(x) (x>m?x-m:x+m)
#define y1 Y1
#define link LINK
using namespace std;
typedef double ll;
const int N=605;
const int M=8005;
const ll pi=3.1415926535897932384626433;
const ll eps=1e-7;
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
int n,m,tot,all;
ll z;
int x[N],x1[M],x2[M],x3[M];
int y[N],y1[M],y2[M],c[M];
int dl[M],belong[M];
int ok[N],w[N],p[N];
int link[N][N],inc[N][N];
int pos[N],o[N][N],ans[N][N];
inline bool cmp(int u,int v){
	return x1[u]*10000+y1[u]<x1[v]*10000+y1[v];
}
inline bool cmp2(int u,int v){
	return p[u]>p[v];
}
inline bool meet(ll x1,ll y1,ll x2,ll y2,ll q1,ll p1,ll q2,ll p2){
	if ((fabs(x1-q1)<=eps && fabs(y1-p1)<=eps) || (fabs(x1-q2)<=eps && fabs(y1-p2)<=eps))	
		return 0;
	if (fabs(q1-q2)<=eps){
		if (fabs(x1-q1)<=eps && p1<=y1 && y1<=p2) return 1;
		if (fabs(x2-q1)<=eps && p1<=y2 && y2<=p2) return 1;
		return 0;
	}
	ll k1=(y2-y1)/(x2-x1);
	ll k2=(p2-p1)/(q2-q1);
	ll b1=y1-k1*x1;
	ll b2=p1-k2*q1;
	ll x=(b2-b1)/(k1-k2);
	ll y=x*k1+b1;
	if (q1>q2) swap(q1,q2);
	return (x1<=x && x<=x2 && q1<=x && x<=q2);
}
inline ll calc(ll x1,ll y1,ll x2,ll y2){
	ll x=x2-x1,y=y2-y1,k=x*x+y*y;
	if (x==0) return y>0?(pi/2):(pi+pi/2);
	if (y==0) return x<0?0:pi;
	if (x<0 && y>0) return asin(y/k);
	if (x>0 && y>0) return pi-asin(y/k);
	if (x>0 && y<0) return acos(x/k)+pi;
	if (x<0 && y<0) return 2*pi-acos(-x/k);
}
inline ll solve(int u,int v){
	ll x,y;
	x=calc(x2[u],y2[u],x1[u],y1[u]);
	y=calc(x1[v],y1[v],x2[v],y2[v])-x;
	return y<0?y+2*pi:y;
}
int main(){
	//freopen("1.in","r",stdin);
	//freopen("1.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=n;++i) 
		x[i]=read(),y[i]=read();
	for (int i=1;i<=m;++i){
		x1[i]=x2[i+m]=read(),y1[i]=y2[i+m]=read();
		x2[i]=x1[i+m]=read(),y2[i]=y1[i+m]=read();
	}
	for (int i=1;i<=m<<1;++i)
		dl[i]=i;
	sort(dl+1,dl+(m<<1)+1,cmp);
	for (int i=1;i<=m<<1;++i){
		if (belong[dl[i]]) continue;
		int k=dl[i];
		belong[k]=++tot;
		all=0,z=0;
		do{
			int s=1,t=m<<1;
			while (s!=t){
				int mid=(s+t)>>1;
				if (x1[dl[mid]]*10000+y1[dl[mid]]<x2[k]*10000+y2[k]) s=mid+1;
				else t=mid;
			}
			int now=0;
			for (int j=s;j<=(m<<1) && x1[dl[j]]==x2[k] && y1[dl[j]]==y2[k];++j){
				if (x2[dl[j]]^x1[k] || y2[dl[j]]^y1[k])
					if (!now || solve(k,dl[j])<solve(k,now)) now=dl[j];	
			}
			belong[now]=tot;
			ll u1=x1[k]-x1[dl[i]];
			ll u2=x2[k]-x1[dl[i]];
			ll v1=y1[k]-y1[dl[i]];
			ll v2=y2[k]-y1[dl[i]];
			z+=(u1*v2-u2*v1)/2;
			x3[++all]=k=now;
		}while (k!=dl[i]);
		while (z<0 && all>0) belong[x3[all--]]=-1;
		tot-=(z<0);
	}
	for (int i=1;i<=n;++i){
		memset(c,0,sizeof(c));
		for (int j=1;j<=(m<<1);++j)
			if (belong[j]>0 && meet(x[i],y[i],x[i]+1,100000,x1[j],y1[j],x2[j],y2[j]))
				++c[belong[j]];
		for (int j=1;j<=n;++j)
			if (c[j]&1){
				++w[j];
				inc[j][i]=o[j][i]=link[i][j]=1;
			}
	}
	for (int i=1;i<=n;++i) p[i]=w[i];
	tot=0;
	for (int i=1;i<=n;++i)
		if (w[i]==1)
			x3[++tot]=i;
	for (int i=1;i<=tot;++i){
		int k;
		for (k=1;k<=n;++k)
			if (inc[x3[i]][k]==1) break;
		pos[x3[i]]=k;
		for (int j=1;j<=n;++j){
			if (link[k][j]^1) continue;
			inc[j][k]=0;
			if (--w[j]==1) x3[++tot]=j;
		}
	}
	for (int i=1;i<=m<<1;++i)
		if (belong[i]>0 && belong[anti(i)]>0)
			ans[pos[belong[i]]][pos[belong[anti(i)]]]=1;
	for (int i=1;i<=n;++i)
		for (int j=1;j<=m<<1;++j)
			if (belong[j]==i && belong[anti(j)]==-1){
				ok[i]=1;
				break;
			}
	for (int i=1;i<=n;++i){
		tot=0;
		for (int j=1;j<=n;++j)
			if (o[j][i]) dl[++tot]=j;
		if (tot<2) continue;
		sort(dl+1,dl+tot+1,cmp2);
		for (int j=2;j<=tot;++j)
			if (ok[dl[j]])
				ans[pos[dl[j]]][pos[dl[j-1]]]=ans[pos[dl[j-1]]][pos[dl[j]]]=1;
	}
	for (int i=1;i<=n;++i){
		int k=0;
		for (int j=1;j<=n;++j)
			if (ans[i][j]) ++k;
		Print(k,k==0?'\n':' ');
		for (int j=1;j<=n;++j)
			if (ans[i][j]) Print(j,--k==0?'\n':' ');
	}
	io::flush();
	return 0;
}
