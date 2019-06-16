#include<bits/stdc++.h>
#define read() Read<int>()
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
using namespace std;
typedef long long ll;
const int N=4e5+5;
const int M=1e7+5;
int n,tot;
ll ans;
int a[N],ch[M][2];
int f[N],g[N],s[N];
inline void init(){
	memset(ch,0,sizeof(ch));
	tot=0;
}
inline void ins(int x){
	int now=0;
	for (int i=30;~i;--i){
		int t=((x&(1<<i))!=0);
		if (!ch[now][t]) ch[now][t]=++tot;
		now=ch[now][t];
	}
}
inline int query(int x){
	int now=0,res=0;
	for (int i=30;~i;--i){
		int t=((x&(1<<i))!=0);
		if (!ch[now][t^1]) t^=1;
		else res+=(1<<i);
		now=ch[now][t^1];
	}
	return res;
}
int main(){
	freopen("4260.in","r",stdin);
	freopen("4260.out","w",stdout);
	n=read();
	for (int i=1;i<=n;++i) a[i]=read();
	ins(0);
	for (int i=1;i<=n;++i){
		s[i]=s[i-1]^a[i];
		ins(s[i]);
		f[i]=query(s[i]);
		f[i]=max(f[i],f[i-1]);
	}	
	init(),ins(0);
	for (int i=n;i;--i){
		s[i]=s[i+1]^a[i];
		ins(s[i]);
		g[i]=query(s[i]);
		g[i]=max(g[i],g[i+1]);
		ans=max(ans,(ll)f[i]+g[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
