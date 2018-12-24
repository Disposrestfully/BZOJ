#include<bits/stdc++.h>
#define read() Read<int>()
using namespace std;
typedef long long ll;
const int N=505;
const double eps=1e-7;
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
struct edge{
	int next,to;
	double w;
}e[N*N];
int head[N],cnt;
inline void add(int u,int v){
	e[++cnt].to=v;
	e[cnt].next=head[u];
	head[u]=cnt;
}
int n,m,d[N];
double a[N][N],f[N],w[N*N];
inline void gauss(){
	for (int k=1;k<=n;++k){
		int pos=k;
		for (int i=k+1;i<=n;++i)
			if (fabs(a[i][k])>fabs(a[pos][k])) pos=i;
		if (pos!=k){
			for (int i=1;i<=n+1;++i)
				swap(a[pos][i],a[k][i]);
		}
		for (int i=k+1;i<=n;++i){
			if (a[i][k]!=0){
				double u=a[i][k]/a[k][k];
				for (int j=k;j<=n+1;++j){
					a[i][j]-=u*a[k][j];
					//if (isinf(a[i][j])) printf("%.3lf %.3lf\n",u,a[k][j]);	
				}
			}
		}
	}
	/*for (int i=1;i<=n;++i){
		for (int j=1;j<=n+1;++j)
			printf("%.3lf ",a[i][j]);
		printf("\n");
	}*/
	for (int i=n;i;--i){
		double tmp=0;
		for (int j=i+1;j<=n;++j)
			tmp+=a[i][j]*f[j];
		f[i]=(a[i][n+1]-tmp)/a[i][i];
	}
}
int main(){
	freopen("3143.in","r",stdin);
	freopen("3143.out","w",stdout);
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		add(u,v),add(v,u);
		++d[u],++d[v];	
	}
	for (int i=1;i<n;++i){
		for (int j=head[i];j;j=e[j].next){
			int y=e[j].to;
			//printf("%d %d\n",i,y);
			if (y!=n) a[i][y]=-1.0/(double)d[y];
		}
		a[i][i]=1;
	}	
	a[1][n]=1;
/*	for (int i=1;i<n;++i){
		for (int j=1;j<=n;++j)
			printf("%.3lf ",a[i][j]);
		printf("\n");
	}*/
	--n;
	gauss();
	++n;
	/*for (int i=1;i<=n;++i)
		printf("%.3lf ",f[i]);
	printf("\n");*/
	for (int i=1;i<=n;++i)
		for (int j=head[i];j;j=e[j].next)
			e[j].w+=f[i]/d[i];
	for (int i=1;i<=cnt;++i){
		w[(i+1)>>1]+=e[i].w;
		//printf("%d %.3lf\n",i,e[i].w);	
	}
	sort(w+1,w+m+1);
	/*for (int i=1;i<=m;++i)
		if (w[i]<0) printf("%.3lf %d ",w[i],i);
	printf("\n");*/
	double ans=0;
	for (int i=1;i<=m;++i)
		ans+=w[i]*(double)(m-i+1);
	printf("%.3lf\n",ans);
	return 0;
}
