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
const int N=1e4+5;
struct node{
	int next,to;
}a[2000010];
int head[N],cnt;
void init(int u,int v){
	a[++cnt].to=v;
	a[cnt].next=head[u];
	head[u]=cnt;
}
int n,m;
int d[N],p[N],vis[N];
int main(){
	n=read();m=read();
	for (int i=1;i<=m;++i){
		int u=read(),v=read();
		init(u,v);init(v,u);	
	}
	for (int i=n;i>=1;--i){
		int pos=-1,mx=-1;
		for (int j=1;j<=n;++j)
			if (mx<d[j] && !p[j]){
				mx=d[j];
				pos=j;
			}
		if (!pos) break;
		p[pos]=1;
		for (int j=head[pos];j;j=a[j].next){
			int y=a[j].to;
			if (!p[y]) ++d[y];
		}
	}
	int ans=0;
	for (int i=1;i<=n;++i)
		if (!vis[d[i]]){
			vis[d[i]]=1;
			++ans;	
		}
	printf("%d\n",ans);
	return 0;
}

